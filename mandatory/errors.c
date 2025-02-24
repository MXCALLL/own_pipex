/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:03:08 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/24 21:40:58 by muidbell         ###   ########.fr       */
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

void	files_check(int in, int out, char *infile, char *outfile)
{
	if (in < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	if (out < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(outfile, 2);
		ft_putstr_fd(": ", 2);
		perror("");
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

void	ft_putchar_fd(char c, int fd)
{
	if (fd > 0)
		write(fd, &c, 1);
}
