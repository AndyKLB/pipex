/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:17:32 by ankammer          #+#    #+#             */
/*   Updated: 2024/08/07 16:52:41 by ankammer         ###   ########.fr       */
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
				ft_putstr_fd("Permission denied", 2);
				error_code = 126;
			}
		}
		else
			ft_putstr_fd("Command not found", 2);
	}
	else
		ft_putstr_fd("No such file or directory", 2);
	return (error_code);
}

int	path_error(char *path, char **cmd_split, char **split_env)
{
	int	error_code;

	error_code = 0;
	error_code = error_code_ret(error_code, cmd_split);
	if (path)
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

	if ((!envp || !envp[0]) && !access(cmd_split[0], F_OK | X_OK))
		return (cmd_split[0]);
	half_path = NULL;
	i = 0;
	if (!check_path_env(&i, envp))
		return (cmd_split[0]);
	data->split_env = ft_split(envp[i] + 5, ':');
	i = -1;
	while (data->split_env[++i])
	{
		path = path_join(half_path, path, data->split_env[i], cmd_split[0]);
		if (!access(path, F_OK | X_OK))
			return (free_tab(data->split_env), path);
		else if (!access(cmd_split[0], F_OK | X_OK))
			return (free_tab(data->split_env), cmd_split[0]);
		if (!data->split_env[i + 1])
			path_error(path, cmd_split, data->split_env);
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
