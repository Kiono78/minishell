/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:43:10 by laraujo           #+#    #+#             */
/*   Updated: 2022/05/23 18:00:56 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_var_env(char *pt)
{
	int		i;
	char	*var;

	i = 1;
	if (pt[i] == '?' || ft_isdigit(pt[i]) || pt[i] == '@' || pt[i] == '#'
		|| pt[i] == '_' || pt[i] == '\'' || pt[i] == '"')
		i++;
	else if (ft_isalpha(pt[i]))
		while (ft_isalnum(pt[i]))
			i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	ft_strlcpy(var, pt, i + 1);
	return (var);
}

char	*free_join_var_env(char *line, char **end, char **temp)
{
	ft_free(end);
	ft_free(temp);
	return (line);
}

char	*join_var_env(char *line, char *var, int dollar, t_env **head)
{
	char	*end;
	char	*temp;
	char	*get_env;
	char	*dollar_zero;
	int		end_var;

	dollar_zero = NULL;
	end_var = ft_strlen(var) + dollar;
	end = ft_substr(line, end_var, ft_strlen(&line[end_var]));
	line[dollar] = '\0';
	get_env = my_getenv(&var[1], head);
	if (!get_env && ft_strcmp(&var[1], "?"))
		dollar_zero = ft_itoa(g_ret_sig);
	if (get_env)
		temp = ft_strjoin(line, get_env);
	else if (dollar_zero)
	{
		temp = ft_strjoin(line, dollar_zero);
		free(dollar_zero);
	}
	else
		temp = ft_strjoin(line, "");
	ft_free(&line);
	line = ft_strjoin(temp, end);
	return (free_join_var_env(line, &end, &temp));
}

char	*parsing_dollar(char *line, t_env **head, int *i, int *quote)
{
	char		*pt;
	char		*var;

	if (!line)
		return (NULL);
	pt = ft_strchr2(line, '$', &i, &quote);
	if (pt == NULL)
		return (line);
	var = get_var_env(pt);
	if (!var)
		return (NULL);
	line = join_var_env(line, var, *i, head);
	if (ft_strcmp(var, "$"))
		*i += 1;
	ft_free(&var);
	line = parsing_dollar(line, head, i, quote);
	return (line);
}
