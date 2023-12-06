/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:12:40 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/22 14:59:08 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_doc_data(int ac, char **av, t_data *pipex)
{
	int	i;
	int	j;

	pipex->cmd = malloc(sizeof(char *) * (ac - 3));
	i = 0;
	j = 3;
	while (i < (ac - 4))
		pipex->cmd[i++] = ft_split(av[j++], ' ');
	pipex->cmd[i] = NULL;
	pipex->cmd_path = malloc(sizeof(char *) * (ac - 3));
	i = -1;
	while (++i < (ac - 4))
	{
		pipex->cmd_path[i] = join_valid_path(pipex, i);
		if (!pipex->cmd_path[i])
			return (1);
	}
	pipex->cmd_path[i] = NULL;
	pipex->i = 0;
	pipex->delimiter = line_in_delimiter(av);
	if (pipe(pipex->fd_buffer) < 0)
		return (ft_printf("Error\nPipe failed\n"));
	return (0);
}

void	doc_child(t_data *pipex, int fd[2], char **envp)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		dup2(pipex->outfile, STDOUT_FILENO);
		execve(pipex->cmd_path[1], pipex->cmd[1], envp);
	}
}

void	doc_stdin(t_data *pipex)
{
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		pipex->buffer = get_next_line(STDIN_FILENO);
		if (!pipex->buffer || !ft_strncmp(pipex->buffer, pipex->delimiter,
				(ft_strlen(pipex->delimiter))))
		{
			free(pipex->buffer);
			break ;
		}
		ft_putstr_fd(pipex->buffer, pipex->fd_buffer[1]);
		free(pipex->buffer);
	}
	close (pipex->fd_buffer[1]);
}

int	doc_child_and_free(t_data *pipex, int ac, char **av, char **envp)
{
	if (doc_errors(ac, av, pipex))
		return (-1);
	allocate_data(ac, envp, pipex);
	if (get_doc_data(ac, av, pipex))
		return (free_data(pipex), -1);
	doc_stdin(pipex);
	dup2(pipex->fd_buffer[0], STDIN_FILENO);
	pipex->i = 0;
	while (pipex->i < (ac - 4))
	{
		mid_child(pipex, envp);
		close_fd(pipex->fd[pipex->i]);
		pipex->i++;
	}
	wait_pids(pipex->pid, ac);
	free_data(pipex);
	free_tab(pipex->cmd_path);
	return (0);
}
