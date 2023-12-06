/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:15:04 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/19 18:05:56 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_errors(int ac, char **av, t_data *pipex)
{
	if (ac != 5)
		return (ft_printf("Error\nProgram needs 4 arguments\n"));
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		return (ft_printf("Error\nInfile opening failed\n"));
	if (access(av[1], F_OK | R_OK | W_OK) < 0)
		return (ft_printf("Error\nInfile permissions denied\n"));
	pipex->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		return (ft_printf("Error\nOutfile opening failed\n"));
	if (access(av[ac - 1], R_OK | W_OK) < 0)
		return (ft_printf("Error\nOutfile permissions denied\n"));
	return (0);
}
