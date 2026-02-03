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

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=redirect_cases.sh
. "$SCRIPT_DIR/redirect_cases.sh"

# ------------------------------------------------------------
# 実行関数
# ------------------------------------------------------------

exec_shell_cmd() {
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
# 実行
# ------------------------------------------------------------

for row in "${cases[@]}"; do
	IFS='|' read -r name desc_in setup_fn exec_fn files_str cmd_in <<< "$row"
	run_case "$name" "$desc_in" "$setup_fn" "$exec_fn" "$files_str" "$cmd_in"
done
