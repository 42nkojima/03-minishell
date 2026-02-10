# Exit Test Cases (bash)

## 1. 引数なし `exit`
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `shell`: 終了する

## 2. 正の数値引数
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 42
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `42`
  - `shell`: 終了する

## 3. 256 の剰余化
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 256
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `shell`: 終了する

## 4. 負数の扱い
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit -1
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `255`
  - `shell`: 終了する

## 5. `+` 付き数値
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit +12
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `12`
  - `shell`: 終了する

## 6. `long long` 最大値
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 9223372036854775807
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `255`
  - `shell`: 終了する

## 7. 非数値引数
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit abc
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `bash: exit: abc: numeric argument required`
  - `exit status`: `2`
  - `shell`: 終了する

## 8. オーバーフロー数値
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 9223372036854775808
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `bash: exit: 9223372036854775808: numeric argument required`
  - `exit status`: `2`
  - `shell`: 終了する

## 9. 符号のみ引数
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit +
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `bash: exit: +: numeric argument required`
  - `exit status`: `2`
  - `shell`: 終了する

## 10. 引数過多（継続）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 1 2
echo STILL
```
- `bash`:
  - `stdout`: `STILL\n`
  - `stderr`: `bash: exit: too many arguments`
  - `exit status`: `0`（`echo STILL` の結果）
  - `shell`: 継続する

## 11. 非数値 + 追加引数（非数値エラー優先）
- `Setup`:
```bash
cat <<'EOF' > case11.sh
exit abc 2
echo NEVER
EOF
```
- `Command`:
```bash
bash case11.sh
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `case11.sh: line 1: exit: abc: numeric argument required`
  - `exit status`: `2`

## 12. パイプ左辺の `exit`
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 7 | cat
echo AFTER_LEFT
```
- `bash`:
  - `stdout`: `AFTER_LEFT\n`
  - `stderr`: 空
  - `exit status`: `0`（`echo AFTER_LEFT` の結果）
  - `shell`: 継続する

## 13. パイプ右辺の `exit`
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
echo hi | exit 9
echo AFTER_RIGHT
```
- `bash`:
  - `stdout`: `AFTER_RIGHT\n`
  - `stderr`: 空
  - `exit status`: `0`（`echo AFTER_RIGHT` の結果）
  - `shell`: 継続する

## 14. 入力リダイレクト失敗時
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit < missing_exit_test_file
echo AFTER_REDIR_FAIL
```
- `bash`:
  - `stdout`: `AFTER_REDIR_FAIL\n`
  - `stderr`: `bash: missing_exit_test_file: No such file or directory`
  - `exit status`: `0`（`echo AFTER_REDIR_FAIL` の結果）
  - `shell`: 継続する

## 15. 出力リダイレクト併用で終了
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
exit 7 > out.txt
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `7`
  - `files`: `out.txt` が作成され、サイズ 0
  - `shell`: 終了する
