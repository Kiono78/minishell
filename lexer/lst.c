/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:33:48 by laraujo           #+#    #+#             */
/*   Updated: 2022/04/05 15:12:51 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_data	*ft_lstnew_data(int token, char **arg, int nbr_arg, t_env **head)
{
	t_data	*newlist;

	newlist = malloc(sizeof(t_data));
	if (!newlist)
		return (0);
	newlist->token = token;
	newlist->head = *head;
	if (strdup_token(token, arg, nbr_arg, &newlist))
	{
		free(newlist);
		return (0);
	}
	newlist->next = 0;
	return (newlist);
}

t_data	*ft_lstlast_data(t_data **lst)
{	
	if (!lst)
		return (0);
	while ((*lst)->next)
		*lst = (*lst)->next;
	return (*lst);
}

void	ft_lstadd_back_data(t_data ***alst, t_data *new)
{
	t_data	*lst;

	if (!**alst)
	{
		**alst = new;
		return ;
	}
	lst = ft_lstlast_data(*alst);
	lst->next = new;
}

void	ft_lstclear_data(t_data **lst)
{
	t_data	*tmplst;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmplst = (*lst)->next;
		ft_free_split((*lst)->str);
		free(*lst);
		*lst = tmplst;
	}
	lst = 0;
}
