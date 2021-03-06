/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laraujo <laraujo@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:50:39 by bterral           #+#    #+#             */
/*   Updated: 2022/05/06 15:37:33 by laraujo          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_data *data)
{
	int	i;

	if (data->str[1] && disable_option(data->str[1], "unset"))
		return (1);
	i = 1;
	if (!data->str[i])
		return (0);
	while (data->str[i])
	{
		if (is_var_valid(data->str[i]) == 0)
			ft_dprintf(2, RED "unset: %s : not a valid identifier\n" WHITE,
				data->str[i]);
		ft_envdel(data, data->str[i]);
		i++;
	}
	return (0);
}
