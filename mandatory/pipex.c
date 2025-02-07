/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:28 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/07 19:49:30 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *env[])
{
	int		in;
	int		out;
	int		id1;
	int		id2;
	int		fd[2];

	arg_check(ac);

	in = open(av[1], O_RDONLY);
	out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	files_check(in, out);
	if(pipe(fd) == -1)
	{
		close(out);
		close(in);
		write(1,"Error Pipe\n",11);
		exit (1);
	}

	id1 = fork();
	if(id1 == -1)
	{
		write(1,"fork fails\n",11);
		return (1);
	}

	if (id1 == 0)
	{
		close(fd[0]);
		dup2(in,0);
		close(in);
		dup2(fd[1],1);
		close(fd[1]);
		execve("/bin/wc", ft_split(av[2],' '), env);
		perror("error");
		exit(1);
	}

	id2 = fork();
	if(id2 == -1)
	{
		write(1,"fork 2 fails\n",13);
		return (1);
	}

	if (id2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(out,1);
		close(out);
		execve("/bin/cat",ft_split(av[3], ' '), env);
		perror("error");
		exit(1);
	}

	close(fd[0]);
	close(fd[1]);
	int status;
	wait(&status);
	exit(0);
}
