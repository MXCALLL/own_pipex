/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:03:08 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/09 11:48:32 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arg_check(int ac)
{
	if (ac != 5)
	{
		write(2, "Error missing with arguments\n", 29);
		exit(1);
	}
}

void	files_check(int in, int out)
{
	if (in < 0)
	{
		perror("Error opening input file");
		exit(1);
	}
	if (out < 0)
	{
		close(out);
		perror("Error opening input file");
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
