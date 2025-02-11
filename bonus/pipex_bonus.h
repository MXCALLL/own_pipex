/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:10:02 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/11 13:06:40 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

void	arg_check(int ac);
char	**ft_split(char const *s, char c);

void	exec_first_cmd(int *fd, int in, char *cmd, char *env[]);
// exec_middle_cmd;
void	exec_middle_cmd(int *prev_fd, int *curr_fd, char *cmd, char *env[]);
// exec_last_cmd;
void	exec_last_cmd(int *fd, int in, char *cmd, char *env[]);

void	create_pipe(int *fd);
void	files_check(int in, int out, char *infile, char *outfile);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_array(char **array);
char	*valid_cmd(char **dirs, char *cmd);

// *** strjoin helpers ***
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif