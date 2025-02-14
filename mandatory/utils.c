/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:49:34 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/14 14:58:15 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*total_alloc;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_alloc = malloc(s1_len + s2_len + 1);
	if (total_alloc == NULL)
		return (NULL);
	ft_memcpy(total_alloc, s1, s1_len);
	ft_memcpy(total_alloc + s1_len, s2, s2_len);
	total_alloc[s1_len + s2_len] = '\0';
	return (total_alloc);
}

char	*valid_cmd(char **dirs, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (free_array(dirs), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (free_array(dirs), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_array(dirs), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*cmd_path(char *cmd, char **env)
{
	char	*path;
	char	*valid;
	char	**dirs;

	if (!cmd || !env)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (NULL);
	path = *env + 5;
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	valid = valid_cmd(dirs, cmd);
	if (valid)
		return (valid);
	write(2,"pipex: Command Not found\n",25);
	return (free_array(dirs),NULL);
}

void	exec_cmd1(int *fd, int in, char *cmd, char *env[])
{
	char	**cmdf;
	char	*path;

	cmdf = ft_split(cmd, ' ');
	if (!cmdf)
		exit(EXIT_FAILURE);
	close(fd[0]);
	if (dup2(in, 0) < 0)
	{
		free_array(cmdf);
		exit(1);
	}
	close(in);
	dup2(fd[1], 1);
	close(fd[1]);
	path = cmd_path(cmdf[0], env);
	if (!path)
	{
		free_array(cmdf);
		exit(127);
	}
	execve(path, cmdf, env);
	free(path);
	free_array(cmdf);
}

void	exec_cmd2(int *fd, int out, char *cmd, char *env[])
{
	char	**cmdf;
	char	*path;

	cmdf = ft_split(cmd, ' ');
	if (!cmdf)
		exit(EXIT_FAILURE);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	if (dup2(out, 1) < 0)
	{
		free_array(cmdf);
		exit(1);
	}
	close(out);
	path = cmd_path(cmdf[0], env);
	if (!path)
	{
		free_array(cmdf);
		exit(127);
	}
	execve(path, cmdf, env);
	free(path);
	free_array(cmdf);
}
