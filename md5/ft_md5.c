/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 10:12:42 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 15:49:32 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"
#include <stdlib.h>
#include <stdio.h>

static uint32_t	*ft_md5padding(char *msg, int len)
{
	uint32_t	*tab;
	int			b;
	int			l;
	uintmax_t	i;

	b = len * 8;
	l = ((b + 1 + 64) / 512 + 1) * 512 / 8;
	tab = malloc(l);
	tab = ft_memset(tab, 0, l);
	tab = ft_memcpy(tab, msg, len);
	tab[(b + 1) / 32] |= 1 << (6 + (b + 1) % 32);
	i = (l / sizeof(uint32_t) - 2) * sizeof(uint32_t) * 8;
	while (i % 512 != 0 && b)
	{
		tab[i / 32] |= (b & 1) << (i % 32);
		b = b >> 1;
		i++;
	}
	return (tab);
}

static t_data	*ft_md5calc(t_data *d, uint32_t *w, int i)
{
	int		t1;
	int		t2;

	if (0 <= i && i <= 15)
	{
		t1 = (d->tmp[1] & d->tmp[2]) | ((~d->tmp[1]) & (d->tmp[3]));
		t2 = i;
	}
	else if (16 <= i && i <= 31)
	{
		t1 = (d->tmp[3] & d->tmp[1]) | ((~d->tmp[3]) & (d->tmp[2]));
		t2 = (i * 5 + 1) % 16;
	}
	else if (32 <= i && i <= 47)
	{
		t1 = d->tmp[1] ^ d->tmp[2] ^ d->tmp[3];
		t2 = (i * 3 + 5) % 16;
	}
	else
	{
		t1 = d->tmp[2] ^ (d->tmp[1] | (~d->tmp[3]));
		t2 = (i * 7) % 16;
	}
	d->tmp[0] = d->tmp[1] + ROT_L((d->tmp[0] + t1 + w[t2] + g_t[i]), g_s[i]);
	return (d);
}

static t_data	*ft_md5hash(t_data *data, char *msg, int len)
{
	uint32_t	*tab;
	uint32_t	*words;
	int			i;
	int			x;
	int			l;

	l = ((len * 8 + 65) / 512 + 1) * 512 / 8 / sizeof(uint32_t);
	tab = ft_md5padding(msg, len);
	words = malloc(sizeof(uint32_t) * 16);
	i = 0;
	while (i < l)
	{
		x = 0;
		while (x < 16)
			words[x++] = tab[i++];
		x = 0;
		while (x < 64)
			data = ft_datarot(ft_md5calc(data, words, x++), 4);
		data = ft_dataadd(data, 4);
	}
	free(words);
	free(tab);
	return (data);
}

char			*ft_md5(char *msg, int len)
{
	t_data	*data;
	char	*ret;
	int		i;
	int		x;

	i = 32;
	x = 4;
	ret = ft_strnew(i);
	data = ft_datanew(x);
	while (--x >= 0)
		data->hash[x] = g_hashmd5[x];
	data = ft_datatmp(data, 4);
	data = ft_md5hash(data, msg, len);
	while (++x <= 3)
		data->hash[x] = FLIP(data->hash[x]);
	x = 3;
	while (--i >= 0)
	{
		ret[i] = g_key[(data->hash[x] & 0xF)];
		data->hash[x] = data->hash[x] >> 4;
		if (i % 8 == 0 && x)
			x--;
	}
	ft_datafree(&data);
	return (ret);
}
