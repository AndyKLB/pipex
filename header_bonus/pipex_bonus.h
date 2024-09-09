/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:29:52 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/29 17:23:11 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int		nb_cmd;
	int		nb_children;
	int		**fd;
	int		status;
	int		infile;
	int		outfile;
	int		index_first_child;
	int		index_last_child;
	int		index_children_begin;
	int		index_first_pipe;
	int		index_pid_children;
	pid_t	first_child;
	pid_t	*middle_children;
	pid_t	last_child;
	char	**split_path;
}			t_data;
void		ft_putstr_fd(char *s, int fd);
void		*ft_calloc(size_t nmemb, size_t size);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		free_tab(char **tab);
void		ft_error(t_data *data, char *message, int exit_code);
void		exec_process(char *cmd_argv, char **envp, t_data *data, int flag);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			check_path_env(int *index, char **envp);
void		ft_free_pipe_fd(t_data *data, int index);
void		data_init(t_data *data, char **argv, int argc);
int			malloc_pipe_fd(t_data *data);
void		ft_piping_and_fork_first_child(t_data *data);

void		ft_forking(t_data *data);

#endif