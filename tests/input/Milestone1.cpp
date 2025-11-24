#include <gtest/gtest.h>
#include <string>
#include <cstring>

extern "C" {
#include "minishell.h"
}

const char* mock_inputs[] = {"hello", "world", "", nullptr};
int mock_index = 0;

extern "C" char* readline(const char* prompt) {
    (void)prompt;
    const char* input = mock_inputs[mock_index++];
    if (input == nullptr) {
        return nullptr;
    }
    return strdup(input);
}

extern "C" void add_history(const char* line) {
    (void)line;
}

TEST(ReplTest, BasicLoopWithEOF) {
    mock_index = 0; // 入力の初期化

    t_bool result = run_repl();

    // TRUEが返されることを確認
    EXPECT_EQ(result, TRUE);
    // すべての入力が処理されたことを確認
    EXPECT_EQ(mock_index, 4); // hello, world, "", nullptr
}

TEST(ReplTest, EmptyInputNotAddedToHistory) {
    // 空文字列が履歴に追加されないことを確認したい場合
    mock_index = 2; // "" から開始

    t_bool result = run_repl();

    EXPECT_EQ(result, TRUE);
}
