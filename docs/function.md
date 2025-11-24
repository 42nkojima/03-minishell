
---

## 🧭 目次

1. **readline関連**
2. **出力・メモリ**
3. **ファイル操作**
4. **プロセス管理**
5. **シグナル処理**
6. **パス・環境変数**
7. **ファイルステータス**
8. **exec 系**
9. **パイプ・dup**
10. **ディレクトリ操作**
11. **TTY・端末関連**
12. **termcap関連**

---

# 1️⃣ readline 系

### `readline(const char *prompt)`

* 標準入力から1行読み取る（プロンプト表示付き）
* 結果は動的に確保され、`free()`が必要。

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char *line = readline("minishell> ");
    if (line && *line)
        add_history(line);
    printf("You typed: %s\n", line);
    free(line);
}
```

---

### `rl_clear_history()`

* readlineの履歴を全消去。

```c
rl_clear_history();
```

---

### `rl_on_new_line()`

* 新しい行に移動する準備（readlineの内部状態更新）

```c
rl_on_new_line();
```

---

### `rl_replace_line(const char *text, int clear_undo)`

* 現在の入力行を置き換える。

```c
rl_replace_line("new input", 1);
rl_redisplay();
```

---

### `rl_redisplay()`

* 現在の入力行を再描画。

```c
rl_redisplay();
```

---

### `add_history(const char *line)`

* 入力行を履歴に追加。

```c
add_history(line);
```

---

# 2️⃣ 出力・メモリ

### `printf`, `write`

```c
printf("Hello %s\n", "world");
write(1, "Hello\n", 6);  // 1 = stdout
```

---

### `malloc`, `free`

```c
char *s = malloc(10);
strcpy(s, "hi");
free(s);
```

---

# 3️⃣ ファイル操作

### `open`, `read`, `write`, `close`

```c
#include <fcntl.h>
#include <unistd.h>

int fd = open("file.txt", O_RDONLY);
char buf[100];
int n = read(fd, buf, 100);
write(1, buf, n);
close(fd);
```

---

### `access`

ファイルの存在・権限をチェック。

```c
if (access("/bin/ls", X_OK) == 0)
    printf("can execute ls\n");
```

---

# 4️⃣ プロセス管理

### `fork`, `wait`, `waitpid`

```c
pid_t pid = fork();
if (pid == 0)
    execlp("ls", "ls", NULL);
else
    waitpid(pid, NULL, 0);
```

---

### `wait3`, `wait4`

* `waitpid`の拡張版でリソース使用情報も取得できる。

---

# 5️⃣ シグナル関連

### `signal`, `sigaction`

```c
#include <signal.h>
#include <stdio.h>

void handler(int sig) { printf("Got signal %d\n", sig); }

int main() {
    signal(SIGINT, handler);
    while (1);
}
```

---

### `sigemptyset`, `sigaddset`

```c
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGINT);
```

---

### `kill`

プロセスにシグナル送信。

```c
kill(pid, SIGTERM);
```

---

# 6️⃣ パス・環境変数

### `getcwd`, `chdir`

```c
char buf[1024];
getcwd(buf, sizeof(buf));
printf("Current dir: %s\n", buf);
chdir("/tmp");
```

---

### `getenv`

環境変数を取得。

```c
printf("PATH=%s\n", getenv("PATH"));
```

---

# 7️⃣ ファイルステータス

### `stat`, `lstat`, `fstat`

```c
#include <sys/stat.h>
struct stat s;
stat("a.out", &s);
printf("Size: %ld\n", s.st_size);
```

---

### `unlink`

ファイル削除。

```c
unlink("temp.txt");
```

---

# 8️⃣ exec 系

### `execve`

```c
char *argv[] = {"ls", "-l", NULL};
char *envp[] = {NULL};
execve("/bin/ls", argv, envp);
```

---

# 9️⃣ パイプ・dup

### `pipe`, `dup`, `dup2`

```c
int fd[2];
pipe(fd);
if (fork() == 0) {
    dup2(fd[1], 1); // stdoutをpipeへ
    execlp("ls", "ls", NULL);
} else {
    char buf[100];
    read(fd[0], buf, 100);
    printf("Output: %s\n", buf);
}
```

---

# 🔟 ディレクトリ操作

### `opendir`, `readdir`, `closedir`

```c
#include <dirent.h>
DIR *d = opendir(".");
struct dirent *e;
while ((e = readdir(d)))
    printf("%s\n", e->d_name);
closedir(d);
```

---

# 11️⃣ TTY・端末関連

### `isatty`

```c
if (isatty(0))
    printf("Input is a terminal\n");
```

---

### `ttyname`, `ttyslot`

```c
printf("tty: %s\n", ttyname(0));
```

---

### `ioctl`

デバイス制御（端末設定など）。

```c
#include <sys/ioctl.h>
#include <unistd.h>

int rows, cols;
struct winsize ws;
ioctl(0, TIOCGWINSZ, &ws);
printf("%d x %d\n", ws.ws_row, ws.ws_col);
```

---

# 12️⃣ termcap 系 (行編集関連)

### `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

端末制御ライブラリ（カーソル移動など）。

```c
#include <term.h>
#include <curses.h>

tgetent(NULL, getenv("TERM"));
char *cm = tgetstr("cm", NULL); // cursor move
char *move = tgoto(cm, 10, 5);
tputs(move, 1, putchar);
```

---

## termios構造体とは

`termios`は、**端末（ターミナル）の動作を制御する設定を格納する構造体**です。端末の入出力の振る舞いを細かく設定できます。

## 関数の解説

### `tcgetattr(int fd, struct termios *term)`
- 端末の**現在の設定を取得**する関数
- `fd`: ファイルディスクリプタ（`STDIN_FILENO` = 標準入力 = 0）
- `term`: 設定を格納する構造体へのポインタ

### `tcsetattr(int fd, int optional_actions, const struct termios *term)`
- 端末の**設定を変更**する関数
- `TCSANOW`: 変更を**即座に**適用する
  - 他のオプション: `TCSADRAIN`（出力完了後）、`TCSAFLUSH`（出力完了後+入力破棄）

## termios構造体の主要メンバー

```c
struct termios {
    tcflag_t c_iflag;   // 入力フラグ
    tcflag_t c_oflag;   // 出力フラグ
    tcflag_t c_cflag;   // 制御フラグ
    tcflag_t c_lflag;   // ローカルフラグ ← 今回使用
    cc_t c_cc[NCCS];    // 制御文字
};
```

## `c_lflag`（ローカルフラグ）

端末の**ローカルな振る舞い**を制御するフラグ群です。

主なフラグ：
- `ECHO`: 入力文字をエコー表示
- `ECHOE`: バックスペースで文字削除
- `ECHOK`: Killで行削除
- **`ECHOCTL`**: **制御文字を`^C`形式で表示**
- `ICANON`: カノニカルモード（行単位入力）
- `ISIG`: シグナル生成を有効化


---
# 🧩 まとめ表（カテゴリ別）

| カテゴリ    | 主な関数                        |
| ------- | --------------------------- |
| 入力      | readline系                   |
| 出力・メモリ  | printf, malloc, free, write |
| ファイル    | open, read, close, access   |
| プロセス    | fork, execve, wait系         |
| シグナル    | signal, sigaction, kill     |
| 環境      | getenv, getcwd, chdir       |
| ファイル情報  | stat, unlink                |
| パイプ     | pipe, dup, dup2             |
| ディレクトリ  | opendir, readdir, closedir  |
| 端末      | ioctl, isatty, ttyname      |
| termcap | tgetent, tputs など           |

---
