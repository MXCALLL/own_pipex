/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:10:02 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/17 20:56:48 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_pipex {
    int     cmd_count;         // *Number of commands
    int     pipe_count;        // *Number of pipes
    int     **pipes;           // *2D array for all pipes
    pid_t   *pids;             // *Array of all process IDs
    int     status;           // Array for exit statuses
    int     infile;            // *Input file descriptor
    int     outfile;           // *Output file descriptor
    char    **cmds;            // Array of command strings
    char    **env;             // Environment variables
} t_pipex;

void	arg_check(int ac);
char	**ft_split(char const *s, char c);
void	exec_first(int *pipe, int in, char *cmd, char *env[]);
void	exec_last(int *pipe, int out, char *cmd, char *env[]);
void    exec_middle(int *prev_pipe, int *curr_pipe, char *cmd, char *env[]);
void	create_pipe(int *fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_array(char **array);
char	*valid_cmd(char **dirs, char *cmd);

// *** strjoin helpers ***
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);


void	cleanup_pipes(int **pipes, pid_t *pids, int count_pipe);
void	close_in_out(int in, int out);
void    close_unused_pipes(t_pipex *px, int current);

#endif