/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:11:37 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/16 12:55:57 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_data	pipex;
	
	if (check_errors(ac, av, &pipex))
		return (-1);
	allocate_data(ac, envp, &pipex);
	if (get_data(ac, av, &pipex))
		return (-1);
	pipex.i = 0;
	while (pipex.i < (ac - 4)) //on s'arrete avant le dernier, autre process 
	{
		mid_child(&pipex, envp);
		close_fd(pipex.fd[pipex.i]);
		pipex.i++;
	}
	waitpid(pipex.pid[0], 0, 0);
	waitpid(pipex.pid[1], 0, 0);
	//end_child(&pipex, envp);
	/*pipex.pid1 = fork();
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
	free_data(&pipex);*/
	return (0);
}
