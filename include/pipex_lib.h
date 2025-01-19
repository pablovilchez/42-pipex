/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:44:30 by pvilchez          #+#    #+#             */
/*   Updated: 2023/09/14 18:59:14 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_LIB_H
# define PIPEX_LIB_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../assets/libft/libft.h"

/* Mandatory*/
void	error(char *text);
void	free_str_list(char **str_list);
char	*find_path(char *command, char **envp);
void	exec_comm(char *argv, char **envp);

/* Bonus*/
void	bonus_syntax_error(void);
int		open_file(char *argv, int i);
int		read_line(char **line);

#endif