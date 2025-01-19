/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:43:18 by pvilchez          #+#    #+#             */
/*   Updated: 2023/09/14 19:02:50 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_lib.h"

void	error(char *text)
{
	perror(text);
	exit(EXIT_FAILURE);
}

void	free_str_list(char **str_list)
{
	int		i;

	i = 0;
	while (str_list[i])
	{
		free(str_list[i]);
		i++;
	}
	free(str_list);
}

char	*find_path(char *command, char **envp)
{
	char	**path_list;
	char	*path_root;
	char	*final_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	path_list = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		path_root = ft_strjoin(path_list[i], "/");
		final_path = ft_strjoin(path_root, command);
		free(path_root);
		if (access(final_path, F_OK) == 0)
		{
			free_str_list(path_list);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_str_list(path_list);
	return (0);
}

void	exec_comm(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	path = find_path(command[0], envp);
	if (!path)
	{
		free_str_list(command);
		error("Path error");
	}
	if (execve(path, command, envp) == -1)
		error("Error during execution");
}
