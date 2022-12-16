/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:32:37 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/16 13:12:02 by darrensdev       ###   ########.fr       */
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
	pipex->cmd_path = malloc(sizeof(char *) * (ac - 3));
	i = -1;
	while (++i < (ac - 3))
	{
		pipex->cmd_path[i] = ft_strjoin(pipex->splitted_path[4],
			pipex->cmd[i][0]);
		if (access(pipex->cmd_path[i], F_OK) < 0)
		{
			free_data(pipex);
			return (printf("Error\nCommand not found\n"));
		}
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
	pipex->pipex = malloc(sizeof(int) * (size - 1));
	i = 0;
	while (i < size - 1)
	{
		pipe(pipex->fd[i]);
		i++;
	}
}

void	mid_child(t_data *pipex, char **envp)
{
	pipex->pid[pipex->i] = fork();
	if (pipex->pid[pipex->i] == 0)
	{
		dup2(pipex->fd[pipex->i][1], STDOUT_FILENO);
		close_fd(pipex->fd[pipex->i]);
		execve(pipex->cmd_path[pipex->i], pipex->cmd[pipex->i], envp);
	}
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