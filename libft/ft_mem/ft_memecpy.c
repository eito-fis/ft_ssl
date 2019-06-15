/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memecpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:35:21 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/15 14:49:41 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memecpy(void *restrict dst,
		const void *restrict src, size_t n, size_t s)
{
	size_t		i;
	int			saved;
	uint32_t	*tab;

	i = 0;
	saved = s - 1;
	while (i < n)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	tab = (uint32_t*)dst;
	while (i < s)
	{
		if (!tab[i] && i)
			s = i - 1;
		tab[i] = FLIP(tab[i]);
		i++;
	}
	return (dst);
}
