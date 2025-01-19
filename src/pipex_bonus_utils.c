/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:11:01 by pvilchez          #+#    #+#             */
/*   Updated: 2023/09/15 11:54:03 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_lib.h"

void	bonus_syntax_error(void)
{
	ft_printf("Error: Bad argument\n");
	ft_printf("Use: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	ft_printf("     ./pipex \"here_doc\" <LIMITER> <cmd1> <cmd2> <...> <file>\n");
	exit(EXIT_SUCCESS);
}

int	open_file(char *file_name, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(file_name, O_RDONLY, 0777);
	if (file == -1)
		error("Error opening file");
	return (file);
}

int	read_line(char **line)
{
	int		i;
	char	c;
	int		try_read;
	char	*read_line;

	i = 0;
	read_line = (char *)malloc(10000);
	if (!read_line)
		return (-1);
	try_read = 0;
	try_read = read(0, &c, 1);
	while (try_read && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			read_line[i] = c;
		i++;
		try_read = read(0, &c, 1);
	}
	read_line[i] = '\n';
	read_line[++i] = '\0';
	*line = read_line;
	free(read_line);
	return (try_read);
}
