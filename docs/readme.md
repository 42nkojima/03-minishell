# MiniShell


``` mermaid
graph LR
    Start["🚀 ユーザー入力<br/>(readline)"] --> Input["📥 Input<br/>- Show prompt<br/>- Add history"]

    Input --> Parse["📝 Parsing<br/>- Quotes処理<br/>- 環境変数展開<br/>- パイプ分割<br/>- リダイレクト解析"]

    Parse --> CheckBuiltin{組み込み<br/>コマンド?}

    CheckBuiltin -->|Yes| Builtin["🔧 Built-in実行<br/>echo, cd, pwd<br/>export, unset, env, exit"]
    CheckBuiltin -->|No| PathSearch["🔍 PATH検索"]

    PathSearch --> Fork["⚙️ Fork & Execute<br/>- Child: パイプ/リダイレクト設定<br/>- execve実行"]
    Builtin --> UpdateStatus
    Fork --> Wait["⏳ Parent: 終了待機"]

    Wait --> UpdateStatus["📊 $?更新<br/>終了ステータス保存"]
    UpdateStatus --> Signal["🔔 Signal処理<br/>Ctrl-C/D/\\\\"]
    Signal --> Start

    style Start fill:#FFE5CC,stroke:#FF6B6B,color:#000,stroke-width:2px
    style Input fill:#D6EAF8,stroke:#2980B9,color:#000,stroke-width:2px
    style Parse fill:#FCF3CF,stroke:#F1C40F,color:#000,stroke-width:2px
    style CheckBuiltin fill:#E8DAEF,stroke:#8E44AD,color:#000,stroke-width:2px
    style Builtin fill:#FADBD8,stroke:#C0392B,color:#000,stroke-width:2px
    style PathSearch fill:#D5F5E3,stroke:#27AE60,color:#000,stroke-width:2px
    style Fork fill:#D5F5E3,stroke:#27AE60,color:#000,stroke-width:2px
    style Wait fill:#D5F5E3,stroke:#27AE60,color:#000,stroke-width:2px
    style UpdateStatus fill:#AED6F1,stroke:#1F618D,color:#000,stroke-width:2px
    style Signal fill:#FFE5CC,stroke:#FF6B6B,color:#000,stroke-width:2px
```

### 機能別カテゴリ

``` mermaid
graph TD
    A["🎯 Minishell 全体構成"]

    A --> B1["📥 Input/Output Layer"]
    A --> B2["📝 Parsing Layer"]
    A --> B3["⚙️ Execution Layer"]
    A --> B4["🔧 Built-in Commands"]

    %% Input / Output
    B1 --> B1_1["▪️ Prompt表示と入力取得<br/>(readline)"]
    B1 --> B1_2["▪️ コマンド履歴管理<br/>(add_history)"]
    B1 --> B1_3["▪️ シグナル処理<br/>Ctrl-C: 新行にPrompt<br/>Ctrl-D: 終了<br/>Ctrl-\\\\: 何もしない"]
    B1 --> B1_4["▪️ グローバル変数は最大1つ<br/>(シグナルハンドラ用)"]

    %% Parsing
    B2 --> B2_1["▪️ クォート処理"]
    B2_1 --> B2_1a["シングルクォート: 展開なし"]
    B2_1 --> B2_1b["ダブルクォート: $ のみ展開"]

    B2 --> B2_2["▪️ 環境変数展開"]
    B2_2 --> B2_2a["$VAR → 値"]
    B2_2 --> B2_2b["$? → 終了ステータス"]

    B2 --> B2_3["▪️ パイプ分割 |"]
    B2 --> B2_4["▪️ リダイレクト解析"]
    B2_4 --> B2_4a["入力: &lt;"]
    B2_4 --> B2_4b["出力: &gt;"]
    B2_4 --> B2_4c["追記: &gt;&gt;"]
    B2_4 --> B2_4d["Heredoc: &lt;&lt;"]

    %% Execution
    B3 --> B3_1["▪️ PATH検索と実行<br/>(相対パス/絶対パス対応)"]
    B3 --> B3_2["▪️ リダイレクション実行<br/>(dup2, open, close)"]
    B3 --> B3_3["▪️ パイプライン実行<br/>(pipe, fork, dup2)"]

    %% Built-in Commands
    B4 --> B4_1["▪️ echo -n"]
    B4 --> B4_2["▪️ cd (相対/絶対パスのみ)"]
    B4 --> B4_3["▪️ pwd"]
    B4 --> B4_4["▪️ export"]
    B4 --> B4_5["▪️ unset"]
    B4 --> B4_6["▪️ env (オプション/引数なし)"]
    B4 --> B4_7["▪️ exit"]

    %% スタイル定義
    classDef io fill:#D6EAF8,stroke:#2980B9,color:#000,stroke-width:2px
    classDef parsing fill:#FCF3CF,stroke:#F1C40F,color:#000,stroke-width:2px
    classDef exec fill:#D5F5E3,stroke:#27AE60,color:#000,stroke-width:2px
    classDef builtin fill:#FADBD8,stroke:#C0392B,color:#000,stroke-width:2px
    classDef detail fill:#FFFFFF,stroke:#999,color:#000,stroke-width:1px

    class B1,B1_1,B1_2,B1_3,B1_4 io
    class B2,B2_1,B2_1a,B2_1b,B2_2,B2_2a,B2_2b,B2_3,B2_4,B2_4a,B2_4b,B2_4c,B2_4d parsing
    class B3,B3_1,B3_2,B3_3 exec
    class B4,B4_1,B4_2,B4_3,B4_4,B4_5,B4_6,B4_7 builtin
```

### パイプとリダイレクションの実装例

``` mermaid
graph TD
    subgraph Pipe["🔗 パイプ例: cat file.txt | grep pattern | wc -l"]
        P1["cat file.txt<br/>stdin: ファイル<br/>stdout: パイプ1"]
        P2["grep pattern<br/>stdin: パイプ1<br/>stdout: パイプ2"]
        P3["wc -l<br/>stdin: パイプ2<br/>stdout: 画面"]

        P1 --> P2 --> P3
    end

    subgraph Redir["📂 リダイレクション例"]
        R1["command &lt; input.txt<br/>input.txt を stdin に接続"]
        R2["command &gt; output.txt<br/>stdout を output.txt に上書き"]
        R3["command &gt;&gt; output.txt<br/>stdout を output.txt に追記"]
        R4["command &lt;&lt; EOF<br/>ここから EOF まで入力"]
    end

    style P1 fill:#D5F5E3,stroke:#27AE60,color:#000
    style P2 fill:#D5F5E3,stroke:#27AE60,color:#000
    style P3 fill:#D5F5E3,stroke:#27AE60,color:#000
    style R1 fill:#D6EAF8,stroke:#2980B9,color:#000
    style R2 fill:#D6EAF8,stroke:#2980B9,color:#000
    style R3 fill:#D6EAF8,stroke:#2980B9,color:#000
    style R4 fill:#D6EAF8,stroke:#2980B9,color:#000
```

