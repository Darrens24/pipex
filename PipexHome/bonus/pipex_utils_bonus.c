/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:15:13 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/15 14:03:27 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	free_tab(pipex->cmd[0]);
	free(pipex->cmd_path);
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
