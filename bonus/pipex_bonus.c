/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:28 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/17 21:14:08 by muidbell         ###   ########.fr       */
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
	if (*in < 0)
		perror("pipex: infile");
	if (*out < 0)
		perror("pipex: outfile");
}

int main(int ac, char *av[], char *env[])
{
    int     i;
    t_pipex px;

    px.cmd_count = ac - 3;
    px.pipe_count = ac - 4;
    arg_check(ac);
    open_files(av[1], av[ac - 1], &px.infile, &px.outfile);
    px.pipes = malloc(sizeof(int *) * px.pipe_count);
    if (!px.pipes)
    {
        write(2, "Malloc fail\n", 12);
        close_in_out(px.infile, px.outfile);
        exit(1);
    }

    i = 0;
    while (i < px.pipe_count)
    {
        px.pipes[i] = malloc(sizeof(int) * 2);
        if (!px.pipes[i])
        {
            cleanup_pipes(px.pipes, NULL, i);
            close_in_out(px.infile, px.outfile);
            exit(1);
        }
        create_pipe(px.pipes[i]);
        i++;
    }

    px.pids = malloc(sizeof(pid_t) * px.cmd_count);
    if (!px.pids)
    {
        cleanup_pipes(px.pipes, NULL, px.pipe_count);
        close_in_out(px.infile, px.outfile);
        exit(1);
    }

	i = 0;
	while(i < px.cmd_count - 1)
	{
		px.pids[i] =  create_process();
		if (px.pids[i] == 0)
		{
			close_unused_pipes(&px, i);
			if(i == 0)
				exec_first(px.pipes[0], px.infile, av[2], env);
			else
				exec_middle(px.pipes[i-1], px.pipes[i], av[i+2], env);
		}
		i++;
	}

	px.pids[i] = create_process();
	if (px.pids[i] == 0)
	{
		close_unused_pipes(&px, i);
		exec_last(px.pipes[px.pipe_count - 1], px.outfile, av[ac - 2], env);
		exit(0);
	}
	i = 0;
	while (i < px.pipe_count)
	{
		close(px.pipes[i][0]);
	    close(px.pipes[i][1]);
	    i++;
	}
	i = 0;
	while (i < px.cmd_count)
	{
		waitpid(px.pids[i], &px.status, 0);
	    i++;
	}

	cleanup_pipes(px.pipes, px.pids, px.pipe_count);
	close_in_out(px.infile, px.outfile);

	if(WIFEXITED(px.status))
	{
		return (WEXITSTATUS(px.status));
	}
	return (1);
}
