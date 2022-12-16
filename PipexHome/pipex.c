/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:32:37 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/14 16:56:00 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	get_data(char **av, char **envp, t_data *pipex)
{	
	pipex->global_path = get_path(envp);
	pipex->splitted_path = ft_split_slash(pipex->global_path, ':');
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	pipex->cmd_path1 = ft_strjoin(pipex->splitted_path[4], pipex->cmd1[0]);
	pipex->cmd_path2 = ft_strjoin(pipex->splitted_path[4], pipex->cmd2[0]);
	if (access(pipex->cmd_path1, F_OK) < 0
		|| access(pipex->cmd_path2, F_OK) < 0)
	{
		free_data(pipex);
		printf("Error\nCommand not found\n");
		return (0);
	}
	return (1);
}
