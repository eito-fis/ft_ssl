/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desmake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:22:37 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/10 14:20:28 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>
#include <unistd.h>

extern int	g_desenclength;
extern int	g_desdecode;

static void	ft_descbcencrypt(uint8_t *buf, char *xor, uint8_t *iv, int i)
{
	int		x;

	x = -1;
	while (++x < 8)
	{
		if (i < 8)
			buf[x] = buf[x] ^ iv[x];
		else
			buf[x] = buf[x] ^ xor[i - 8 + x];
	}
}

static int	ft_desgetpadding(uint8_t *buf)
{
	int		x;
	int		s;

	x = 7;
	s = buf[x];
	if (s > 8)
		return (0);
	while (--x >= 8 - s)
		if (buf[x] != s)
			return (0);
	return (8 - x - 1);
}

static char	*ft_desdecrypt(char *msg, uint8_t *iv, int cbc, uint8_t keys[16][6])
{
	char	*ret;
	uint8_t	buf[8];
	int		l;
	int		i;

	l = g_desenclength;
	i = l;
	while ((i -= 8) >= 0)
	{
		ft_memset(buf, 0, 8);
		ft_memcpy(buf, msg + i, 8);
		ft_desalg(buf, keys);
		if (cbc)
			ft_descbcencrypt(buf, msg, iv, i);
		if (i == l - 8)
		{
			g_desenclength = l - ft_desgetpadding(buf);
			ret = ft_strnew(g_desenclength);
			ft_memcpy(ret + i, buf, 8 - ft_desgetpadding(buf));
		}
		else
			ft_memcpy(ret + i, buf, 8);
	}
	return (ret);
}

static char	*ft_desencrypt(char *msg, uint8_t *iv, int cbc, uint8_t keys[16][6])
{
	char	*ret;
	uint8_t	buf[8];
	int		l;
	int		i;

	l = g_desenclength;
	g_desenclength = (((l * 8 / 64) + 1) * 64 / 8);
	ret = ft_strnew(g_desenclength);
	i = -8;
	while ((i += 8) <= l)
	{
		ft_memset(buf, 0, 8);
		if (i + 8 >= l)
		{
			ft_memcpy(buf, msg + i, l - i);
			ft_memset(buf + l - i, 8 - (l - i), 8 - (l - i));
		}
		else
			ft_memcpy(buf, msg + i, 8);
		if (cbc)
			ft_descbcencrypt(buf, ret, iv, i);
		ft_desalg(buf, keys);
		ft_memcpy(ret + i, buf, 8);
	}
	return (ret);
}

char		*ft_desmake(char *msg, uint8_t *key, uint8_t *iv, int cbc)
{
	char	*ret;
	uint8_t	keys[16][6];

	ft_dessubkey(key, keys, g_desdecode);
	if (g_desdecode)
		ret = ft_desdecrypt(msg, iv, cbc, keys);
	else
		ret = ft_desencrypt(msg, iv, cbc, keys);
	return (ret);
}
