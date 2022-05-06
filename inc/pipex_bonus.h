/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <erickngooh@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:50:38 by engooh            #+#    #+#             */
/*   Updated: 2022/05/06 18:54:40 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# define FIRST_CMD 0
# define MIDLLE_CMD 1
# define LAST_CMD 2

typedef struct t_pipe
{
	pid_t	*pid;
	int		prev;
	int		fd[2];
	char	**cmd;
	int		status;
	char	**envp;
	int		infile;
	int		outfile;
}	t_pipe;

char	*get_next_line(int fd);
int		set_here_doc(char *limiter);
void	execute_cmd(t_pipe *p, char *cmd);
void	get_path_cmd(t_pipe *p, char *cmd);
void	print_error(t_pipe *p, char *str, char *msg, int exit_code);
void	redir(t_pipe *p, int stdin, int stdout);
void	open_file(t_pipe *p, char *f1, char *f2, int here_doc);
#endif