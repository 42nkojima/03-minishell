# Redirect Test Cases (bash)

このドキュメントは、テストケースと bash の実際の挙動のみをまとめたものです。

## 作業ディレクトリ
```bash
mkdir -p /tmp/redir
cd /tmp/redir
```

## 1. `>` による作成・切り詰め
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
echo one > out_trunc.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `out_trunc.txt` が作成され、内容は `one\n`

## 2. `>>` による既存ファイルへの追記
- `Setup`:
```bash
printf "A\n" > out_app.txt
```
- `Command`:
```bash
echo B >> out_app.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `out_app.txt` の内容は `A\nB\n`

## 3. `>>` で新規作成
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
echo C >> out_new.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `out_new.txt` が作成され、内容は `C\n`

## 4. 入力リダイレクトの基本
- `Setup`:
```bash
printf "in1\n" > in1.txt
```
- `Command`:
```bash
cat < in1.txt
```
- `bash`:
  - `stdout`: `in1\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `in1.txt` は `in1\n` のまま

## 5. 入力の多重指定（最後が有効）
- `Setup`:
```bash
printf "first\n" > in1.txt
printf "second\n" > in2.txt
```
- `Command`:
```bash
cat < in1.txt < in2.txt
```
- `bash`:
  - `stdout`: `second\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `in1.txt` と `in2.txt` はどちらも内容不変

## 6. 出力の多重指定（最後が有効）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
echo X > out1.txt > out2.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`:
    - `out1.txt`: サイズ 0
    - `out2.txt`: 内容 `X\n`

## 7. 入出力の同時指定
- `Setup`:
```bash
printf "mix\n" > in1.txt
```
- `Command`:
```bash
cat < in1.txt > out_mix.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`:
    - `in1.txt`: 内容不変
    - `out_mix.txt`: 内容 `mix\n`

## 8. 出力作成後に入力失敗
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
cat > out_order.txt < missing.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `No such file or directory` 系
  - `exit status`: `1`
  - `files`:
    - `out_order.txt`: 作成され、サイズ 0
    - `missing.txt`: 存在しない

## 9. 入力失敗時は後続の出力先が作成されない
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
cat < missing.txt > out_order.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `No such file or directory` 系
  - `exit status`: `1`
  - `files`:
    - `missing.txt`: 存在しない
    - `out_order.txt`: 作成されない

## 10. 出力先ディレクトリが存在しない
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
echo HI > no_such_dir/out.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `No such file or directory` 系
  - `exit status`: `1`
  - `files`: `no_such_dir/out.txt` は作成されない

## 11. コマンド未発見でもリダイレクトは実行される
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
nosuchcmd > out_nf.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `command not found` 系
  - `exit status`: `127`
  - `files`: `out_nf.txt` は作成され、サイズ 0

## 12. 出力先がディレクトリ
- `Setup`:
```bash
mkdir dir
```
- `Command`:
```bash
echo hi > dir
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `Is a directory` 系
  - `exit status`: `1`
  - `files`: `dir` はディレクトリのまま

## 13. 入力元がディレクトリ
- `Setup`:
```bash
mkdir dir
```
- `Command`:
```bash
cat < dir
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `cat: stdin: Is a directory`
  - `exit status`: `1`
  - `files`: `dir` はディレクトリのまま

## 14. 出力先が書き込み不可
- `Setup`:
```bash
printf "orig\n" > readonly.txt
chmod 444 readonly.txt
```
- `Command`:
```bash
echo hi > readonly.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `Permission denied` 系
  - `exit status`: `1`
  - `files`: `readonly.txt` は内容 `orig\n`、権限 `444` のまま

## 15. 入力元が読み取り不可
- `Setup`:
```bash
printf "secret\n" > noread.txt
chmod 000 noread.txt
```
- `Command`:
```bash
cat < noread.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `Permission denied` 系
  - `exit status`: `1`
  - `files`: `noread.txt` は内容不変、権限 `000` のまま

### これは `\` だから要件外

## 16. heredoc（未クォート）で変数展開
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
VAR=HELLO
cat <<EOF
$VAR
EOF
```
- `bash`:
  - `stdout`: `HELLO\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: なし

## 17. heredoc（クォート）で変数展開なし
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
VAR=HELLO
cat <<'EOF'
$VAR
EOF
```
- `bash`:
  - `stdout`: `$VAR\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: なし

## 18. heredoc + 出力リダイレクト
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
cat <<EOF > out_heredoc.txt
line1
line2
EOF
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `out_heredoc.txt` の内容は `line1\nline2\n`

## 19. heredoc + 入力リダイレクトの優先順位
- `Setup`:
```bash
printf "FILE\n" > in1.txt
```
- `Command`:
```bash
cat <<EOF < in1.txt
HEREDOC
EOF
```
- `bash`:
  - `stdout`: `FILE\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `in1.txt` は内容不変

## 20. コマンドなしのリダイレクト
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
> out_only.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `out_only.txt` が作成され、サイズ 0

## 21. `printf "EOF\n" | cat <<"EOF"`（heredoc が優先）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
printf "EOF\n" | cat <<"EOF"
EOF
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: なし

## 22. `yes X | cat <<'EOF'`（heredoc が優先）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
yes X | cat <<'EOF'
EOF
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: なし

## 23. `cat <<EOF` 入力中に `Ctrl-C`
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
cat <<EOF
abc
# ここで Ctrl-C
```
- `bash`:
  - `stdout`: 空（`cat` は実行されない）
  - `stderr`: 空
  - `exit status`: `130`
  - `files`: なし

## 24. 複数 heredoc（最後が有効）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
cat <<A <<B
from-A
A
from-B
B
```
- `bash`:
  - `stdout`: `from-B\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: なし

## 25. `<<` と `<` の混在（最後が heredoc）
- `Setup`:
```bash
printf "FILE\n" > in_mix.txt
```
- `Command`:
```bash
cat <<A < in_mix.txt <<B
from-A
A
from-B
B
```
- `bash`:
  - `stdout`: `from-B\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `in_mix.txt` は内容不変

## 26. `<` の後に `<<`（heredoc が上書き）
- `Setup`:
```bash
printf "FILE\n" > in_mix.txt
```
- `Command`:
```bash
cat < in_mix.txt <<A
from-A
A
```
- `bash`:
  - `stdout`: `from-A\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `in_mix.txt` は内容不変

## 27. 複数 `<<` の後に `<`（最後が `<`）
- `Setup`:
```bash
printf "FILE\n" > in_mix.txt
```
- `Command`:
```bash
cat <<A <<B < in_mix.txt
from-A
A
from-B
B
```
- `bash`:
  - `stdout`: `FILE\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `in_mix.txt` は内容不変

## 28. パイプ + 複数 heredoc（heredoc が優先、最後が有効）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
printf "pipe\n" | cat <<A <<B
from-A
A
from-B
B
```
- `bash`:
  - `stdout`: `from-B\n`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: なし
