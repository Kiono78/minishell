/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laraujo <laraujo@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:13:45 by laraujo           #+#    #+#             */
/*   Updated: 2022/04/04 17:01:18 by laraujo          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_MEM_H
# define ALLOC_MEM_H

# include "../includes/minishell.h"

/*---free.c---*/

void	*ft_free(char **pt);
void	ft_free_split(char **split);

/*---alloc.c---*/

#endif