/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_membcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:49:49 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 18:22:17 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_membcpy(void *dest, void *src, int b)
{
	int				i;
	unsigned char	*x;
	unsigned char	*y;

	i = 0;
	x = dest;
	y = src;
	while (i < b)
	{
		x[b - 1 - i] = y[i];
		i++;
	}
}
