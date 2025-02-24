/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:10:02 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/19 15:03:30 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>

void	arg_check(int ac);
char	**ft_split(char const *s, char c);
void	exec_cmd1(int *fd, int in, char *cmd, char *env[]);
void	exec_cmd2(int *fd, int out, char *cmd, char *env[]);
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
void	ft_putstr_fd(char *s, int fd);

#endif