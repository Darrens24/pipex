/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:17:50 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/19 18:15:06 by eleleux          ###   ########.fr       */
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	free_tab(pipex->splitted_path);
	while (pipex->cmd[i])
		i++;
	while (j < (i - 1))
		free_tab(pipex->cmd[j++]);
}

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	wait_pids(int *pid, int ac)
{
	int	i;

	i = 0;
	while (i < (ac - 4))
	{
		waitpid(pid[i], 0, 0);
		i++;
	}
}
