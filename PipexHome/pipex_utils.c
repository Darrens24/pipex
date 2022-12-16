/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:15:13 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/14 12:46:57 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_data(t_data *pipex)
{
	free_tab(pipex->splitted_path);
	free_tab(pipex->cmd1);
	free_tab(pipex->cmd2);
	free(pipex->cmd_path1);
	free(pipex->cmd_path2);
}

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	wait_pids(int pid1, int pid2)
{
	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);
}

void	close_and_wait(int fd[2], int pid1, int pid2)
{
	close_fd(fd);
	wait_pids(pid1, pid2);
}
