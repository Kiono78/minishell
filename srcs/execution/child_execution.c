/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 09:54:36 by bterral           #+#    #+#             */
/*   Updated: 2022/04/28 11:00:50 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_fd_in(t_exec *exec, int i)
{
	if (exec[i].fd_in)
		dup2(exec[i].fd_in, STDIN_FILENO);
	else if (i != 0)
		dup2(exec[i - 1].fd[0], STDIN_FILENO);
	close(exec[i].fd[0]);
}

void	manage_fd_out(t_exec *exec, int nbr_cmd, int i)
{
	if (exec[i].fd_out)
		dup2(exec[i].fd_out, STDOUT_FILENO);
	else if (i == (nbr_cmd - 1)) 
		dup2(1, STDOUT_FILENO);
	else
		dup2(exec[i].fd[1], STDOUT_FILENO);
}

int	child_process(t_exec *exec, int nbr_cmd, char **envp)
{
	int i;

	i = 0;
	while (i < nbr_cmd)
	{
		exec[i].pid = fork();
		if (exec[i].pid == 0)
		{
			manage_fd_in(exec, i);
			manage_fd_out(exec, nbr_cmd, i);
			if (exec[i].is_builtin)
				exit(is_build_in(exec[i].data));
			else
				execve(exec[i].cmd_full_path, exec[i].cmd[0], envp);
		}
		close(exec[i].fd[1]);
		if (i != 0)
			close(exec[i - 1].fd[0]);
		else if (i == 0 && nbr_cmd == 1)
			close(exec[i].fd[0]);
		i++;
	}
	return (0);
}