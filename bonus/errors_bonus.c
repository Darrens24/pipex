/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:15:04 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/17 15:13:01 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_errors(int ac, char **av, t_data *pipex)
{
	if (ac < 5)
		return (ft_printf("Error\nAt least 4 arguments required\n"));
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

int	doc_errors(int ac, char **av, t_data *pipex)
{
	if (ac < 6)
		return (ft_printf("Error\nDoc: 5 arguments minimum required\n"));
	pipex->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile < 0)
		return (ft_printf("Error\nOutfile opening failed\n"));
	if (access(av[ac - 1], R_OK | W_OK) < 0)
		return (ft_printf("Error\nOutfile permissions denied\n"));
	return (0);
}
