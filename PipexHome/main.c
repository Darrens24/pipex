/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:11:37 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/14 16:54:23 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	pipex;

	if (check_errors(ac, av, &pipex))
		return (-1);
	if (!get_data(av, envp, &pipex))
		return (-1);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		dup2(pipex.fd[1], STDOUT_FILENO);
		close_fd(pipex.fd);
		execve(pipex.cmd_path1, pipex.cmd1, envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		dup2(pipex.fd[0], STDIN_FILENO);
		close_fd(pipex.fd);
		dup2(pipex.outfile, STDOUT_FILENO);
		close_fd(pipex.fd);
		execve(pipex.cmd_path2, pipex.cmd2, envp);
	}
	close_and_wait(pipex.fd, pipex.pid1, pipex.pid2);
	free_data(&pipex);
	return (0);
}
