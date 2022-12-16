/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2022/12/15 15:08:25 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	int		infile;		//ok
	int		outfile;	//ok
	char	*global_path;	//ok
	char	**splitted_path;//ok
	char	***cmd;	//ok
	char	**cmd_path;	//ok
	int		*pipex;	//ok
	int		*pid;	//ok
	int		**fd;	//ok
	int		i;
}				t_data;

//Errors
int		check_errors(int ac, char **av, t_data *pipex);

//Cmd Path
char	*get_path(char **envp);
char	**ft_split_slash(char const *s, char c);
int		get_data(int ac, char **av, t_data *pipex);

//Utils
void	free_tab(char **tab);
void	free_data(t_data *pipex);
void	close_fd(int fd[2]);
void	wait_pids(int pid1, int pid2);
void	close_and_wait(int fd[2], int pid1, int pid2);

//Bonus
void	allocate_data(int ac, char **envp, t_data *pipex);
void	mid_child(t_data *pipex, char **envp);
void	end_child(t_data *pipex, char **envp);

#endif
