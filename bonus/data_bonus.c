/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:17:36 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/17 13:24:50 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (envp[i][j] == 'P')
			if (envp[i][j + 1] == 'A')
				if (envp[i][j + 2] == 'T')
					if (envp[i][j + 3] == 'H')
						return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*join_valid_path(t_data *pipex, int k)
{
	int		i;
	int		j;
	char	*valid;

	i = 0;
	j = 0;
	while (pipex->splitted_path[i])
	{
		j = 0;
		while (pipex->cmd[j])
		{
			valid = ft_strjoin(pipex->splitted_path[i],
					pipex->cmd[k][0]);
			if (access(valid, R_OK) == 0)
				return (valid);
			free(valid);
			j++;
		}
		i++;
	}
	ft_printf("Error\nCommand not found\n");
	return (0);
}

int	get_data(int ac, char **av, t_data *pipex)
{
	int	i;
	int	j;

	pipex->cmd = malloc(sizeof(char *) * (ac - 2));
	i = 0;
	j = 2;
	while (i < (ac - 3))
		pipex->cmd[i++] = ft_split(av[j++], ' ');
	pipex->cmd[i] = NULL;
	pipex->cmd_path = malloc(sizeof(char *) * (ac - 2));
	i = -1;
	while (++i < (ac - 3))
	{
		pipex->cmd_path[i] = join_valid_path(pipex, i);
		if (!pipex->cmd_path[i])
			return (1);
	}
	pipex->cmd_path[i] = NULL;
	return (0);
}

void	allocate_data(int ac, char **envp, t_data *pipex)
{
	int		size;
	int		i;

	pipex->global_path = get_path(envp);
	pipex->splitted_path = ft_split_slash(pipex->global_path, ':');
	size = ac - 3;
	pipex->pid = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		pipex->pid[i] = 0;
		i++;
	}
	pipex->fd = malloc(sizeof(int *) * (ac - 4));
	i = 0;
	while (i < (ac - 4))
		pipex->fd[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < size - 1)
	{
		pipe(pipex->fd[i]);
		i++;
	}
}
