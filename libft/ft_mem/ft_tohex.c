/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:10:53 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 16:24:37 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "ft_mem.h"
#include "ft_printf.h"

static void	ft_tohexerror(void)
{
	ft_printf("invalid hex value\n");
	exit(1);
}

uint8_t		*ft_tohex(uint8_t *buf, char *msg, int n)
{
	int			i;
	uint8_t		tmp;

	ft_memset(buf, 0, 8);
	i = -1;
	while (++i < n && msg[i])
	{
		tmp = g_hexlookup[(int)msg[i]];
		if (tmp == 255)
			ft_tohexerror();
		if (i % 2 == 0)
			tmp = tmp << 4;
		buf[i / 2] |= tmp;
	}
	return (buf);
}
