/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:17:32 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/20 14:01:18 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	*path_join(char *half_path, char *path, char *split_env, char *cmd)
{
	if (!cmd)
		return (NULL);
	half_path = ft_strjoin(split_env, "/");
	path = ft_strjoin(half_path, cmd);
	free(half_path);
	if (!path)
		return (NULL);
	return (path);
}

int	error_code_ret(int error_code, char **cmd_split)
{
	error_code = 127;
	if ((cmd_split && (cmd_split[0][0] != '/' && cmd_split[0][0] != ' '))
		|| !cmd_split)
	{
		if (cmd_split && !access(cmd_split[0], F_OK))
		{
			if (access(cmd_split[0], X_OK))
			{
				perror("Permission denied");
				error_code = 126;
			}
		}
		else
			perror("Command not found");
	}
	else
		perror("No such file or directory");
	return (error_code);
}

int	path_error(char *path, char **cmd_split, char **split_env)
{
	int	error_code;

	error_code = 0;
	error_code = error_code_ret(error_code, cmd_split);
	if (path && path != cmd_split[0])
		free(path);
	if (split_env)
		free_tab(split_env);
	if (cmd_split)
		free_tab(cmd_split);
	exit(error_code);
}

char	*get_path(char **envp, char **cmd_split, t_data *data)
{
	int		i;
	char	*path;
	char	*half_path;

	i = 0;
	if ((!envp || !envp[0] || !check_path_env(&i, envp))
		&& !access(cmd_split[0], F_OK | X_OK))
		return (cmd_split[0]);
	half_path = NULL;
	data->split_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (data->split_path[++i])
	{
		path = path_join(half_path, path, data->split_path[i], cmd_split[0]);
		if (!access(path, F_OK | X_OK))
			return (free_tab(data->split_path), path);
		else if (!access(cmd_split[0], F_OK | X_OK))
			return (free_tab(data->split_path), cmd_split[0]);
		if (!data->split_path[i + 1])
			path_error(path, cmd_split, data->split_path);
		free(path);
		path = NULL;
	}
	return (NULL);
}

void	exec_process(char *cmd_argv, char **envp, t_data *data)
{
	char	**cmd_split;
	char	*path;

	path = NULL;
	cmd_split = ft_split(cmd_argv, ' ');
	if (cmd_split)
		path = get_path(envp, cmd_split, data);
	if (!path)
		free_tab(cmd_split);
	if (!cmd_split || execve(path, cmd_split, envp) == -1)
		path_error(path, cmd_split, NULL);
}
