# 変数展開 / 終了ステータス テストケース

## 前提

```sh
export FOO=bar
export FOO_1=baz
```

- `export` が未実装の間は、現在のコードで起動時に `FOO=bar` / `FOO_1=baz` を注入して確認する。

## 1. 基本展開

### 入力
```sh
echo $FOO
echo "$FOO"
echo '$FOO'
```

### 出力
```text
bar
bar
$FOO
```

## 2. 連結とクォート

### 入力
```sh
echo "foo"$FOO
echo "foo"$FOO"baz"
echo foo'bar'baz
echo "a|b"
```

### 出力
```text
foobar
foobarbaz
foobarbaz
a|b
```

## 3. #61 変数名ルール（A: [A-Za-z_][A-Za-z0-9_]*）

### 入力
```sh
echo $FOO_1
echo $FOO_1zzz
echo "$FOO_1zzz"
echo ${FOO}_1
```

### 出力
```text
baz


${FOO}_1
```

- `A` ルールでは `$FOO_1zzz` は `FOO_1zzz` 全体を変数名として扱う（未定義なら空）。
- `${FOO}` は未対応なのでリテラルのまま。

## 4. 不正な `$` の扱い（未対応機能はリテラル維持）

### 入力
```sh
echo foo$
echo $1
```

### 出力
```text
foo$
$1
```

## 5. 終了ステータス `$?`

### 入力
```sh
true
echo $?
false
echo $?
```

### 出力
```text
0
1
```

### 補足（`;` 非対応）

- `false; $?` / `false; "$?"` はこの minishell では `;` をサポートしていないため未対応。
- 代わりに以下で同等確認する。

```sh
false
echo $?
echo "$?"
```
