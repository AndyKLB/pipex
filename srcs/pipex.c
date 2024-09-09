/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:28:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/29 16:52:14 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	second_child_process(t_data *data, char **argv, char **envp)
{
	close(data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	if (data->outfile >= 0)
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
	close(data->fd[0]);
	exec_process(argv[3], envp, data, 1);
}

void	child_process(t_data *data, char **argv, char **envp)
{
	close(data->fd[0]);
	data->infile = open(argv[1], O_RDONLY, 0644);
	if (data->infile == -1)
		ft_error(data, "Permission denied", 0);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	if (data->outfile >= 0)
		close(data->outfile);
	close(data->infile);
	exec_process(argv[2], envp, data, 0);
}

void	end_process(t_data *data)
{
	int	code;

	code = EXIT_FAILURE;
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->outfile >= 0)
		close(data->outfile);
	while (errno != ECHILD)
		if (wait(&data->status) == data->second_child
			&& WIFEXITED(data->status))
			code = WEXITSTATUS(data->status);
	if (data->second_child == -1)
		exit(127);
	else if (data->outfile == -1)
		ft_error(data, "Permission denied", 1);
	exit(code);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_init(&data, argv);
	if (argc == 5)
	{
		if ((pipe(data.fd)) == -1)
			ft_error(&data, "pipe error", EXIT_FAILURE);
		data.first_child = fork();
		if (data.first_child > 0)
			data.second_child = fork();
		if (data.first_child == -1 || data.second_child == -1)
			ft_error(&data, "fork error", EXIT_FAILURE);
		else if (data.first_child == 0)
			child_process(&data, argv, envp);
		else if (data.second_child == 0)
			second_child_process(&data, argv, envp);
		end_process(&data);
	}
	else
		ft_error(&data,
			"bad argument\nrappel : <infile> <cmd1> <cmd2> <outfile>\n", 127);
}
