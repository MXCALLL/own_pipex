/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:10:02 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/07 21:52:14 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void	arg_check(int ac);
char	**ft_split(char const *s, char c);

void	exec_cmd1(int *fd, int in, char *cmd, char *env[]);
void	exec_cmd2(int *fd, int out, char *cmd, char *env[]);

void	create_pipe(int *fd);
void	files_check(int in, int out);

#endif