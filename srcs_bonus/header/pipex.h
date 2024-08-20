/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:29:52 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/20 17:09:19 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int		fd[2];
	int		status;
	int		infile;
	int		outfile;
	int		outfile_flag;
	pid_t	first_child;
	pid_t	second_child;
	char	**split_path;
}			t_data;
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		free_tab(char **tab);
void		ft_error(t_data *data, char *message, int exit_code);
void		exec_process(char *cmd_argv, char **envp, t_data *data);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			check_path_env(int *index, char **envp);
void		data_init(t_data *data, char **argv);

#endif