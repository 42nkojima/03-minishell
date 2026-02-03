#!/usr/bin/env bash

# 共通のケース定義。各ランナー側で source して使う。
# exec_shell_cmd / exec_heredoc_* 関数の実装はランナー側に置く。

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
# テーブル（name|desc|setup|exec|files(comma)|cmd）
# ------------------------------------------------------------

cases=(
	"create_truncate|`>` による作成・切り詰め|setup_none|exec_shell_cmd|out_trunc.txt|echo one > out_trunc.txt"
	"append_existing|`>>` による既存ファイルへの追記|setup_none|exec_shell_cmd|out_app.txt|printf \"A\\n\" > out_app.txt; echo B >> out_app.txt"
	"append_new|追記で新規作成される|setup_none|exec_shell_cmd|out_new.txt|echo C >> out_new.txt"
	"input_basic|入力リダイレクトの基本|setup_in1|exec_shell_cmd|in1.txt|cat < in1.txt"
	"input_last_wins|入力の多重指定（最後が有効）|setup_in1_in2|exec_shell_cmd|in1.txt,in2.txt|cat < in1.txt < in2.txt"
	"output_last_wins|出力の多重指定（最後が有効、先は空作成）|setup_none|exec_shell_cmd|out1.txt,out2.txt|echo X > out1.txt > out2.txt"
	"input_output_together|入出力の同時指定|setup_mix|exec_shell_cmd|in1.txt,out_mix.txt|cat < in1.txt > out_mix.txt"
	"output_then_input_fail|出力作成→入力失敗の順序|setup_none|exec_shell_cmd|out_order.txt,missing.txt|cat > out_order.txt < missing.txt"
	"input_fail_then_output_missing|入力失敗→出力未作成の順序|setup_none|exec_shell_cmd|out_order.txt,missing.txt|cat < missing.txt > out_order.txt"
	"output_path_missing_dir|出力先ディレクトリが存在しない|setup_none|exec_shell_cmd|no_such_dir/out.txt|echo HI > no_such_dir/out.txt"
	"cmd_not_found_but_redir|コマンド未発見でもリダイレクト処理|setup_none|exec_shell_cmd|out_nf.txt|nosuchcmd > out_nf.txt"
	"output_target_directory|出力先がディレクトリ|setup_dir|exec_shell_cmd|dir|echo hi > dir"
	"input_source_directory|入力元がディレクトリ|setup_dir|exec_shell_cmd|dir|cat < dir"
	"output_readonly|出力先が書き込み不可|setup_readonly|exec_shell_cmd|readonly.txt|echo hi > readonly.txt"
	"input_unreadable|入力元が読み取り不可|setup_noread|exec_shell_cmd|noread.txt|cat < noread.txt"
	"filename_with_spaces|空白を含むファイル名|setup_none|exec_shell_cmd|spaced name.txt|echo hi > \"spaced name.txt\""
	"heredoc_unquoted_expands|heredoc（未クォート）で変数展開|setup_none|exec_heredoc_unquoted||"
	"heredoc_quoted_no_expand|heredoc（クォート）で変数展開なし|setup_none|exec_heredoc_quoted||"
	"heredoc_with_output|heredoc + 出力リダイレクト|setup_none|exec_heredoc_with_output|out_heredoc.txt|"
	"heredoc_and_input_precedence|heredoc + 入力リダイレクトの優先|setup_in1_file|exec_heredoc_input_precedence|in1.txt|"
	"redir_without_command|コマンドなしのリダイレクト|setup_none|exec_shell_cmd|out_only.txt|> out_only.txt"
)
