/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:28 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/08 13:41:24 by muidbell         ###   ########.fr       */
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

static void	open_files(char *infile, char *outfile, int *in, int *out)
{
	*in = open(infile, O_RDONLY);
	*out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	files_check(*in, *out);
}

int	main(int ac, char *av[], char *env[])
{
	int		in;
	int		out;
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		fd[2];

	arg_check(ac);
	open_files(av[1], av[4], &in, &out);
	create_pipe(fd);
	pid1 = create_process();
	if (pid1 == 0)
		exec_cmd1(fd, in, av[2], env);
	pid2 = create_process();
	if (pid2 == 0)
		exec_cmd2(fd, out, av[3], env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);
}
