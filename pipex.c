/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:28 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/05 19:40:28 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char *av[], char *env[])
{
	char		*in;
	int			fd1;
	int			fd2;
	int			out;

	if (ac != 5)
	{
		write(2,"Error missing with arguments",28);
		return (1);
	}

	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening input file");
		return (1);
	}
	fd2 = open(av[4], O_WRONLY | O_CREAT,0644);
	if (fd2 < 0)
	{
		close(fd1);
		perror("Error opening input file");
		return (1);
	}

}
