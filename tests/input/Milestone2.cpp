#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C"
{
	#include "minishell.h"
}


TEST(SignalTest, SigintHandlerTest)
{
	rl_done = 0;
	extern volatile sig_atomic_t g_interrupt;
	g_interrupt = 0;
	sigint_handler(SIGINT);
	EXPECT_EQ(g_interrupt, 1);
	EXPECT_EQ(rl_done, 1);
}

TEST(SignalTest, SigquitIsIgnored)
{
	struct sigaction	sa;

	sigaction(SIGQUIT, NULL, &sa);
	EXPECT_TRUE(sa.sa_handler == SIG_IGN || sa.sa_handler == nullptr);
}

static int	call_count = 0;

char	*mock_readline(const char *prompt)
{
	if (call_count == 0)
	{
		sigint_handler(SIGINT); // simulate ctrl-c
		return (strdup(""));
	}
	return (NULL);
}
