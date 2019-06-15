/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setbit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:31:03 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/09 17:16:18 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_setbit(int b, int x, void *mem, int type)
{
	uint32_t	*buf32;
	uint8_t		*buf8;

	if (type == 32)
	{
		buf32 = mem;
		if (b)
			buf32[x / 32] = buf32[x / 32] | b << (31 - x % 32);
		else if ((buf32[x / 32] >> (31 - x % 32)) % 2)
			buf32[x / 32] = buf32[x / 32] ^ 1 << (31 - x % 32);
	}
	else if (type == 8)
	{
		buf8 = mem;
		if (b)
			buf8[x / 8] = buf8[x / 8] | b << (7 - x % 8);
		else if ((buf8[x / 8] >> (7 - x % 8)) % 2)
			buf8[x / 8] = buf8[x / 8] ^ 1 << (7 - x % 8);
	}
}
