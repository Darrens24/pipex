/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:26:01 by darrensdev        #+#    #+#             */
/*   Updated: 2022/12/14 12:56:10 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_errors(int ac, char **av, t_data *pipex)
{
	if (ac != 5)
		return (printf("Error\nProgram needs 4 arguments\n"));
	if (access(av[1], F_OK | R_OK | W_OK) < 0)
		return (printf("Error\nFile permissions denied\n"));
	pipex->infile = open(av[1], O_RDWR);
	if (pipex->infile < 0)
		return (printf("Error\nInfile opening failed\n"));
	pipex->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC);
	if (access(av[4], R_OK | W_OK) < 0)
		return (printf("Error\nFile permissions denied\n"));
	if (pipex->outfile < 0)
		return (printf("Error\nOutfile opening failed\n"));
	pipex->pipex = pipe(pipex->fd);
	if (pipex->pipex < 0)
		return (printf("Error\nPipe failed\n"));
	return (0);
}
