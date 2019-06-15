/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deskey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:08:32 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/09 17:13:48 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_deskey.h"
#include <stdlib.h>

static void		ft_keyrot(uint32_t *c, uint32_t *d, uint8_t keys[16][6],
		int dec)
{
	uint8_t		ckey[7];
	uint8_t		tmp[6];
	int			i;
	int			x;

	i = -1;
	while (++i < 16)
	{
		c[0] = ROT_L_N(c[0], g_deskeyrot[i], 28) & (0xFFFFFFF0);
		d[0] = ROT_L_N(d[0], g_deskeyrot[i], 28) & (0xFFFFFFF0);
		x = -1;
		ft_memset(ckey, 0, 7);
		while (++x < 56)
			ft_setbit(ft_getbit(x - ((x < 28) ? 0 : 28),
						((x < 28) ? c : d), 32), x, ckey, 8);
		x = -1;
		while (++x < 48)
			ft_setbit(ft_getbit(g_deskeyp2[x] - 1, ckey, 8), x, keys[i], 8);
	}
	while (dec && --i > 7)
	{
		ft_memcpy(tmp, keys[i], 6);
		ft_memcpy(keys[i], keys[15 - i], 6);
		ft_memcpy(keys[15 - i], tmp, 6);
	}
}

void			ft_dessubkey(uint8_t *rkey, uint8_t keys[16][6], int decrypt)
{
	uint8_t		pkey[7];
	uint32_t	c[1];
	uint32_t	d[1];
	int			i;

	i = -1;
	ft_memset(pkey, 0, 7);
	while (++i < 56)
		ft_setbit(ft_getbit(g_deskeyp1[i] - 1, rkey, 8), i, pkey, 8);
	ft_membcpy(c, pkey, 4);
	c[0] = c[0] & 0xFFFFFFF0;
	ft_membcpy(d, pkey + 3, 4);
	d[0] = (d[0] & 0x0FFFFFFF) << 4;
	i = -1;
	while (++i < 16)
		ft_memset(keys[i], 0, 6);
	ft_keyrot(c, d, keys, decrypt);
}

uint8_t			*ft_deskeygen(char *password, uint8_t *salt, int set)
{
	char		*combined;
	char		*hash;
	uint8_t		*ret;
	int			l;

	if (!set)
		ft_random(salt, 8);
	l = ft_strlen(password);
	combined = ft_strnew(l + 8);
	ft_memcpy(combined, password, l);
	ft_memcpy(combined + l, salt, 8);
	hash = ft_md5(combined, l + 8);
	free(combined);
	ret = malloc(16);
	ft_memset(ret, 0, 16);
	ft_tohex(ret, hash, 32);
	free(hash);
	return (ret);
}
