#include <gtest/gtest.h>
#include "repl.h"

static const char* test_inputs[] = {
    "hello",
    "",
    nullptr // EOF
};
static int input_index = 0;

char* mock_readline(const char* prompt) {
    const char* s = test_inputs[input_index++];
    if (!s) return nullptr; // EOF
    return strdup(s);
}

TEST(REPLTest, BasicLoop) {
    input_index = 0;
    // REPL はループを回すだけ。標準出力は必要に応じてモック
    repl_loop(mock_readline);
    // assert できるのは副作用や履歴など
    // 例: add_history が正しく呼ばれたか
}

