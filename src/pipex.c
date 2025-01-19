/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:42:05 by pvilchez          #+#    #+#             */
/*   Updated: 2023/09/21 12:57:16 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_lib.h"

void	f_child(char **argv, char **envp, int *pipex_fd)
{
	int	fd_read;

	fd_read = open(argv[1], O_RDONLY, 0777);
	if (fd_read == -1)
		error("Error accessing input file");
	dup2(pipex_fd[1], STDOUT_FILENO);
	dup2(fd_read, STDIN_FILENO);
	close(pipex_fd[0]);
	exec_comm(argv[2], envp);
}

void	f_parent(char **argv, char **envp, int *pipex_fd)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error("Error accessing output file ");
	dup2(pipex_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipex_fd[1]);
	exec_comm(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipex_fd[2];
	pid_t	pid;

	if (argc != 5)
		error("Error.\n Usage: ./pipex file1 command1 command2 file2\n");
	else
	{
		if (pipe(pipex_fd) == -1)
			error("Error: pipe failure");
		pid = fork();
		if (pid == -1)
			error("Error creating child process");
		if (pid == 0)
			f_child(argv, envp, pipex_fd);
		waitpid(pid, NULL, WNOHANG);
		f_parent(argv, envp, pipex_fd);
	}
	return (0);
}
