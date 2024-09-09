/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:28:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/03 14:45:40 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"

void	last_child_process(t_data *data, char **argv, char **envp)
{
	if (dup2(data->fd[(data->nb_cmd - 2)][0], STDIN_FILENO) == -1)
		ft_error(data, "dup2 error", EXIT_FAILURE);
	if (data->outfile >= 0)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			ft_error(data, "dup2 error", EXIT_FAILURE);
		close(data->outfile);
	}
	ft_free_pipe_fd(data, data->nb_cmd - 2);
	exec_process(argv[data->index_last_child], envp, data, 1);
}

void	inter_process(t_data *data, char *cmd_inter, char **envp)
{
	if (dup2(data->fd[data->index_first_pipe][0], STDIN_FILENO) == -1)
		ft_error(data, "dup2 error", EXIT_FAILURE);
	if (dup2(data->fd[data->index_first_pipe + 1][1], STDOUT_FILENO) == -1)
		ft_error(data, "dup2 error", EXIT_FAILURE);
	if (data->outfile >= 0)
		close(data->outfile);
	ft_free_pipe_fd(data, data->nb_cmd - 2);
	exec_process(cmd_inter, envp, data, 0);
}

void	first_child_process(t_data *data, char **argv, char **envp)
{
	data->infile = open(argv[(data->index_first_child - 1)], O_RDONLY, 0644);
	if (data->infile == -1)
		ft_error(data, "Permission denied", 0);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		ft_error(data, "dup2 error", EXIT_FAILURE);
	if (dup2(data->fd[0][1], STDOUT_FILENO) == -1)
		ft_error(data, "dup2 error", EXIT_FAILURE);
	if (data->outfile >= 0)
		close(data->outfile);
	ft_free_pipe_fd(data, data->nb_cmd - 2);
	close(data->infile);
	exec_process(argv[data->index_first_child], envp, data, 0);
}

void	end_process(t_data *data)
{
	int	code;

	code = EXIT_FAILURE;
	ft_free_pipe_fd(data, (data->nb_cmd - 2));
	if (data->outfile >= 0)
		close(data->outfile);
	while (errno != ECHILD)
		if (wait(&data->status) == data->last_child && WIFEXITED(data->status))
			code = WEXITSTATUS(data->status);
	if (data->last_child == -1)
		exit(127);
	else if (data->outfile == -1)
		ft_error(data, "Permission denied", 1);
	exit(code);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_init(&data, argv, argc);
	if (argc > 5)
	{
		ft_piping_and_fork_first_child(&data);
		if (data.first_child > 0)
			ft_forking(&data);
		if (data.first_child == 0)
			first_child_process(&data, argv, envp);
		else if (data.last_child == 0)
			last_child_process(&data, argv, envp);
		if (data.middle_children[data.index_pid_children] == 0)
			inter_process(&data, argv[data.index_children_begin], envp);
		end_process(&data);
	}
	else
		ft_error(&data,
			"bad argument\nrappel : <infile> <cmd1> <cmd2> <outfile>\n", 127);
}
