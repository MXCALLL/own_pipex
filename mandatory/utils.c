/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:49:34 by muidbell          #+#    #+#             */
/*   Updated: 2025/02/08 18:17:22 by muidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*total_alloc;
	size_t		s1_len;
	size_t		s2_len;

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static char	*cmd_path(char *cmd, char **env)
{
    char	*path;
    char	**dirs;
    char	*full_path;
    char    *tmp;
    int		i;

    if (!cmd || !env)
        return (NULL);
    // Handle absolute or relative paths
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    // Get PATH from environment
    while (*env && ft_strncmp(*env, "PATH=", 5))
        env++;
    if (!*env)
        return (NULL);
    // Split and check directories
    path = *env + 5;
    dirs = ft_split(path, ':');
    if (!dirs)
        return (NULL);
    i = 0;
    while (dirs[i])
    {
        tmp = ft_strjoin(dirs[i], "/");
        if (!tmp)
        {
            free_array(dirs);
            return (NULL);
        }
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!full_path)
        {
            free_array(dirs);
            return (NULL);
        }
        if (access(full_path, F_OK | X_OK) == 0)
        {
            free_array(dirs);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_array(dirs);
    return (NULL);
}

void	exec_cmd1(int *fd, int in, char *cmd, char *env[])
{
	char	**cmdf;
	char	*path;

	cmdf = ft_split(cmd, ' ');
	if(!cmdf)
	{
		perror("Split failed");
		exit(1);
	}
	close(fd[0]);
	dup2(in, 0);
	close(in);
	dup2(fd[1], 1);
	close(fd[1]);
	path = cmd_path(cmdf[0],env);
	if (!path)
	{
		free_array(cmdf);
		perror("Command not found");
		exit(1);
	}
	execve(path, cmdf, env);
	free(path);
	free_array(cmdf);
	perror("Exceve 1 failed");
	exit(1);
}

void	exec_cmd2(int *fd, int out, char *cmd, char *env[])
{
	char	**cmdf;
	char	*path;

	cmdf = ft_split(cmd, ' ');
	if(!cmdf)
	{
		perror("Split failed");
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(out, 1);
	close(out);
	path = cmd_path(cmdf[0],env);
	if (!path)
	{
		free_array(cmdf);
		write(2,"Command not found\n",18);
		exit(1);
	}
	execve(path, cmdf, env);
	free(path);
	free_array(cmdf);
	perror("Exceve 2 failed");
	exit(1);
}

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		write(2, "Error Pipe\n", 11);
		exit(1);
	}
}
