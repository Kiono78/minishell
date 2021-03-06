/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:46:14 by laraujo           #+#    #+#             */
/*   Updated: 2022/05/23 18:01:54 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret_sig;

void	process_line(char *line, t_termios *term, t_env **head)
{
	t_data	*lex;

	set_sig(&sig_handler_disable);
	add_history(line);
	lex = lexer(parsing(line, head), head);
	if (lex && lex->str[0] && is_build_in_bool(lex->str[0])
		&& lex->next == NULL)
		g_ret_sig = is_build_in(&lex, 1, term);
	else if (lex)
		execute_command(&lex, head, term);
	ft_lstclear_data(&lex);
}

int	prompt(t_env **head, char **env, t_termios *term)
{
	char	*line;

	(void)env;
	line = readline(MINISHELL);
	if (!line)
	{
		tcsetattr(0, TCSANOW, &term->old_term);
		free_env(head);
		ft_dprintf(1, "%se%sxi%st%s\n", BLUE, WHITE, RED, WHITE);
		exit(g_ret_sig);
	}
	else if (ft_strcmp(line, ""))
		free(line);
	else
		process_line(line, term, head);
	return (0);
}

void	init_termios(t_termios *term)
{
	tcgetattr(ttyslot(), &term->old_term);
	term->new_term = term->old_term;
	term->new_term.c_lflag &= ~(ICANON | ECHOCTL);
	tcsetattr(ttyslot(), TCSANOW, &term->new_term);
}

int	main(int argc, char **argv, char **env)
{
	t_env		*head;
	t_termios	term;
	int			ret;

	(void) argv;
	if (argc != 1)
		return (-1);
	init_env_var(env, &head);
	init_termios(&term);
	while (1)
	{
		tcsetattr(0, TCSANOW, &term.new_term);
		set_sig(&sig_handler_prompt);
		ret = prompt(&head, env, &term);
	}
}
