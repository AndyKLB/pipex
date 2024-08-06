/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:18:36 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/06 19:21:29 by ankammer         ###   ########.fr       */
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
}

int	check_env(char **env)
{
	int	i;

	i = 0;
	if (!env[i])
		return (0);
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	if (!env[i])
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
