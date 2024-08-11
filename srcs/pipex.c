/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:28:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/11 15:33:55 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	second_child_process(t_data *data, char **argv, char **envp)
{
	data->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		ft_error(data, "Permission denied", 5, 1);
	close(data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->fd[0]);
	close(data->outfile);
	exec_process(argv[3], envp, data);
}

void	child_process(t_data *data, char **argv, char **envp)
{
	close(data->fd[0]);
	data->infile = open(argv[1], O_RDONLY, 0644);
	if (data->infile == -1)
		ft_error(data, "Permission denied", 5, 0);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	close(data->infile);
	exec_process(argv[2], envp, data);
}

void	end_process(t_data *data)
{
	close(data->fd[0]);
	close(data->fd[1]);
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_init(&data);
	if (argc == 5 && (check_envp(envp, argv)))
	{
		if ((pipe(data.fd)) == -1)
			ft_error(&data, "pipe error", argc, EXIT_FAILURE);
		data.first_child = fork();
		if (data.first_child > 0)
			data.second_child = fork();
		if (data.first_child == -1 || data.second_child == -1)
			ft_error(&data, "fork error", argc, EXIT_FAILURE);
		else if (data.first_child == 0)
			child_process(&data, argv, envp);
		else if (data.second_child == 0)
		{
			second_child_process(&data, argv, envp);
		}
		end_process(&data);
	}
	else
		ft_error(&data, NULL, argc, 127);
}
