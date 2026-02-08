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
	g_signal_status = 0;
	sigint_handler(SIGINT);
	EXPECT_EQ(g_signal_status, SIGINT);
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
