/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:28:50 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/06 19:21:13 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	second_child_process(t_data *data, char **argv, char **env)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		ft_error(data, 0, 5, outfile);
	close(data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(data->fd[0]);
	close(outfile);
	exec_process(argv[3], env);
}

void	child_process(t_data *data, char **argv, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0644);
	if (infile == -1)
		ft_error(data, 0, 5, infile);
	close(data->fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	close(infile);
	exec_process(argv[2], env);
}

// void	print_status(int status)
// {
// 	if (WIFEXITED(status))
// 	{
// 		printf("\nProcess exited with status %d\n", WEXITSTATUS(status));
// 	}
// 	else if (WIFSIGNALED(status))
// 	{
// 		printf("\nProcess exited with status %d\n", WEXITSTATUS(status));
// 		printf("\n\nProcess killed by signal %d\n", WTERMSIG(status));
// 	}
// 	else if (WIFSTOPPED(status))
// 	{
// 		printf("\n\nProcess stopped by signal %d\n", WSTOPSIG(status));
// 	}
// 	else
// 	{
// 		printf("\nUnknown process status\n");
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data_init(&data);
	data.second_child = 0;
	if (argc == 5 && (check_env(env) || (!check_env(env) && argv[2][0] == '/'
			&& argv[3][0] == '/')))
	{
		if ((pipe(data.fd)) == -1)
			ft_error(&data, "pipe error", argc, EXIT_FAILURE);
		data.first_child = fork();
		if (data.first_child > 0)
			data.second_child = fork();
		if (data.first_child == -1 || data.second_child == -1)
			ft_error(&data, "fork error", argc, EXIT_FAILURE);
		else if (data.first_child == 0)
			child_process(&data, argv, env);
		else if (data.second_child == 0)
			second_child_process(&data, argv, env);
		close(data.fd[0]);
		close(data.fd[1]);
		while (wait(&data.status) > 0)
			;
	}
	else
		ft_error(&data, NULL, argc, 127);
}
