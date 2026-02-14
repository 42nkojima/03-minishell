/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_unset.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 00:00:00 by test              #+#    #+#             */
/*   Updated: 2026/02/14 00:00:00 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <cstring>
#include <string>

extern "C"
{
#include "minishell.h"
#include "builtin.h"
}

// Helper function to create a test environment
static t_env *create_test_env()
{
	t_env *env = NULL;
	set_env(&env, (char *)"PATH", (char *)"/usr/bin:/bin");
	set_env(&env, (char *)"HOME", (char *)"/home/user");
	set_env(&env, (char *)"USER", (char *)"testuser");
	return env;
}

// Test fixture for env/unset tests
class EnvUnsetTest : public ::testing::Test
{
protected:
	t_env *env;

	void SetUp() override
	{
		env = NULL;
	}

	void TearDown() override
	{
		free_env_list(env);
		env = NULL;
	}
};

// ============================================================================
// builtin_unset tests
// ============================================================================

TEST_F(EnvUnsetTest, UnsetNoArguments)
{
	env = create_test_env();
	char *argv[] = {(char *)"unset", NULL};

	int result = builtin_unset(argv, &env);
	EXPECT_EQ(result, 0);

	// Environment should remain unchanged
	EXPECT_NE(get_env_value(env, (char *)"PATH"), nullptr);
	EXPECT_NE(get_env_value(env, (char *)"HOME"), nullptr);
}

TEST_F(EnvUnsetTest, UnsetExistingVariable)
{
	env = create_test_env();
	set_env(&env, (char *)"TEST_VAR", (char *)"test_value");

	EXPECT_STREQ(get_env_value(env, (char *)"TEST_VAR"), "test_value");

	char *argv[] = {(char *)"unset", (char *)"TEST_VAR", NULL};
	int result = builtin_unset(argv, &env);

	EXPECT_EQ(result, 0);
	EXPECT_EQ(get_env_value(env, (char *)"TEST_VAR"), nullptr);
}

TEST_F(EnvUnsetTest, UnsetVariableStartingWithUnderscore)
{
	env = create_test_env();
	set_env(&env, (char *)"_TEST", (char *)"value");

	EXPECT_STREQ(get_env_value(env, (char *)"_TEST"), "value");

	char *argv[] = {(char *)"unset", (char *)"_TEST", NULL};
	int result = builtin_unset(argv, &env);

	EXPECT_EQ(result, 0);
	EXPECT_EQ(get_env_value(env, (char *)"_TEST"), nullptr);
}

TEST_F(EnvUnsetTest, UnsetNonExistentVariable)
{
	env = create_test_env();

	char *argv[] = {(char *)"unset", (char *)"NONEXISTENT", NULL};
	int result = builtin_unset(argv, &env);

	EXPECT_EQ(result, 0);
	// Should not crash or cause errors
}

TEST_F(EnvUnsetTest, UnsetInvalidIdentifierStartingWithDigit)
{
	env = create_test_env();

	char *argv[] = {(char *)"unset", (char *)"1BAD", NULL};
	int result = builtin_unset(argv, &env);

	EXPECT_EQ(result, 1);
}

TEST_F(EnvUnsetTest, UnsetInvalidIdentifierWithEquals)
{
	env = create_test_env();

	char *argv[] = {(char *)"unset", (char *)"A=B", NULL};
	int result = builtin_unset(argv, &env);

	EXPECT_EQ(result, 1);
}

TEST_F(EnvUnsetTest, UnsetAfterVariableIsHidden)
{
	env = create_test_env();
	set_env(&env, (char *)"TEST", (char *)"value");

	// Unset once
	char *argv[] = {(char *)"unset", (char *)"TEST", NULL};
	builtin_unset(argv, &env);
	EXPECT_EQ(get_env_value(env, (char *)"TEST"), nullptr);

	// Setting it again should make it visible
	set_env(&env, (char *)"TEST", (char *)"newvalue");
	EXPECT_STREQ(get_env_value(env, (char *)"TEST"), "newvalue");
}

// ============================================================================
// env_to_array tests
// ============================================================================

TEST_F(EnvUnsetTest, EnvToArrayBasic)
{
	env = create_test_env();

	char **envp = env_to_array(env);
	ASSERT_NE(envp, nullptr);

	// Count entries
	int count = 0;
	while (envp[count])
		count++;

	EXPECT_EQ(count, 3); // PATH, HOME, USER

	// Verify format
	bool found_path = false;
	bool found_home = false;
	bool found_user = false;

	for (int i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			found_path = true;
		if (strncmp(envp[i], "HOME=", 5) == 0)
			found_home = true;
		if (strncmp(envp[i], "USER=", 5) == 0)
			found_user = true;
	}

	EXPECT_TRUE(found_path);
	EXPECT_TRUE(found_home);
	EXPECT_TRUE(found_user);

	free_envp(envp);
}

TEST_F(EnvUnsetTest, EnvToArrayAfterUnset)
{
	env = create_test_env();
	set_env(&env, (char *)"TO_REMOVE", (char *)"value");

	// Verify it's in the array
	char **envp1 = env_to_array(env);
	int count1 = 0;
	while (envp1[count1])
		count1++;
	EXPECT_EQ(count1, 4); // PATH, HOME, USER, TO_REMOVE
	free_envp(envp1);

	// Unset the variable
	char *argv[] = {(char *)"unset", (char *)"TO_REMOVE", NULL};
	builtin_unset(argv, &env);

	// Verify it's not in the array anymore
	char **envp2 = env_to_array(env);
	int count2 = 0;
	while (envp2[count2])
		count2++;
	EXPECT_EQ(count2, 3); // PATH, HOME, USER (TO_REMOVE is hidden)

	// Make sure TO_REMOVE is not in the array
	for (int i = 0; envp2[i]; i++)
	{
		EXPECT_TRUE(strncmp(envp2[i], "TO_REMOVE=", 10) != 0);
	}

	free_envp(envp2);
}

TEST_F(EnvUnsetTest, EnvToArrayEmptyEnv)
{
	char **envp = env_to_array(NULL);
	ASSERT_NE(envp, nullptr);
	EXPECT_EQ(envp[0], nullptr);
	free_envp(envp);
}

TEST_F(EnvUnsetTest, EnvToArrayWithNullValue)
{
	set_env(&env, (char *)"NO_VALUE", NULL);

	char **envp = env_to_array(env);
	ASSERT_NE(envp, nullptr);

	// Should have one entry with empty value
	EXPECT_NE(envp[0], nullptr);
	EXPECT_STREQ(envp[0], "NO_VALUE=");
	EXPECT_EQ(envp[1], nullptr);

	free_envp(envp);
}

// ============================================================================
// builtin_env tests with VISIBLE/HIDDEN filtering
// ============================================================================

TEST_F(EnvUnsetTest, EnvCommandBasic)
{
	env = create_test_env();

	char *argv[] = {(char *)"env", NULL};
	int result = builtin_env(argv, env);

	EXPECT_EQ(result, EXIT_SUCCESS);
}

TEST_F(EnvUnsetTest, EnvCommandWithArgument)
{
	env = create_test_env();

	char *argv[] = {(char *)"env", (char *)"somearg", NULL};
	int result = builtin_env(argv, env);

	EXPECT_EQ(result, EXIT_CMD_NOT_FOUND);
}

TEST_F(EnvUnsetTest, EnvCommandAfterUnset)
{
	env = create_test_env();
	set_env(&env, (char *)"VISIBLE_VAR", (char *)"visible");

	// Unset the variable
	char *unset_argv[] = {(char *)"unset", (char *)"VISIBLE_VAR", NULL};
	builtin_unset(unset_argv, &env);

	// Verify it's not returned by get_env_value
	EXPECT_EQ(get_env_value(env, (char *)"VISIBLE_VAR"), nullptr);

	// Env command should also not show it
	char *env_argv[] = {(char *)"env", NULL};
	int result = builtin_env(env_argv, env);
	EXPECT_EQ(result, EXIT_SUCCESS);
}

// ============================================================================
// get_env_value tests
// ============================================================================

TEST_F(EnvUnsetTest, GetEnvValueBasic)
{
	env = create_test_env();

	char *value = get_env_value(env, (char *)"HOME");
	EXPECT_STREQ(value, "/home/user");
}

TEST_F(EnvUnsetTest, GetEnvValueNonExistent)
{
	env = create_test_env();

	char *value = get_env_value(env, (char *)"NONEXISTENT");
	EXPECT_EQ(value, nullptr);
}

TEST_F(EnvUnsetTest, GetEnvValueAfterUnset)
{
	env = create_test_env();
	set_env(&env, (char *)"TO_HIDE", (char *)"secret");

	// Before unset
	EXPECT_STREQ(get_env_value(env, (char *)"TO_HIDE"), "secret");

	// After unset
	char *argv[] = {(char *)"unset", (char *)"TO_HIDE", NULL};
	builtin_unset(argv, &env);

	EXPECT_EQ(get_env_value(env, (char *)"TO_HIDE"), nullptr);
}

// ============================================================================
// set_env tests (to verify it makes variables VISIBLE again)
// ============================================================================

TEST_F(EnvUnsetTest, SetEnvMakesHiddenVariableVisible)
{
	env = create_test_env();
	set_env(&env, (char *)"VAR", (char *)"first");

	// Unset it (makes it HIDDEN)
	char *argv[] = {(char *)"unset", (char *)"VAR", NULL};
	builtin_unset(argv, &env);
	EXPECT_EQ(get_env_value(env, (char *)"VAR"), nullptr);

	// Set it again (should make it VISIBLE)
	set_env(&env, (char *)"VAR", (char *)"second");
	EXPECT_STREQ(get_env_value(env, (char *)"VAR"), "second");

	// Should appear in env_to_array
	char **envp = env_to_array(env);
	bool found = false;
	for (int i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], "VAR=second", 10) == 0)
			found = true;
	}
	EXPECT_TRUE(found);
	free_envp(envp);
}

TEST_F(EnvUnsetTest, SetEnvWithNullValue)
{
	set_env(&env, (char *)"EMPTY", NULL);

	char *value = get_env_value(env, (char *)"EMPTY");
	EXPECT_EQ(value, nullptr);

	// Should still be in the environment list but with NULL value
	t_env *cur = env;
	bool found = false;
	while (cur)
	{
		if (strcmp(cur->key, "EMPTY") == 0)
		{
			found = true;
			EXPECT_EQ(cur->value, nullptr);
			EXPECT_EQ(cur->is_show, VISIBLE);
		}
		cur = cur->next;
	}
	EXPECT_TRUE(found);
}

// ============================================================================
// Integration tests
// ============================================================================

TEST_F(EnvUnsetTest, UnsetMultipleVariablesSequentially)
{
	env = create_test_env();
	set_env(&env, (char *)"VAR1", (char *)"value1");
	set_env(&env, (char *)"VAR2", (char *)"value2");
	set_env(&env, (char *)"VAR3", (char *)"value3");

	// Unset VAR1
	char *argv1[] = {(char *)"unset", (char *)"VAR1", NULL};
	builtin_unset(argv1, &env);
	EXPECT_EQ(get_env_value(env, (char *)"VAR1"), nullptr);
	EXPECT_STREQ(get_env_value(env, (char *)"VAR2"), "value2");
	EXPECT_STREQ(get_env_value(env, (char *)"VAR3"), "value3");

	// Unset VAR2
	char *argv2[] = {(char *)"unset", (char *)"VAR2", NULL};
	builtin_unset(argv2, &env);
	EXPECT_EQ(get_env_value(env, (char *)"VAR1"), nullptr);
	EXPECT_EQ(get_env_value(env, (char *)"VAR2"), nullptr);
	EXPECT_STREQ(get_env_value(env, (char *)"VAR3"), "value3");

	// Verify env_to_array doesn't include hidden variables
	char **envp = env_to_array(env);
	int count = 0;
	while (envp[count])
		count++;

	// Should have PATH, HOME, USER, VAR3 = 4 variables
	EXPECT_EQ(count, 4);
	free_envp(envp);
}

TEST_F(EnvUnsetTest, UnsetAndResetCycle)
{
	env = create_test_env();

	// Set -> Unset -> Set -> Unset
	set_env(&env, (char *)"CYCLE", (char *)"v1");
	EXPECT_STREQ(get_env_value(env, (char *)"CYCLE"), "v1");

	char *argv[] = {(char *)"unset", (char *)"CYCLE", NULL};
	builtin_unset(argv, &env);
	EXPECT_EQ(get_env_value(env, (char *)"CYCLE"), nullptr);

	set_env(&env, (char *)"CYCLE", (char *)"v2");
	EXPECT_STREQ(get_env_value(env, (char *)"CYCLE"), "v2");

	builtin_unset(argv, &env);
	EXPECT_EQ(get_env_value(env, (char *)"CYCLE"), nullptr);
}

// ============================================================================
// Edge case tests
// ============================================================================

TEST_F(EnvUnsetTest, UnsetSpecialVariableUnderscore)
{
	set_env(&env, (char *)"_", (char *)"last_command");

	char *argv[] = {(char *)"unset", (char *)"_", NULL};
	int result = builtin_unset(argv, &env);

	EXPECT_EQ(result, 0);
	EXPECT_EQ(get_env_value(env, (char *)"_"), nullptr);
}

TEST_F(EnvUnsetTest, EnvToArrayOrderIndependent)
{
	set_env(&env, (char *)"Z_VAR", (char *)"z");
	set_env(&env, (char *)"A_VAR", (char *)"a");
	set_env(&env, (char *)"M_VAR", (char *)"m");

	char **envp = env_to_array(env);
	ASSERT_NE(envp, nullptr);

	int count = 0;
	while (envp[count])
		count++;

	EXPECT_EQ(count, 3);

	// Verify all three are present (order doesn't matter for env_to_array)
	bool found_z = false, found_a = false, found_m = false;
	for (int i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], "Z_VAR=", 6) == 0) found_z = true;
		if (strncmp(envp[i], "A_VAR=", 6) == 0) found_a = true;
		if (strncmp(envp[i], "M_VAR=", 6) == 0) found_m = true;
	}

	EXPECT_TRUE(found_z);
	EXPECT_TRUE(found_a);
	EXPECT_TRUE(found_m);

	free_envp(envp);
}

TEST_F(EnvUnsetTest, ComplexScenarioHiddenAndVisible)
{
	// Create environment with mix of visible and hidden variables
	set_env(&env, (char *)"V1", (char *)"visible1");
	set_env(&env, (char *)"V2", (char *)"visible2");
	set_env(&env, (char *)"V3", (char *)"visible3");

	// Hide V2
	char *argv[] = {(char *)"unset", (char *)"V2", NULL};
	builtin_unset(argv, &env);

	// Verify env_to_array only returns V1 and V3
	char **envp = env_to_array(env);
	int count = 0;
	bool found_v1 = false, found_v2 = false, found_v3 = false;

	while (envp[count])
	{
		if (strncmp(envp[count], "V1=", 3) == 0) found_v1 = true;
		if (strncmp(envp[count], "V2=", 3) == 0) found_v2 = true;
		if (strncmp(envp[count], "V3=", 3) == 0) found_v3 = true;
		count++;
	}

	EXPECT_TRUE(found_v1);
	EXPECT_FALSE(found_v2);
	EXPECT_TRUE(found_v3);
	EXPECT_EQ(count, 2);

	free_envp(envp);
}

// ============================================================================
// Memory leak tests
// ============================================================================

TEST_F(EnvUnsetTest, NoMemoryLeakOnMultipleUnsets)
{
	env = create_test_env();

	for (int i = 0; i < 100; i++)
	{
		std::string key = "VAR_" + std::to_string(i);
		std::string value = "value_" + std::to_string(i);
		set_env(&env, (char *)key.c_str(), (char *)value.c_str());
	}

	for (int i = 0; i < 100; i++)
	{
		std::string key = "VAR_" + std::to_string(i);
		char *argv[] = {(char *)"unset", (char *)key.c_str(), NULL};
		builtin_unset(argv, &env);
	}

	// All should be hidden
	char **envp = env_to_array(env);
	int count = 0;
	while (envp[count])
		count++;

	// Should only have the initial 3 (PATH, HOME, USER)
	EXPECT_EQ(count, 3);
	free_envp(envp);
}

TEST_F(EnvUnsetTest, EnvToArrayMultipleCalls)
{
	env = create_test_env();

	// Call env_to_array multiple times
	for (int i = 0; i < 10; i++)
	{
		char **envp = env_to_array(env);
		ASSERT_NE(envp, nullptr);

		int count = 0;
		while (envp[count])
			count++;
		EXPECT_EQ(count, 3);

		free_envp(envp);
	}
}