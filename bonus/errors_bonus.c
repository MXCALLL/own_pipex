/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:03:08 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/11 17:17:10 by muidbell         ###   ########.fr       */
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

void	files_check(int in, int out, char *infile, char *outfile)
{
	if (in < 0)
	{
		printf("pipex: %s: No such file or directory\n",infile);
		exit(0);
	}
	if (out < 0)
	{
		printf("pipex: %s: %s\n",outfile,strerror(errno));
		exit(0);
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
	tmp = NULL;
}
