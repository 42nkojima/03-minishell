/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/10 15:32:11 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// 終了ステータス
typedef enum e_exit_status
{
	EXIT_BUILTIN_MISUSE = 2,
	EXIT_CMD_NOT_EXECUTABLE = 126,
	EXIT_CMD_NOT_FOUND = 127,
	EXIT_SIGNAL_BASE = 128
}	t_exit_status;

// ファイルディスクリプタ
typedef enum e_fd
{
	FD_STDIN = 0,
	FD_STDOUT = 1,
	FD_STDERR = 2
}	t_fd;

// ファイルパーミッション
# define FILE_PERMISSION 0644

// システムコール戻り値
# define SYSCALL_ERROR -1
# define SYSCALL_SUCCESS 0
# define HEREDOC_FD_UNSET -1

#endif
