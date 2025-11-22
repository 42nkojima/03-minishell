# MiniShell 実装ガイド

## 目次

1. [プロジェクト構成](#プロジェクト構成)
2. [段階的実装順序](#段階的実装順序)
2. [依存関係](#依存関係)
---

## プロジェクト構成

```
minishell
  docs
  libs
    libft
  tests
  includes
  src
    utils
    input
    parse
    exec
    builtin
  objs
  Makefile

```

---

## 段階的実装順序

---
# **📌 Milestone 1 — 基本の対話ループ（REPL）**

### **目標**

* minishell が起動し、プロンプトを表示し、入力できる
* `readline()` と `add_history()` が動く

### **実装**

* プロンプト表示
* `readline("minishell$ ")`
* EOF(ctrl-D) で終了
* 空行処理

### **動作確認**

```
minishell$ hello
minishell$
minishell$ <ctrl-D>
```

---

# **📌 Milestone 2 — シグナルが Bash と同じように動く**

### **目標**

* ctrl-C: 新しい行のプロンプトが出る
* ctrl-: 何も起きない
* ctrl-D: 終了

### **実装**

* `sigaction`
* `g_signal_status`（グローバルは1つだけ）

### **動作確認**

```
minishell$ <ctrl-C>
minishell$ (新しいプロンプト)
```

Bash と同じ動きをすること。

---

# **📌 Milestone 3 — 最小のパーサ（スペース区切りだけ）**

### **目標**

* 入力をスペースで分割してコマンド配列を作成
* 引用符などはまだなし

### **動作確認**

```
minishell$ ls -l /tmp
→ ["ls", "-l", "/tmp"]
```

実行はまだしない。

---

# **📌 Milestone 4 — PATH によるコマンド実行（最小）**

### **目標**

* fork + execve で実行できる
* PATH 探索あり

### **動作確認**

```
minishell$ ls
(結果が表示される)

minishell$ echo 問題なし
bash の echo は外部コマンドではないので失敗する→OK
※ echo builtin は後で実装する
```

---

# **📌 Milestone 5 — シングル/ダブルクォート実装**

### **目標**

* `'abc def'` → 1トークン
* `"a $PATH b"` → 展開あり
* `'a $PATH b'` → 展開なし

### **動作確認**

```
minishell$ echo "hello $USER"
minishell$ echo 'hello $USER'
```

---

# **📌 Milestone 6 — 環境変数展開（$VAR と $?）**

### **目標**

* `$PATH`, `$HOME`
* `$?`（直前の終了ステータス）

### **動作確認**

```
minishell$ ls
minishell$ echo $?
0

minishell$ cat unknown
minishell$ echo $?
1
```

---

# **📌 Milestone 7 — リダイレクト (<, >, >>, <<)**

### **最初にやる順番**

1. `>` 出力リダイレクト
2. `<` 入力リダイレクト
3. `>>` 追記
4. `<<` ヒアドキュメント（最難関）

### **動作確認**

```
minishell$ echo hello > a.txt
minishell$ cat < a.txt
hello

minishell$ echo test >> a.txt
minishell$ cat a.txt
hello
test

minishell$ cat << EOF
aaa
bbb
EOF
aaa
bbb
```

---

# **📌 Milestone 8 — パイプ（|）**

### **実装順**

1. パイプでコマンド列を分割
2. 各コマンドごとに fork
3. `pipe() + dup2()` で接続

### **動作確認**

```
minishell$ ls | wc -l
```

---

# **📌 Milestone 9 — ビルトイン（外部コマンドと区別が必要）**

順番は簡単なものから：

1. echo (-n)
2. pwd
3. env
4. cd
5. export
6. unset
7. exit（最終的な cleanup も）

### **動作確認**

```
minishell$ echo -n hello
hellominishell$
```

---

# **📌 Milestone 10 — 全体統合テスト**

### テスト項目例

#### ✔ quoting

```
echo "a b ' c"
```

#### ✔ pipe + redirect

```
ls -l | grep minishell > out.txt
```

#### ✔ builtin in pipeline

```
export X=123 | cat
```

#### ✔ signal while running command

```
sleep 5   ← ctrl-C
```

#### ✔ $? が更新される

```
ls not_exist
echo $?
```

---

### 依存関係
``` mermaid
graph LR
    subgraph "🧱 基本環境"
        A1["signal handler登録"]
        A2["readline初期化"]
        A3["mainループ構築"]
    end

    subgraph "🟦 入出力層"
        B1["プロンプト表示"]
        B2["履歴管理"]
        B3["Ctrl-C / D / \\ の制御"]
    end

    subgraph "🟨 構文解析層"
        C1["トークン分割（空白・パイプなど）"]
        C2["クォート処理（シングル、ダブル）"]
        C3["環境変数展開（$VAR, $?）"]
        C4["リダイレクト解析（&lt;, &gt;, &lt;&lt;, &gt;&gt;）"]
        C5["構文ツリー構築"]
    end

    subgraph "🟩 実行層"
        D1["PATH検索とexecve実行"]
        D2["リダイレクト設定 (dup2, open)"]
        D3["パイプ処理 (pipe, fork, dup2)"]
        D4["終了ステータスの管理"]
    end

    subgraph "🟥 ビルトイン層"
        E1["echo (-n)"]
        E2["cd"]
        E3["pwd"]
        E4["export/unset/env"]
        E5["exit"]
    end

    %% 依存関係
    A3 --> B1
    B1 --> C1
    C1 --> C2
    C2 --> C3
    C3 --> C4
    C4 --> C5
    C5 --> D1
    D1 --> D2
    D2 --> D3
    D3 --> D4
    D4 --> E1

```

```mermaid
graph TD
    %% カラー定義
    classDef io fill:#D6EAF8,stroke:#2980B9,color:#000;
    classDef parsing fill:#FCF3CF,stroke:#F1C40F,color:#000;
    classDef exec fill:#D5F5E3,stroke:#27AE60,color:#000;
    classDef builtin fill:#FADBD8,stroke:#C0392B,color:#000;

    %% フェーズ1: 入出力の基礎
    A1["① readlineで入力を受け取る"]:::io
    A2["② プロンプトを表示"]:::io
    A3["③ 履歴機能 (add_history)"]:::io
    A4["④ シグナルハンドリング (Ctrl-C / D / \\)"]:::io
    A5["⑤ グローバル変数1個以内でsignal処理"]:::io

    %% フェーズ2: パーサ（字句・構文）
    B1["⑥ トークナイズ（スペース分割・引用符考慮）"]:::parsing
    B2["⑦ シングル/ダブルクォート処理"]:::parsing
    B3["⑧ 環境変数展開 ($VAR, $?)"]:::parsing
    B4["⑨ リダイレクト (<, >, <<, >>) を抽出"]:::parsing
    B5["⑩ パイプ (|) を分解"]:::parsing
    B6["⑪ コマンド構造体(command struct)を生成"]:::parsing

    %% フェーズ3: 実行
    C1["⑫ PATH探索 (環境変数PATHから実行ファイル検索)"]:::exec
    C2["⑬ fork/execveでコマンドを実行"]:::exec
    C3["⑭ dup2, pipe でリダイレクト・パイプ接続"]:::exec
    C4["⑮ 終了ステータス($?)の管理"]:::exec

    %% フェーズ4: ビルトインコマンド
    D1["⑯ echo (-n)"]:::builtin
    D2["⑰ cd (相対・絶対パス)"]:::builtin
    D3["⑱ pwd"]:::builtin
    D4["⑲ export"]:::builtin
    D5["⑳ unset"]:::builtin
    D6["㉑ env"]:::builtin
    D7["㉒ exit"]:::builtin

    %% 依存関係 (フェーズ間)
    A1 --> A2 --> A3 --> A4 --> A5
    A5 --> B1
    B1 --> B2 --> B3 --> B4 --> B5 --> B6
    B6 --> C1 --> C2 --> C3 --> C4
    C4 --> D1
    D1 --> D2 --> D3 --> D4 --> D5 --> D6 --> D7

    %% クロス依存（シグナル処理は実行にも関与）
    A4 --> C2
    %% 環境変数展開はPATH探索に必要
    B3 --> C1
    %% $? はパース側の変数展開に影響
    C4 --> B3
```
