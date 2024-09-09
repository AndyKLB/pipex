/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:18:36 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/02 14:31:45 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"

void	data_init(t_data *data, char **argv, int argc)
{
	data->fd = NULL;
	data->index_first_child = 2;
	data->index_last_child = argc - 2;
	data->index_children_begin = data->index_first_child + 1;
	data->index_pid_children = 0;
	data->nb_cmd = argc - 3;
	data->nb_children = data->nb_cmd - 3;
	data->middle_children = NULL;
	data->index_first_pipe = 0;
	data->first_child = -2;
	data->last_child = -2;
	data->status = 0;
	data->infile = 0;
	data->outfile = open(argv[(data->index_last_child + 1)],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		if (data->fd)
			ft_free_pipe_fd(data, (data->nb_cmd - 2));
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
