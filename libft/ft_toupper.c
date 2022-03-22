/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laraujo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:10:03 by laraujo           #+#    #+#             */
/*   Updated: 2021/11/16 14:10:09 by laraujo          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if ((c >= 97 && c <= 122))
		return (c - 32);
	else
		return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main()
{
	printf("%d", ft_toupper('a'));
}*/
