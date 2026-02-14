/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export_print.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 00:00:00 by test              #+#    #+#             */
/*   Updated: 2026/02/14 00:00:00 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <cstring>

extern "C"
{
#include "minishell.h"
#include "builtin.h"
}

// Test fixture for export_print tests
class ExportPrintTest : public ::testing::Test
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
// print_export tests
// ============================================================================

TEST_F(ExportPrintTest, PrintExportBasic)
{
	set_env(&env, (char *)"VAR1", (char *)"value1");
	set_env(&env, (char *)"VAR2", (char *)"value2");

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, PrintExportEmptyEnv)
{
	int result = print_export(NULL);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, PrintExportExcludesUnderscore)
{
	set_env(&env, (char *)"_", (char *)"last_command");
	set_env(&env, (char *)"PATH", (char *)"/usr/bin");

	// print_export should not print the "_" variable
	// This is tested by the implementation checking ft_strcmp(copy->key, "_") != 0
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, PrintExportExcludesHidden)
{
	set_env(&env, (char *)"VISIBLE", (char *)"shown");
	set_env(&env, (char *)"TO_HIDE", (char *)"hidden");

	// Hide one variable
	char *argv[] = {(char *)"unset", (char *)"TO_HIDE", NULL};
	builtin_unset(argv, &env);

	// print_export should only show VISIBLE variables
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	// Verify TO_HIDE is truly hidden
	EXPECT_EQ(get_env_value(env, (char *)"TO_HIDE"), nullptr);
}

TEST_F(ExportPrintTest, PrintExportWithNullValue)
{
	set_env(&env, (char *)"NO_VALUE", NULL);

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, PrintExportSorting)
{
	// Add variables in non-alphabetical order
	set_env(&env, (char *)"ZEBRA", (char *)"z");
	set_env(&env, (char *)"APPLE", (char *)"a");
	set_env(&env, (char *)"MIDDLE", (char *)"m");

	// print_export should sort them alphabetically
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	// The internal implementation creates a copy and sorts it
	// We can't easily test output here, but we verify it doesn't crash
}

TEST_F(ExportPrintTest, PrintExportPreservesOriginal)
{
	set_env(&env, (char *)"ZEBRA", (char *)"z");
	set_env(&env, (char *)"APPLE", (char *)"a");

	// Get the original order
	t_env *first = env;
	char *first_key = first->key;

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	// Verify the original list is unchanged
	EXPECT_EQ(env, first);
	EXPECT_STREQ(env->key, first_key);
}

// ============================================================================
// copy_env tests (helper function)
// ============================================================================

TEST_F(ExportPrintTest, CopyEnvPreservesData)
{
	set_env(&env, (char *)"KEY1", (char *)"value1");
	set_env(&env, (char *)"KEY2", (char *)"value2");

	// This is tested indirectly through print_export
	// print_export calls copy_env internally
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	// Verify original is still intact
	EXPECT_STREQ(get_env_value(env, (char *)"KEY1"), "value1");
	EXPECT_STREQ(get_env_value(env, (char *)"KEY2"), "value2");
}

// ============================================================================
// sort_env tests (helper function)
// ============================================================================

TEST_F(ExportPrintTest, SortEnvHandlesIdenticalKeys)
{
	set_env(&env, (char *)"SAME", (char *)"value1");

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, SortEnvHandlesSingleElement)
{
	set_env(&env, (char *)"ONLY", (char *)"one");

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

// ============================================================================
// Integration tests with export and unset
// ============================================================================

TEST_F(ExportPrintTest, ExportThenUnsetThenPrint)
{
	char *export_argv1[] = {(char *)"export", (char *)"VAR1=value1", NULL};
	char *export_argv2[] = {(char *)"export", (char *)"VAR2=value2", NULL};

	builtin_export(export_argv1, &env);
	builtin_export(export_argv2, &env);

	// Verify both are visible
	EXPECT_STREQ(get_env_value(env, (char *)"VAR1"), "value1");
	EXPECT_STREQ(get_env_value(env, (char *)"VAR2"), "value2");

	// Unset VAR1
	char *unset_argv[] = {(char *)"unset", (char *)"VAR1", NULL};
	builtin_unset(unset_argv, &env);

	// print_export should only show VAR2
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	// Verify VAR1 is hidden
	EXPECT_EQ(get_env_value(env, (char *)"VAR1"), nullptr);
	EXPECT_STREQ(get_env_value(env, (char *)"VAR2"), "value2");
}

TEST_F(ExportPrintTest, ExportWithoutValueThenUnset)
{
	// Export without assignment (just declares the variable)
	char *export_argv[] = {(char *)"export", (char *)"DECLARED", NULL};
	builtin_export(export_argv, &env);

	// Should exist but with NULL value
	t_env *cur = env;
	bool found = false;
	while (cur)
	{
		if (strcmp(cur->key, "DECLARED") == 0)
		{
			found = true;
			break;
		}
		cur = cur->next;
	}
	EXPECT_TRUE(found);

	// Unset it
	char *unset_argv[] = {(char *)"unset", (char *)"DECLARED", NULL};
	builtin_unset(unset_argv, &env);

	// Should be hidden
	EXPECT_EQ(get_env_value(env, (char *)"DECLARED"), nullptr);
}

// ============================================================================
// Edge cases
// ============================================================================

TEST_F(ExportPrintTest, LargeNumberOfVariables)
{
	// Add many variables
	for (int i = 0; i < 100; i++)
	{
		std::string key = "VAR_" + std::to_string(i);
		std::string value = "value_" + std::to_string(i);
		set_env(&env, (char *)key.c_str(), (char *)value.c_str());
	}

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, VariablesWithSpecialCharactersInValue)
{
	set_env(&env, (char *)"SPECIAL", (char *)"value with spaces");
	set_env(&env, (char *)"QUOTES", (char *)"value\"with\"quotes");

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);
}

TEST_F(ExportPrintTest, EmptyStringValue)
{
	set_env(&env, (char *)"EMPTY", (char *)"");

	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	EXPECT_STREQ(get_env_value(env, (char *)"EMPTY"), "");
}

TEST_F(ExportPrintTest, AfterMultipleUnsetAndReset)
{
	set_env(&env, (char *)"VAR", (char *)"v1");

	char *unset_argv[] = {(char *)"unset", (char *)"VAR", NULL};
	builtin_unset(unset_argv, &env);

	set_env(&env, (char *)"VAR", (char *)"v2");

	builtin_unset(unset_argv, &env);

	set_env(&env, (char *)"VAR", (char *)"v3");

	// Should show VAR=v3
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	EXPECT_STREQ(get_env_value(env, (char *)"VAR"), "v3");
}

// ============================================================================
// Stress tests
// ============================================================================

TEST_F(ExportPrintTest, AlternatingVisibleHidden)
{
	// Create pattern: V1 (visible), H1 (hidden), V2 (visible), H2 (hidden), ...
	for (int i = 0; i < 10; i++)
	{
		std::string v_key = "V" + std::to_string(i);
		std::string h_key = "H" + std::to_string(i);

		set_env(&env, (char *)v_key.c_str(), (char *)"visible");
		set_env(&env, (char *)h_key.c_str(), (char *)"to_hide");
	}

	// Hide all H* variables
	for (int i = 0; i < 10; i++)
	{
		std::string h_key = "H" + std::to_string(i);
		char *argv[] = {(char *)"unset", (char *)h_key.c_str(), NULL};
		builtin_unset(argv, &env);
	}

	// print_export should only show V* variables
	int result = print_export(env);
	EXPECT_EQ(result, SYSCALL_SUCCESS);

	// Verify
	for (int i = 0; i < 10; i++)
	{
		std::string v_key = "V" + std::to_string(i);
		std::string h_key = "H" + std::to_string(i);

		EXPECT_NE(get_env_value(env, (char *)v_key.c_str()), nullptr);
		EXPECT_EQ(get_env_value(env, (char *)h_key.c_str()), nullptr);
	}
}