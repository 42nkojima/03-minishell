#!/usr/bin/env bash

# bash と minishell の結果を比較する。
# stdout からプロンプトを除去し、stdout/stderr/exit status/ファイルを比較する。

set -o pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
MINISHELL_BIN="${MINISHELL_BIN:-$ROOT_DIR/minishell}"

if [ ! -x "$MINISHELL_BIN" ]; then
	echo "minishell binary not found: $MINISHELL_BIN" >&2
	exit 1
fi

WORKDIR="$(mktemp -d 2>/dev/null || mktemp -d -t minishell-redir)"
cleanup() {
	rm -rf "$WORKDIR"
}
trap cleanup EXIT

STATUS_MARK="__MSH_STATUS__"

mismatch_stdout=()
mismatch_stderr=()
mismatch_status=()
mismatch_files=()

id=""
desc=""
cmd=""
files=()
status=0
case_dir=""
stdout_path=""
stderr_path=""

run_cmd() {
	stdout_path="$case_dir/stdout.txt"
	stderr_path="$case_dir/stderr.txt"
	"$@" >"$stdout_path" 2>"$stderr_path"
	status=$?
}

run_minishell_input() {
	local input="$1"
	local input_file="$case_dir/input.txt"

	stdout_path="$case_dir/stdout.txt"
	stderr_path="$case_dir/stderr.txt"
	printf "%s\n" "$input" > "$input_file"
	"$MINISHELL_BIN" < "$input_file" >"$stdout_path" 2>"$stderr_path"
	status=$?
}

filter_prompt() {
	sed 's/^minishell\$ //; s/^minishell\$//'
}

normalize_output() {
	local src="$1"
	local dest="$2"

	grep -v "^${STATUS_MARK}:" "$src" | filter_prompt > "$dest"
}

extract_status() {
	local src="$1"
	local s

	s=$(awk -F: -v m="$STATUS_MARK" '$1==m {s=$2} END{print s}' "$src")
	if [ -z "$s" ]; then
		echo "(missing)"
	else
		echo "$s"
	fi
}

append_status_line() {
	printf "%s\n%s\n" "$1" "echo ${STATUS_MARK}:\$?"
}

compare_files() {
	local bash_dir="$1"
	local msh_dir="$2"
	local files_str="$3"
	local mismatch=0
	local file_list=()

	if [ -z "$files_str" ]; then
		return 0
	fi
	IFS=',' read -r -a file_list <<< "$files_str"
	for f in "${file_list[@]}"; do
		local bf="$bash_dir/$f"
		local mf="$msh_dir/$f"

		if [ ! -e "$bf" ] && [ ! -e "$mf" ]; then
			continue
		fi
		if [ -e "$bf" ] != [ -e "$mf" ]; then
			mismatch=1
			continue
		fi
		if [ -d "$bf" ] || [ -d "$mf" ]; then
			if [ -d "$bf" ] && [ -d "$mf" ]; then
				continue
			else
				mismatch=1
				continue
			fi
		fi
		if [ -f "$bf" ] && [ -f "$mf" ]; then
			if [ -r "$bf" ] && [ -r "$mf" ]; then
				if ! cmp -s "$bf" "$mf"; then
					mismatch=1
				fi
			else
				if [ -r "$bf" ] != [ -r "$mf" ]; then
					mismatch=1
				fi
			fi
		else
			mismatch=1
		fi
	done
	return $mismatch
}

run_case() {
	local runner="$1"
	local name="$2"
	local desc_in="$3"
	local setup_fn="$4"
	local exec_fn="$5"
	local files_str="$6"
	local cmd_in="$7"

	id="$name"
	desc="$desc_in"
	cmd="$cmd_in"
	files=()
	if [ -n "$files_str" ]; then
		IFS=',' read -r -a files <<< "$files_str"
	fi
	status=0
	case_dir="$WORKDIR/$runner/$name"
	mkdir -p "$case_dir"
	pushd "$case_dir" >/dev/null || exit 1
	RUNNER="$runner"
	"$setup_fn"
	"$exec_fn"
	popd >/dev/null || exit 1
}

# shellcheck source=redirect_cases.sh
. "$SCRIPT_DIR/redirect_cases.sh"

# ------------------------------------------------------------
# 実行関数
# ------------------------------------------------------------

exec_shell_cmd() {
	local script

	script=$(append_status_line "$cmd")
	if [ "$RUNNER" = "bash" ]; then
		run_cmd bash -c "$script"
	else
		run_minishell_input "$script"
	fi
}

