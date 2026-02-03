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
	local fn="$1"

	id="$fn"
	desc=""
	cmd=""
	files=()
	status=0
	case_dir="$WORKDIR/$fn"
	mkdir -p "$case_dir"
	pushd "$case_dir" >/dev/null || exit 1
	"$fn"
	emit_report
	popd >/dev/null || exit 1
}

# ------------------------------------------------------------
# ケース定義
# ------------------------------------------------------------

create_truncate() {
	desc="`>` による作成・切り詰め"
	cmd='echo one > out_trunc.txt'
	files=("out_trunc.txt")
	run_cmd bash -c "$cmd"
}

append_existing() {
	desc="`>>` による既存ファイルへの追記"
	cmd='printf "A\n" > out_app.txt; echo B >> out_app.txt'
	files=("out_app.txt")
	run_cmd bash -c "$cmd"
}

append_new() {
	desc="追記で新規作成される"
	cmd='echo C >> out_new.txt'
	files=("out_new.txt")
	run_cmd bash -c "$cmd"
}

input_basic() {
	desc="入力リダイレクトの基本"
	printf "in1\n" > in1.txt
	cmd='cat < in1.txt'
	files=("in1.txt")
	run_cmd bash -c "$cmd"
}

input_last_wins() {
	desc="入力の多重指定（最後が有効）"
	printf "first\n" > in1.txt
	printf "second\n" > in2.txt
	cmd='cat < in1.txt < in2.txt'
	files=("in1.txt" "in2.txt")
	run_cmd bash -c "$cmd"
}

output_last_wins() {
	desc="出力の多重指定（最後が有効、先は空作成）"
	cmd='echo X > out1.txt > out2.txt'
	files=("out1.txt" "out2.txt")
	run_cmd bash -c "$cmd"
}

input_output_together() {
	desc="入出力の同時指定"
	printf "mix\n" > in1.txt
	cmd='cat < in1.txt > out_mix.txt'
	files=("in1.txt" "out_mix.txt")
	run_cmd bash -c "$cmd"
}

output_then_input_fail() {
	desc="出力作成→入力失敗の順序"
	cmd='cat > out_order.txt < missing.txt'
	files=("out_order.txt" "missing.txt")
	run_cmd bash -c "$cmd"
}

input_fail_then_output_missing() {
	desc="入力失敗→出力未作成の順序"
	cmd='cat < missing.txt > out_order.txt'
	files=("out_order.txt" "missing.txt")
	run_cmd bash -c "$cmd"
}

output_path_missing_dir() {
	desc="出力先ディレクトリが存在しない"
	cmd='echo HI > no_such_dir/out.txt'
	files=("no_such_dir/out.txt")
	run_cmd bash -c "$cmd"
}

cmd_not_found_but_redir() {
	desc="コマンド未発見でもリダイレクト処理"
	cmd='nosuchcmd > out_nf.txt'
	files=("out_nf.txt")
	run_cmd bash -c "$cmd"
}

output_target_directory() {
	desc="出力先がディレクトリ"
	mkdir dir
	cmd='echo hi > dir'
	files=("dir")
	run_cmd bash -c "$cmd"
}

input_source_directory() {
	desc="入力元がディレクトリ"
	mkdir dir
	cmd='cat < dir'
	files=("dir")
	run_cmd bash -c "$cmd"
}

output_readonly() {
	desc="出力先が書き込み不可"
	printf "orig\n" > readonly.txt
	chmod 444 readonly.txt
	cmd='echo hi > readonly.txt'
	files=("readonly.txt")
	run_cmd bash -c "$cmd"
}

input_unreadable() {
	desc="入力元が読み取り不可"
	printf "secret\n" > noread.txt
	chmod 000 noread.txt
	cmd='cat < noread.txt'
	files=("noread.txt")
	run_cmd bash -c "$cmd"
}

filename_with_spaces() {
	desc="空白を含むファイル名"
	cmd='echo hi > "spaced name.txt"'
	files=("spaced name.txt")
	run_cmd bash -c "$cmd"
}

heredoc_unquoted_expands() {
	desc="heredoc（未クォート）で変数展開"
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
	files=()
	run_cmd bash cmd.sh
}

heredoc_quoted_no_expand() {
	desc="heredoc（クォート）で変数展開なし"
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
	files=()
	run_cmd bash cmd.sh
}

heredoc_with_output() {
	desc="heredoc + 出力リダイレクト"
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
	files=("out_heredoc.txt")
	run_cmd bash cmd.sh
}

heredoc_and_input_precedence() {
	desc="heredoc + 入力リダイレクトの優先"
	printf "FILE\n" > in1.txt
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
	files=("in1.txt")
	run_cmd bash cmd.sh
}

redir_without_command() {
	desc="コマンドなしのリダイレクト"
	cmd='> out_only.txt'
	files=("out_only.txt")
	run_cmd bash -c "$cmd"
}

run_case create_truncate
run_case append_existing
run_case append_new
run_case input_basic
run_case input_last_wins
run_case output_last_wins
run_case input_output_together
run_case output_then_input_fail
run_case input_fail_then_output_missing
run_case output_path_missing_dir
run_case cmd_not_found_but_redir
run_case output_target_directory
run_case input_source_directory
run_case output_readonly
run_case input_unreadable
run_case filename_with_spaces
run_case heredoc_unquoted_expands
run_case heredoc_quoted_no_expand
run_case heredoc_with_output
run_case heredoc_and_input_precedence
run_case redir_without_command
