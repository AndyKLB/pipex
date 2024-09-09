/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:18:36 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/21 17:35:40 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	data_init(t_data *data, char **argv)
{
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->first_child = 0;
	data->second_child = 0;
	data->status = 0;
	data->infile = 0;
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		perror("open error");
	data->split_path = NULL;
}

void	ft_error(t_data *data, char *message, int exit_code)
{
	if (message)
		ft_putstr_fd(message, 2);
	if (data)
	{
		if (data->infile >= 0)
			close(data->infile);
		if (data->outfile >= 0)
			close(data->outfile);
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
