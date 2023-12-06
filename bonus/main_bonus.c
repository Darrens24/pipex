/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:16:34 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/22 14:30:13 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	mid_child(t_data *pipex, char **envp)
{
	pipex->pid[pipex->i] = fork();
	early_child(pipex, envp);
	if (pipex->cmd[pipex->i + 1] != NULL)
	{
		pipex->pid[pipex->i + 1] = fork();
		dup2(pipex->fd[pipex->i][0], STDIN_FILENO);
		close_fd(pipex->fd[pipex->i]);
		if (pipex->pid[pipex->i + 1] == 0)
		{
			if (pipex->cmd[pipex->i + 2] != NULL)
			{
				dup2(pipex->fd[pipex->i + 1][1], STDOUT_FILENO);
				close_fd(pipex->fd[pipex->i + 1]);
			}
			else
			{
				dup2(pipex->outfile, STDOUT_FILENO);
				close_fd(pipex->fd[pipex->i]);
			}
			execve(pipex->cmd_path[pipex->i + 1],
				pipex->cmd[pipex->i + 1], envp);
		}
	}
}

void	early_child(t_data *pipex, char **envp)
{
	if (pipex->pid[pipex->i] == 0)
	{
		dup2(pipex->fd[pipex->i][1], STDOUT_FILENO);
		close_fd(pipex->fd[pipex->i]);
		execve(pipex->cmd_path[pipex->i], pipex->cmd[pipex->i], envp);
	}
}

char	*line_in_delimiter(char **av)
{
	char	*limiter;
	char	*temp;

	temp = ft_strdup(av[2]);
	limiter = ft_strjoin(temp, "\n");
	free(temp);
	return (limiter);
}

int	main(int ac, char **av, char **envp)
{
	t_data	pipex;

	if (ac > 1 && !ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		doc_child_and_free(&pipex, ac, av, envp);
		return (0);
	}
	if (check_errors(ac, av, &pipex))
		return (-1);
	allocate_data(ac, envp, &pipex);
	if (get_data(ac, av, &pipex))
		return (free_data(&pipex), -1);
	pipex.i = 0;
	dup2(pipex.infile, STDIN_FILENO);
	while (pipex.i < (ac - 4))
	{
		mid_child(&pipex, envp);
		close_fd(pipex.fd[pipex.i]);
		pipex.i++;
	}
	wait_pids(pipex.pid, ac);
	free_data(&pipex);
	free_tab(pipex.cmd_path);
	return (0);
}
