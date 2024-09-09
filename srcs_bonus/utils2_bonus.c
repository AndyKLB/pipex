/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:07:03 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/03 14:22:00 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"

void	ft_free_pipe_fd(t_data *data, int index)
{
	if (data->fd)
	{
		while (index >= 0)
		{
			if (data->fd[index][0] >= 0)
				close(data->fd[index][0]);
			if (data->fd[index][1] >= 0)
				close(data->fd[index][1]);
			free(data->fd[index]);
			index--;
		}
		free(data->fd);
		data->fd = NULL;
	}
	if (data->middle_children)
		free(data->middle_children);
	return ;
}

int	malloc_pipe_fd(t_data *data)
{
	int	i;

	i = 0;
	data->fd = malloc(sizeof(int *) * (data->nb_cmd - 1));
	if (!data->fd)
		return (1);
	while (i < data->nb_cmd - 1)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
		{
			ft_free_pipe_fd(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_piping_and_fork_first_child(t_data *data)
{
	int	i;

	i = 0;
	if (malloc_pipe_fd(data) == 1)
		ft_error(data, "malloc pipe error", EXIT_FAILURE);
	while (i < (data->nb_cmd - 1))
	{
		if ((pipe(data->fd[i])) == -1)
		{
			ft_free_pipe_fd(data, (data->nb_cmd - 1));
			ft_error(data, "pipe error", EXIT_FAILURE);
		}
		i++;
	}
	data->first_child = fork();
	if (data->first_child == -1)
		ft_error(data, "fork error", EXIT_FAILURE);
}

void	fork_brothers(t_data *data)
{
	int	i;

	i = 1;
	while (i < (data->nb_cmd - 2))
	{
		if (data->middle_children[i - 1] > 0)
		{
			data->index_pid_children++;
			data->index_children_begin++;
			data->index_first_pipe++;
			data->middle_children[i] = fork();
		}
		if (data->middle_children[i] == -1)
			ft_error(data, "fork error", EXIT_FAILURE);
		i++;
	}
}

void	ft_forking(t_data *data)
{
	data->last_child = fork();
	if (data->last_child == -1)
		ft_error(data, "fork error", EXIT_FAILURE);
	if (data->first_child > 0 && data->last_child > 0 && data->nb_cmd > 2)
	{
		data->middle_children = ft_calloc((data->nb_cmd - 2), sizeof(pid_t));
		if (!data->middle_children)
			ft_error(data, "malloc pid error", EXIT_FAILURE);
		data->middle_children[0] = fork();
		fork_brothers(data);
	}
}
