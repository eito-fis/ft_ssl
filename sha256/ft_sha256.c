/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 10:12:42 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/14 10:08:46 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_sha256.h"
#include <stdlib.h>
#include <stdio.h>

static uint32_t	*ft_sha256padding(char *msg)
{
	uint32_t	*tab;
	int			b;
	int			l;
	int			i;

	b = ft_strlen(msg) * 8;
	l = ((b + 1 + 64) / 512 + 1) * 512 / 8;
	tab = malloc(l);
	tab = ft_memset(tab, 0, l);
	tab = ft_memecpy(tab, msg, ft_strlen(msg), l / 4);
	tab[(b + 1) / 32] |= 1 << (32 - (b + 1) % 32);
	i = l * 8 - 1;
	while (i % 512 != 447 && b)
	{
		tab[i / 32] |= (b & 0x1) << (31 - i % 32);
		b = b >> 1;
		i--;
	}
	return (tab);
}

static uint32_t	*ft_sha256words(uint32_t *tab, uint32_t *w, int *i)
{
	int			x;
	uint32_t	t1;
	uint32_t	t2;

	x = 0;
	while (x < 16)
		w[x++] = tab[(*i)++];
	while (x < 64)
	{
		t1 = ROT_R(w[x - 15], 7) ^ ROT_R(w[x - 15], 18) ^ (w[x - 15] >> 3);
		t2 = ROT_R(w[x - 2], 17) ^ ROT_R(w[x - 2], 19) ^ (w[x - 2] >> 10);
		w[x] = w[x - 16] + t1 + w[x - 7] + t2;
		x++;
	}
	return (w);
}

static t_data	*ft_sha256calc(t_data *d, uint32_t *w, int i)
{
	uint32_t		t1;
	uint32_t		t2;
	uint32_t		a;
	uint32_t		b;

	a = ROT_R(d->tmp[4], 6) ^ ROT_R(d->tmp[4], 11) ^ ROT_R(d->tmp[4], 25);
	b = (d->tmp[4] & d->tmp[5]) ^ ((~d->tmp[4]) & d->tmp[6]);
	t1 = d->tmp[7] + a + b + g_k[i] + w[i];
	a = ROT_R(d->tmp[0], 2) ^ ROT_R(d->tmp[0], 13) ^ ROT_R(d->tmp[0], 22);
	b = (d->tmp[0] & d->tmp[1]) ^ (d->tmp[0] & d->tmp[2])
		^ (d->tmp[1] & d->tmp[2]);
	t2 = a + b;
	d->tmp[7] = d->tmp[6];
	d->tmp[6] = d->tmp[5];
	d->tmp[5] = d->tmp[4];
	d->tmp[4] = d->tmp[3] + t1;
	d->tmp[3] = d->tmp[2];
	d->tmp[2] = d->tmp[1];
	d->tmp[1] = d->tmp[0];
	d->tmp[0] = t1 + t2;
	return (d);
}

static t_data	*ft_sha256hash(t_data *data, char *msg)
{
	uint32_t	*tab;
	uint32_t	*words;
	int			i;
	int			x;
	int			l;

	l = ((ft_strlen(msg) * 8 + 65) / 512 + 1) * 512 / 8 / sizeof(uint32_t);
	tab = ft_sha256padding(msg);
	words = malloc(sizeof(uint32_t) * 64);
	i = 0;
	while (i < l)
	{
		words = ft_sha256words(tab, words, &i);
		x = 0;
		while (x < 64)
			data = ft_sha256calc(data, words, x++);
		data = ft_dataadd(data, 8);
	}
	free(words);
	free(tab);
	return (data);
}

char			*ft_sha256(char *msg)
{
	t_data	*data;
	char	*ret;
	char	*key;
	int		i;
	int		x;

	i = 64;
	x = 8;
	key = "0123456789abcdef";
	ret = ft_strnew(i);
	data = ft_datanew(x);
	while (--x >= 0)
		data->hash[x] = g_hashsha256[x];
	data = ft_datatmp(data, 8);
	data = ft_sha256hash(data, msg);
	x = 7;
	while (--i >= 0)
	{
		ret[i] = key[(data->hash[x] & 0xF)];
		data->hash[x] = data->hash[x] >> 4;
		if (i % 8 == 0 && x)
			x--;
	}
	ft_datafree(&data);
	return (ret);
}
