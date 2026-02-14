# Unset Test Cases (bash)

## 1. 引数なし `unset`
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
unset
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `shell`: 継続する

## 2. 既存変数の削除（基本）
- `Setup`:
```bash
export U_A=hello
```
- `Command`:
```bash
unset U_A
env | grep '^U_A=' || echo "U_A missing"
```
- `bash`:
  - `stdout`: `U_A missing`
  - `stderr`: 空
  - `exit status`: `0`
  - `env`: `U_A` が存在しない

## 3. `_` 始まり識別子
- `Setup`:
```bash
export _U_A=1
```
- `Command`:
```bash
unset _U_A
env | grep '^_U_A=' || echo "_U_A missing"
```
- `bash`:
  - `stdout`: `_U_A missing`
  - `stderr`: 空
  - `exit status`: `0`
  - `env`: `_U_A` が存在しない

## 4. 未定義変数の削除
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
unset U_NO_SUCH_VAR
```
- `bash`:
  - `stdout`: 空
  - `stderr`: 空
  - `exit status`: `0`
  - `shell`: 継続する

## 5. 複数引数（すべて有効）
- `Setup`:
```bash
export U1=1
export U2=2
```
- `Command`:
```bash
unset U1 U2
env | grep '^U1=' || echo "U1 missing"
env | grep '^U2=' || echo "U2 missing"
```
- `bash`:
  - `stdout`: `U1 missing` と `U2 missing`
  - `stderr`: 空
  - `exit status`: `0`
  - `env`: `U1` と `U2` が存在しない

## 6. 不正識別子（先頭数字）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
unset 1BAD
```
- `bash`:
  - `stdout`: 空
  - `stderr`: unset: `1BAD': not a valid identifier
  - `exit status`: `1`
  - `shell`: 継続する

## 7. 不正識別子（`=` を含む）
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
unset A=B
```
- `bash`:
  - `stdout`: 空
  - `stderr`: unset: `A=B': not a valid identifier
  - `exit status`: `1`
  - `shell`: 継続する

## 8. 有効 + 不正の混在引数
- `Setup`:
```bash
export U_OK=1
```
- `Command`:
```bash
unset U_OK 1BAD
env | grep '^U_OK=' || echo "U_OK missing"
```
- `bash`:
  - `stdout`: `U_OK missing`
  - `stderr`: unset: `1BAD': not a valid identifier
  - `exit status`: `1`
  - `env`: `U_OK` は存在しない

## 9. パイプ左辺の `unset`
- `Setup`:
```bash
export U_P=1
```
- `Command`:
```bash
unset U_P | cat
echo "U_P=$U_P"
```
- `bash`:
  - `stdout`: `U_P=1`
  - `stderr`: 空
  - `exit status`: `0`
  - `shell`: 継続する（親シェル環境は変化しない）

## 10. パイプ右辺の `unset`
- `Setup`:
```bash
export U_Q=1
```
- `Command`:
```bash
echo hi | unset U_Q
echo "U_Q=$U_Q"
```
- `bash`:
  - `stdout`: `U_Q=1`
  - `stderr`: 空
  - `exit status`: `0`
  - `shell`: 継続する（親シェル環境は変化しない）

## 11. 入力リダイレクト失敗時
- `Setup`:
```bash
: # なし
```
- `Command`:
```bash
unset U_Z < missing_unset_test_file
```
- `bash`:
  - `stdout`: 空
  - `stderr`: `bash: missing_unset_test_file: No such file or directory`
  - `exit status`: `1`
  - `shell`: 継続する

## 12. 出力リダイレクト併用
- `Setup`:
```bash
export U_OUT=1
```
- `Command`:
```bash
unset U_OUT > out.txt
wc -c < out.txt
echo "U_OUT=$U_OUT"
```
- `bash`:
  - `stdout`: `0`、`U_OUT=`
  - `stderr`: 空
  - `exit status`: `0`
  - `files`: `out.txt` が作成され、サイズ 0
  - `env`: `U_OUT` が存在しない
