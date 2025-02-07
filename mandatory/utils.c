/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:49:34 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/07 21:52:03 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd1(int *fd, int in, char *cmd, char *env[])
{
	close(fd[0]);
	dup2(in, 0);
	close(in);
	dup2(fd[1], 1);
	close(fd[1]);
	execve("/bin/wc", ft_split(cmd, ' '), env);
	perror("error");
	exit(1);
}

void	exec_cmd2(int *fd, int out, char *cmd, char *env[])
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(out, 1);
	close(out);
	execve("/bin/cat", ft_split(cmd, ' '), env);
	perror("error");
	exit(1);
}

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		write(1, "Error Pipe\n", 11);
		exit(1);
	}
}
