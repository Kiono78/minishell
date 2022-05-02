/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:25:20 by bterral           #+#    #+#             */
/*   Updated: 2022/05/02 10:57:44 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_here_doc(char *delim, t_env **env)
{
	char	*line;
	int		len;
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		//perror_exit(PIPE_ERROR);
		ft_dprintf(2, "error here_doc error");
	pid = fork();
	if (pid == 0)
	{
		line = NULL;
		len = ft_strlen(delim);
		while (1)
		{
			ft_putstr_fd("> ", 1);
			line = parsing_dollar(get_next_line(STDIN_FILENO), env);
			if (!line)
				break ;
			if (!ft_strncmp(line, delim, len) && line[len] == '\n')
				break ;
			if (write(fd[1], line, ft_strlen(line)) == -1)
				ft_dprintf(2, "Error reading the here_doc");
			free(line);
		}
		free(line);
		close(fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	// exit(status);
	return (fd[0]);
}

int	wait_all_pid(t_exec *exec, int nbr_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(exec[i].pid, &status, 0);
		free(exec[i].cmd_full_path);
		i++;
	}
	return (status);
}

void	free_paths(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void	free_all(char **envp, t_exec *exec)
{
	if (envp)
		free_paths(envp);
	if (exec)
		free(exec);
}

int	execute_command(t_data **start, t_env **env)
{
	int		nbr_cmd;
	t_exec	*exec;
	char	**envp;

	nbr_cmd = nbr_of_cmd(start);
	exec = ft_calloc(nbr_cmd, sizeof(t_exec));
	if (!exec)
		exit(1);
	if (populate_exec_table(*start, exec, nbr_cmd, env))
		return (1);
	// print_execution_table(exec, nbr_cmd);
	envp = get_paths(&(*start)->head);
	get_abs_path_cmd(exec, nbr_cmd, envp);
	child_process(exec, nbr_cmd, envp);
	printf("pid status : %d\n", wait_all_pid(exec, nbr_cmd));
	free_all(envp, exec);
	return (0);
}
