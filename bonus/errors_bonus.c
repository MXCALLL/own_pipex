/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:03:08 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/17 20:56:00 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	arg_check(int ac)
{
	if (ac < 5)
	{
		write(2, "Error missing with arguments\n", 29);
		exit(1);
	}
}

void	free_array(char **array)
{
	char	**tmp;

	tmp = array;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(array);
}

void	cleanup_pipes(int **pipes, pid_t *pids, int count_pipe)
{
    int i;

    i = 0;
	if (pipes)
	{
    	while (i < count_pipe)
    	{
    	    if (pipes[i])
    	        free(pipes[i]);
    	    i++;
    	}
		free(pipes);
	}
	if (pids)
		free(pids);
}

void	close_in_out(int in, int out)
{
	if (in)
		close(in);
	if (out)
		close(out);
}