exec_heredoc_unquoted() {
	if [ "$RUNNER" = "bash" ]; then
		cat > cmd.sh <<'EOS'
VAR=HELLO
cat <<EOF
$VAR
EOF
echo __MSH_STATUS__:$?
EOS
		run_cmd bash cmd.sh
	else
		cmd=$(cat <<'EOS'
VAR=HELLO
cat <<EOF
$VAR
EOF
echo __MSH_STATUS__:$?
EOS
)
		run_minishell_input "$cmd"
	fi
}

exec_heredoc_quoted() {
	if [ "$RUNNER" = "bash" ]; then
		cat > cmd.sh <<'EOS'
VAR=HELLO
cat <<'EOF'
$VAR
EOF
echo __MSH_STATUS__:$?
EOS
		run_cmd bash cmd.sh
	else
		cmd=$(cat <<'EOS'
VAR=HELLO
cat <<'EOF'
$VAR
EOF
echo __MSH_STATUS__:$?
EOS
)
		run_minishell_input "$cmd"
	fi
}

exec_heredoc_with_output() {
	if [ "$RUNNER" = "bash" ]; then
		cat > cmd.sh <<'EOS'
cat <<EOF > out_heredoc.txt
line1
line2
EOF
echo __MSH_STATUS__:$?
EOS
		run_cmd bash cmd.sh
	else
		cmd=$(cat <<'EOS'
cat <<EOF > out_heredoc.txt
line1
line2
EOF
echo __MSH_STATUS__:$?
EOS
)
		run_minishell_input "$cmd"
	fi
}

exec_heredoc_input_precedence() {
	if [ "$RUNNER" = "bash" ]; then
		cat > cmd.sh <<'EOS'
cat <<EOF < in1.txt
HEREDOC
EOF
echo __MSH_STATUS__:$?
EOS
		run_cmd bash cmd.sh
	else
		cmd=$(cat <<'EOS'
cat <<EOF < in1.txt
HEREDOC
EOF
echo __MSH_STATUS__:$?
EOS
)
		run_minishell_input "$cmd"
	fi
}

for row in "${cases[@]}"; do
	IFS='|' read -r name desc_in setup_fn exec_fn files_str cmd_in <<< "$row"

	run_case "bash" "$name" "$desc_in" "$setup_fn" "$exec_fn" "$files_str" "$cmd_in"
	bash_dir="$WORKDIR/bash/$name"
	normalize_output "$bash_dir/stdout.txt" "$bash_dir/stdout.norm"
	bash_status="$(extract_status "$bash_dir/stdout.txt")"

	run_case "minishell" "$name" "$desc_in" "$setup_fn" "$exec_fn" "$files_str" "$cmd_in"
	msh_dir="$WORKDIR/minishell/$name"
	normalize_output "$msh_dir/stdout.txt" "$msh_dir/stdout.norm"
	msh_status="$(extract_status "$msh_dir/stdout.txt")"

	if ! cmp -s "$bash_dir/stdout.norm" "$msh_dir/stdout.norm"; then
		mismatch_stdout+=("$name")
	fi
	if ! cmp -s "$bash_dir/stderr.txt" "$msh_dir/stderr.txt"; then
		mismatch_stderr+=("$name")
	fi
	if [ "$bash_status" != "$msh_status" ]; then
		mismatch_status+=("$name")
	fi
	if ! compare_files "$bash_dir" "$msh_dir" "$files_str"; then
		mismatch_files+=("$name")
	fi
done

failed=0
if [ ${#mismatch_stdout[@]} -ne 0 ]; then
	echo "STDOUT mismatch:"
	printf " - %s\n" "${mismatch_stdout[@]}"
	failed=1
fi
if [ ${#mismatch_stderr[@]} -ne 0 ]; then
	echo "STDERR mismatch:"
	printf " - %s\n" "${mismatch_stderr[@]}"
	failed=1
fi
if [ ${#mismatch_status[@]} -ne 0 ]; then
	echo "STATUS mismatch:"
	printf " - %s\n" "${mismatch_status[@]}"
	failed=1
fi
if [ ${#mismatch_files[@]} -ne 0 ]; then
	echo "FILES mismatch:"
	printf " - %s\n" "${mismatch_files[@]}"
	failed=1
fi

if [ "$failed" -eq 0 ]; then
	echo "ALL MATCHED"
	exit 0
fi
exit 1
