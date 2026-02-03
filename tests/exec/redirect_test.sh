#!/usr/bin/env bash

# Bash のリダイレクト挙動を観察する参照テスト。
# 各ケースは「準備 → desc/cmd/files 設定 → run_cmd 実行」の順に記述する。

set -o pipefail

WORKDIR="$(mktemp -d 2>/dev/null || mktemp -d -t minishell-redir)"
cleanup() {
	rm -rf "$WORKDIR"
}
trap cleanup EXIT

echo "BASH_VERSION=${BASH_VERSION:-unknown}"
echo "BASH_BIN=$(command -v bash || echo bash)"
echo "DATE_UTC=$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
echo "WORKDIR=$WORKDIR"
echo

id=""
desc=""
cmd=""
files=()
status=0
case_dir=""
stdout_path=""
stderr_path=""

# コマンドの stdout/stderr/終了コードを捕捉する
run_cmd() {
	stdout_path="$case_dir/stdout.txt"
	stderr_path="$case_dir/stderr.txt"
	"$@" >"$stdout_path" 2>"$stderr_path"
	status=$?
}

snapshot_file() {
	local f="$1"

	echo "-- $f --"
	if [ -e "$f" ]; then
		ls -ld "$f"
		if [ -f "$f" ]; then
			if [ -r "$f" ]; then
				printf "サイズ: %s バイト\n" "$(wc -c < "$f" 2>/dev/null | tr -d ' ')"
				echo "先頭:"
				head -n 5 "$f"
			else
				echo "サイズ: (読み取り不可)"
				echo "先頭: (読み取り不可)"
			fi
		else
			echo "種別: (通常ファイルではありません)"
		fi
	else
		echo "存在しません"
	fi
}

emit_report() {
	# ケース結果を整形して出力する
	echo "=== $id: $desc ==="
	echo "コマンド:"
	printf '%s\n' "$cmd"
	echo "終了コード: $status"
	echo "標準出力:"
	if [ -s "$stdout_path" ]; then
		cat "$stdout_path"
	else
		echo "(空)"
	fi
	echo "標準エラー:"
	if [ -s "$stderr_path" ]; then
		cat "$stderr_path"
	else
		echo "(空)"
	fi
	echo "ファイル:"
	if [ "${#files[@]}" -eq 0 ]; then
		echo "(なし)"
	else
		for f in "${files[@]}"; do
			snapshot_file "$f"
		done
	fi
	echo
}

run_case() {
	# ケース用の一時ディレクトリを作って実行する
	local name="$1"
	local desc_in="$2"
	local setup_fn="$3"
	local exec_fn="$4"
	local files_str="$5"
	local cmd_in="$6"

	id="$name"
	desc="$desc_in"
	cmd="$cmd_in"
	files=()
	if [ -n "$files_str" ]; then
		IFS=',' read -r -a files <<< "$files_str"
	fi
	status=0
	case_dir="$WORKDIR/$name"
	mkdir -p "$case_dir"
	pushd "$case_dir" >/dev/null || exit 1
	"$setup_fn"
	"$exec_fn"
	emit_report
	popd >/dev/null || exit 1
}

# ------------------------------------------------------------
# 準備関数
# ------------------------------------------------------------

setup_none() { :; }
setup_in1() { printf "in1\n" > in1.txt; }
setup_in1_in2() {
	printf "first\n" > in1.txt
	printf "second\n" > in2.txt
}
setup_mix() { printf "mix\n" > in1.txt; }
setup_dir() { mkdir dir; }
setup_readonly() {
	printf "orig\n" > readonly.txt
	chmod 444 readonly.txt
}
setup_noread() {
	printf "secret\n" > noread.txt
	chmod 000 noread.txt
}
setup_in1_file() { printf "FILE\n" > in1.txt; }

# ------------------------------------------------------------
# 実行関数
# ------------------------------------------------------------

exec_bash_cmd() {
	run_cmd bash -c "$cmd"
}

exec_heredoc_unquoted() {
	cat > cmd.sh <<'EOS'
VAR=HELLO
cat <<EOF
$VAR
EOF
EOS
	cmd=$(cat <<'EOS'
VAR=HELLO
cat <<EOF
$VAR
EOF
EOS
)
	run_cmd bash cmd.sh
}

exec_heredoc_quoted() {
	cat > cmd.sh <<'EOS'
VAR=HELLO
cat <<'EOF'
$VAR
EOF
EOS
	cmd=$(cat <<'EOS'
VAR=HELLO
cat <<'EOF'
$VAR
EOF
EOS
)
	run_cmd bash cmd.sh
}

