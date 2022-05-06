/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <erickngooh@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:37:45 by engooh            #+#    #+#             */
/*   Updated: 2022/05/06 18:52:29 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	redir(t_pipe *p, int stdin, int stdout)
{
	if (stdin < 0 || stdout < 0)
		print_error(p, NULL, NULL, 1);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
}

void	execute_cmd(t_pipe *p, char *cmd)
{
	get_path_cmd(p, cmd);
	if (access(p->cmd[0], F_OK) < 0
		|| !(p->cmd[0][0] == '/'
		|| (p->cmd[0][0] == '.' && p->cmd[0][1] == '/')))
		print_error(p, p->cmd[0], "command not found", 127);
	if (access(p->cmd[0], F_OK) && access(p->cmd[0], X_OK) < 0)
		print_error(p, p->cmd[0], strerror(errno), 126);
	if (execve(p->cmd[0], p->cmd, p->envp) < 0)
		print_error(p, NULL, NULL, 1);
	ft_free_tabs((void **)p->cmd);
	exit(0);
}

void	print_error(t_pipe *p, char *str, char *msg, int exit_code)
{
	char	*s;

	s = NULL;
	unlink("/tmp/.here_doc");
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (str)
		s = ft_strrchr(str, '/');
	if (s && msg)
		ft_printf("bash: %s: %s\n", msg, s + 1);
	else if (!s && msg)
		ft_printf("bash: %s: %s\n", msg, str);
	if (p->cmd)
		ft_free_tabs((void **)p->cmd);
	if (p->pid)
		free(p->pid);
	if (exit_code > 0)
		exit(exit_code);
}

void	get_path_cmd(t_pipe *p, char *cmd)
{
	int		i;
	char	**env;

	i = 0;
	p->cmd = ft_split(cmd, ' ');
	if (access(p->cmd[0], F_OK) < 0)
	{
		while (p->envp && p->envp[i]
			&& !ft_strnstr(p->envp[i], "PATH", ft_strlen("PATH")))
			i++;
		env = ft_split(p->envp[i] + ft_strlen("PATH="), ':');
		cmd = ft_strjoin("/", p->cmd[0]);
		i = -1;
		while (env[++i] && access(p->cmd[0], X_OK) < 0)
		{
			free(p->cmd[0]);
			p->cmd[0] = ft_strjoin(env[i], cmd);
		}
		free(cmd);
		ft_free_tabs((void **)env);
	}
}

char	*get_next_line(int fd)
{
	int		ret;
	char	*line;
	char	buf[2];

	ret = 1;
	line = NULL;
	buf[0] = '\0';
	buf[1] = '\0';
	while (ret && *buf != '\n')
	{
		ret = read(fd, buf, 1);
		if (ret < 0)
		{
			free(line);
			return (NULL);
		}
		if (buf[0])
			line = ft_strjoin_update(line, buf);
	}
	return (line);
}
