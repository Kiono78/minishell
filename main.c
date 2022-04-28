/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:46:14 by laraujo           #+#    #+#             */
/*   Updated: 2022/04/28 15:57:45 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_env **head, char **env)
{
	t_data	*lex;
	char	*line;

	(void) env;
	line = readline(MINISHELL);
	if (!line)
	{
		free_env(head);
		return (-1);
	}
	else
	{
		add_history(line);
		lex = lexer(parsing(line), head);
		printdata(lex);
		// if (lex)
		// 	is_build_in(&lex);
		if (lex)
			execute_command(&lex);
		ft_lstclear_data(&lex);
	}
	return (0);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_termios(void)
{
	struct termios	old_term;
	struct termios	new_term;

	tcgetattr(ttyslot(), &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(ttyslot(), TCSANOW, &new_term);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*head;
	int		ret;

	(void) argv;
	if (argc != 1)
		return (-1);
	init_env_var(env, &head);
	init_termios();
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	while (1)
	{
		ret = prompt(&head, env);
		if (ret)
			return (0);
	}
}
