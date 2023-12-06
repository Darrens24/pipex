/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_.h	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/19 10:19:26 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

//	Structures	//

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	*global_path;
	char	**splitted_path;
	char	***cmd;
	char	**cmd_path;
	int		*pid;
	int		**fd;
	int		i;
	char	*delimiter;
	int		fd_buffer[2];
	char	*buffer;
}				t_data;

//	Errors	//

int		check_errors(int ac, char **av, t_data *pipex);
int		doc_errors(int ac, char **av, t_data *pipex);

//	Cmd Path	//

char	*get_path(char **envp);
char	**ft_split_slash(char const *s, char c);
char	*join_valid_path(t_data *pipex, int k);
int		get_data(int ac, char **av, t_data *pipex);

//	Utils //

void	free_tab(char **tab);
void	free_data(t_data *pipex);
void	close_fd(int fd[2]);
void	wait_pids(int *pid, int ac);
void	free_tabtab(char ***tab);

//	Bonus Multipipe //

void	allocate_data(int ac, char **envp, t_data *pipex);
void	mid_child(t_data *pipex, char **envp);
void	early_child(t_data *pipex, char **envp);
void	end_child(t_data *pipex, char **envp);

//	Bonus Heredoc	//

int		docdoc(t_data *pipex, int ac, char **av, char **envp);
int		get_doc_data(int ac, char **av, t_data *pipex);
void	doc_child(t_data *pipex, int fd[2], char **envp);
char	*line_in_delimiter(char **av);
void	doc_stdin(t_data *pipex);
void	early_doc(t_data *pipex, char **envp);

#endif
