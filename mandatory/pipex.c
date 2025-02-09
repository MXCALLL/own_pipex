/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:28 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/09 22:37:26 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	create_process(void)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		write(1, "fork fails\n", 11);
		exit(1);
	}
	return (id);
}

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		write(2, "Error Pipe\n", 11);
		exit(1);
	}
}

static void	open_files(char *infile, char *outfile, int *in, int *out)
{
	*in = open(infile, O_RDONLY);
	*out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	files_check(*in, *out);
}

int	main(int ac, char *av[], char *env[])
{
	int		files[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	arg_check(ac);
	open_files(av[1], av[4], &files[0], &files[1]);
	create_pipe(fd);
	pid1 = create_process();
	if (pid1 == 0)
		exec_cmd1(fd, files[0], av[2], env);
	pid2 = create_process();
	if (pid2 == 0)
		exec_cmd2(fd, files[1], av[3], env);
	close(files[0]);
	close(files[1]);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
