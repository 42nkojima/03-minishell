/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2025/12/14 00:00:00 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// 終了ステータス
# define EXIT_SUCCESS 0
# define EXIT_GENERAL_ERROR 1
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_NOT_EXECUTABLE 126
# define EXIT_SIGNAL_BASE 128

// ファイルディスクリプタ
# define FD_STDIN 0
# define FD_STDOUT 1
# define FD_STDERR 2

// ファイルパーミッション
# define FILE_PERMISSION 0644

// システムコール戻り値
# define SYSCALL_ERROR -1
# define SYSCALL_SUCCESS 0

#endif
