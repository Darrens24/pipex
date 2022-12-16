/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2022/12/14 16:54:05 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	*global_path;
	char	**splitted_path;
	char	**cmd1;
	char	**cmd2;
	char	*cmd_path1;
	char	*cmd_path2;
	int		pipex;
	int		pid1;
	int		pid2;
	int		fd[2];
}				t_data;

//Errors
int		check_errors(int ac, char **av, t_data *pipex);

//Cmd Path
char	*get_path(char **envp);
char	**ft_split_slash(char const *s, char c);
int		get_data(char **av, char **envp, t_data *pipex);

//Utils
void	free_tab(char **tab);
void	free_data(t_data *pipex);
void	close_fd(int fd[2]);
void	wait_pids(int pid1, int pid2);
void	close_and_wait(int fd[2], int pid1, int pid2);

#endif
