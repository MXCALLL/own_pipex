/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:28 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/11 17:46:58 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	files_check(*in, *out, infile, outfile);
}

static void cleanup_pipes(int **fd, pid_t *pid, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (fd[i])
            free(fd[i]);
        i++;
    }
    free(fd);
    free(pid);
}

int	main(int ac, char *av[], char *env[])
{
	int		files[2];
	// int		status[2];
	pid_t	*pid;
	int		**fd;
	int		i;
	int		j;
	int		cmd_count = ac - 3;
	int		pipe_count = cmd_count - 1;

	arg_check(ac);
	open_files(av[1], av[ac - 1], &files[0], &files[1]);

	fd = malloc(sizeof(int) * pipe_count);
	pid = malloc(sizeof(int) * cmd_count);
	if(!fd || !pid)
	{
		write(2,"malloc fails\n",14);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipe_count)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			cleanup_pipes(fd, pid, i);
			exit(EXIT_FAILURE);
		}
		create_pipe(fd[i]);
		i++;
	}
	i = 0;
	j = 2;
	while(i < cmd_count)
	{
		pid[i] = create_process();
		if (pid[i] == 0)
		{
			if(i == 0)
			{
				exec_first_cmd(fd[i], files[0], av[j],env);
			}
			else if (i == cmd_count - 1)
			{
				exec_last_cmd(fd[i - 1], files[1], av[j], env);
			}
			else
			{
				exec_middle_cmd(fd[i - 1], fd[i], av[j], env);
			}
		}
		i++;
		j++;
	}

	// cleanup_pipes(fd, pid, pipe_count);

	// pid[0] = create_process();
	// if (pid[0] == 0)
	// 	exec_cmd1(fd, files[0], av[2], env);

	// pid[1] = create_process();
	// if (pid[1] == 0)
	// 	exec_cmd2(fd, files[1], av[3], env);
	// close(files[0]);
	// close(files[1]);
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid[0], &status[0], 0);
	// waitpid(pid[1], &status[1], 0);
	// if (WIFEXITED(status[1]))
	// 	return (WEXITSTATUS(status[1]));
	// else if (WIFEXITED(status[0]))
	// 	return (WEXITSTATUS(status[0]));
	return (0);
}
