/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:18:36 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/07 18:18:02 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	data_init(t_data *data)
{
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->first_child = 0;
	data->second_child = 0;
	data->status = 0;
	data->infile = 0;
	data->outfile = 0;
	data->split_env = NULL;
}

int	check_envp(char **envp, char **argv)
{
	int	i;

	i = 0;
	if (argv[2][0] == '/' && argv[3][0] == '/')
		return (1);
	else if (!envp[i] || !envp)
		return (0);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (0);
	else
		return (1);
}

void	ft_error(t_data *data, char *message, int argc, int exit_code)
{
	if (argc != 5)
	{
		ft_putstr_fd("bad argument\n", 2);
		ft_putstr_fd("rappel : <infile> <cmd1> <cmd2> <outfile>\n", 2);
	}
	else if (argc == 5 && !message)
		ft_putstr_fd("error env", 2);
	else if (message)
	{
		ft_putstr_fd(message, 2);
	}
	if (data)
	{
		if (data->fd[0] >= 0)
			close(data->fd[0]);
		if (data->fd[1] >= 0)
			close(data->fd[1]);
	}
	exit(exit_code);
}

int	check_path_env(int *index, char **envp)
{
	while (ft_strnstr(envp[*index], "PATH", 4) == NULL)
	{
		if (!envp[*index + 1])
			return (0);
		(*index)++;
	}
	return (1);
}