exec_heredoc_with_output() {
	cat > cmd.sh <<'EOS'
cat <<EOF > out_heredoc.txt
line1
line2
EOF
EOS
	cmd=$(cat <<'EOS'
cat <<EOF > out_heredoc.txt
line1
line2
EOF
EOS
)
	run_cmd bash cmd.sh
}

exec_heredoc_input_precedence() {
	cat > cmd.sh <<'EOS'
cat <<EOF < in1.txt
HEREDOC
EOF
EOS
	cmd=$(cat <<'EOS'
cat <<EOF < in1.txt
HEREDOC
EOF
EOS
)
	run_cmd bash cmd.sh
}

# ------------------------------------------------------------
# テーブル（name|desc|setup|exec|files(comma)|cmd）
# ------------------------------------------------------------

cases=(
	"create_truncate|`>` による作成・切り詰め|setup_none|exec_bash_cmd|out_trunc.txt|echo one > out_trunc.txt"
	"append_existing|`>>` による既存ファイルへの追記|setup_none|exec_bash_cmd|out_app.txt|printf \"A\\n\" > out_app.txt; echo B >> out_app.txt"
	"append_new|追記で新規作成される|setup_none|exec_bash_cmd|out_new.txt|echo C >> out_new.txt"
	"input_basic|入力リダイレクトの基本|setup_in1|exec_bash_cmd|in1.txt|cat < in1.txt"
	"input_last_wins|入力の多重指定（最後が有効）|setup_in1_in2|exec_bash_cmd|in1.txt,in2.txt|cat < in1.txt < in2.txt"
	"output_last_wins|出力の多重指定（最後が有効、先は空作成）|setup_none|exec_bash_cmd|out1.txt,out2.txt|echo X > out1.txt > out2.txt"
	"input_output_together|入出力の同時指定|setup_mix|exec_bash_cmd|in1.txt,out_mix.txt|cat < in1.txt > out_mix.txt"
	"output_then_input_fail|出力作成→入力失敗の順序|setup_none|exec_bash_cmd|out_order.txt,missing.txt|cat > out_order.txt < missing.txt"
	"input_fail_then_output_missing|入力失敗→出力未作成の順序|setup_none|exec_bash_cmd|out_order.txt,missing.txt|cat < missing.txt > out_order.txt"
	"output_path_missing_dir|出力先ディレクトリが存在しない|setup_none|exec_bash_cmd|no_such_dir/out.txt|echo HI > no_such_dir/out.txt"
	"cmd_not_found_but_redir|コマンド未発見でもリダイレクト処理|setup_none|exec_bash_cmd|out_nf.txt|nosuchcmd > out_nf.txt"
	"output_target_directory|出力先がディレクトリ|setup_dir|exec_bash_cmd|dir|echo hi > dir"
	"input_source_directory|入力元がディレクトリ|setup_dir|exec_bash_cmd|dir|cat < dir"
	"output_readonly|出力先が書き込み不可|setup_readonly|exec_bash_cmd|readonly.txt|echo hi > readonly.txt"
	"input_unreadable|入力元が読み取り不可|setup_noread|exec_bash_cmd|noread.txt|cat < noread.txt"
	"filename_with_spaces|空白を含むファイル名|setup_none|exec_bash_cmd|spaced name.txt|echo hi > \"spaced name.txt\""
	"heredoc_unquoted_expands|heredoc（未クォート）で変数展開|setup_none|exec_heredoc_unquoted||"
	"heredoc_quoted_no_expand|heredoc（クォート）で変数展開なし|setup_none|exec_heredoc_quoted||"
	"heredoc_with_output|heredoc + 出力リダイレクト|setup_none|exec_heredoc_with_output|out_heredoc.txt|"
	"heredoc_and_input_precedence|heredoc + 入力リダイレクトの優先|setup_in1_file|exec_heredoc_input_precedence|in1.txt|"
	"redir_without_command|コマンドなしのリダイレクト|setup_none|exec_bash_cmd|out_only.txt|> out_only.txt"
)

for row in "${cases[@]}"; do
	IFS='|' read -r name desc_in setup_fn exec_fn files_str cmd_in <<< "$row"
	run_case "$name" "$desc_in" "$setup_fn" "$exec_fn" "$files_str" "$cmd_in"
done
