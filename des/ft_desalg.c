/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desalg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 13:52:23 by eito-fis          #+#    #+#             */
/*   Updated: 2019/06/14 20:16:10 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdlib.h>
#include "ft_desalg.h"

extern uint8_t	g_keys[16][6];

static void		ft_desboxes(uint8_t *buf, uint32_t *tmp)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < 8)
	{
		x = (ft_getbit(i * 6 + 1, buf, 8) << 3) |
			(ft_getbit(i * 6 + 2, buf, 8) << 2) |
			(ft_getbit(i * 6 + 3, buf, 8) << 1) |
			(ft_getbit(i * 6 + 4, buf, 8));
		y = (ft_getbit(i * 6, buf, 8) << 1) |
			(ft_getbit(i * 6 + 5, buf, 8));
		tmp[0] = tmp[0] << 4;
		tmp[0] |= g_desboxes[i][x + y * 16];
	}
}

static void		ft_desrounds(uint32_t l[17][1], uint32_t r[17][1],
		uint8_t keys[16][6])
{
	uint8_t		buf[6];
	uint32_t	tmp[1];
	int			i;
	int			x;

	i = 0;
	while (++i <= 16)
	{
		l[i][0] = r[i - 1][0];
		x = -1;
		ft_memset(buf, 0, 6);
		while (++x < 48)
			ft_setbit(ft_getbit(g_desencp2[x] - 1, r[i - 1], 32), x, buf, 8);
		x = -1;
		while (++x < 6)
			buf[x] = buf[x] ^ keys[i - 1][x];
		ft_desboxes(buf, tmp);
		x = -1;
		r[i][0] = 0;
		while (++x < 32)
			ft_setbit(ft_getbit(g_desencp3[x] - 1, tmp, 32), x, r[i], 32);
		r[i][0] = r[i][0] ^ l[i - 1][0];
	}
}

uint8_t			*ft_desalg(uint8_t buf[8], uint8_t keys[16][6])
{
	uint8_t		block[8];
	uint32_t	l[17][1];
	uint32_t	r[17][1];
	uint8_t		final[8];
	int			i;

	i = -1;
	ft_memset(block, 0, 8);
	while (++i < 64)
		ft_setbit(ft_getbit(g_desencp1[i] - 1, buf, 8), i, block, 8);
	ft_membcpy(l[0], block, 4);
	ft_membcpy(r[0], block + 4, 4);
	ft_desrounds(l, r, keys);
	i = -1;
	ft_membcpy(final, r[16], 4);
	ft_membcpy(final + 4, l[16], 4);
	while (++i < 64)
		ft_setbit(ft_getbit(g_desencp4[i] - 1, final, 8), i, buf, 8);
	return (buf);
}
