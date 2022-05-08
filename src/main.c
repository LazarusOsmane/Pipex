/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:40:57 by engooh            #+#    #+#             */
/*   Updated: 2022/05/08 11:20:30 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	open_file(t_pipe *p, char *f1, char *f2, int here_doc)
{
	if (!here_doc)
	{
		p->infile = open(f1, O_RDONLY);
		if (p->infile < 0)
			print_error(p, f1, strerror(errno), -1);
		p->outfile = open(f2, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	else
	{
		p->infile = set_here_doc(f1);
		p->outfile = open(f2, O_WRONLY | O_CREAT | O_APPEND, 0664);
	}
	if (p->outfile < 0)
		print_error(p, f2, strerror(errno), -1);
}

void	child_process(t_pipe *p, char *cmd, int flag, int i)
{
	p->pid[i] = fork();
	if (p->pid[i] < 0)
		return ;
	if (!p->pid[i])
	{
		if (flag == FIRST_CMD)
			redir(p, p->infile, p->fd[1]);
		if (flag == MIDLLE_CMD)
			redir(p, p->prev, p->fd[1]);
		if (flag == LAST_CMD)
			redir(p, p->prev, p->outfile);
		while (p->fd[1] > 2)
			close(p->fd[1]--);
		execute_cmd(p, cmd);
		exit(0);
	}
	else
		p->prev = p->fd[0];
}

void	pipex(t_pipe *p, char **cmd)
{
	int	i;

	if (pipe(p->fd) < 0)
		return ;
	i = 0;
	child_process(p, cmd[i], FIRST_CMD, i);
	while (cmd[++i + 2])
	{
		if (pipe(p->fd) < 0)
			return ;
		child_process(p, cmd[i], MIDLLE_CMD, i);
	}
	child_process(p, cmd[i], LAST_CMD, i);
	while (p->fd[1] > 2)
		close(p->fd[1]--);
	i = -1;
	while (p->pid[++i] && waitpid(p->pid[i], &p->status, 0))
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
	print_error(p, NULL, NULL, p->status);
}

int	set_here_doc(char *limiter)
{
	int		fd;
	char	*buf;

	fd = open("/tmp/.here_doc", O_RDONLY | O_WRONLY | O_CREAT, 0777);
	if (!fd)
		return (-1);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			exit(1);
		if (!ft_strncmp(buf, limiter, ft_strlen(limiter)))
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	close(fd);
	free(buf);
	return (open("/tmp/.here_doc", O_RDONLY));
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	p;

	p.cmd = NULL;
	p.pid = NULL;
	p.envp = envp;
	if (ac != 5)
		return (1);
	open_file(&p, av[1], av[ac - 1], 0);
	p.pid = calloc(ac - 2, sizeof(pid_t));
	if (!p.pid)
		return (0);
	pipex(&p, av + 2);
	return (0);
}
