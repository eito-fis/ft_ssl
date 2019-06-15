/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 09:55:08 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/18 15:30:27 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_base64.h"
#include <stdlib.h>

char		*ft_base64e(char *msg, int l)
{
	uint8_t		*tab;
	char		*ret;
	int			b;
	int			i;

	tab = malloc(l + 1);
	tab = ft_memcpy(tab, msg, l);
	tab[l] = 0;
	b = l * 8;
	l = ((b / 6) / 4 + (((b / 6) % 4) ? 1 : 0)) * 4;
	ret = ft_strnew(l);
	ret = ft_memset(ret, '=', l);
	i = -1;
	while (++i < l && (i * 6) < b)
		ret[i] = g_eb64[B64_B(tab, i * 6, 0) | B64_B(tab, i * 6, 1) |
			B64_B(tab, i * 6, 2) | B64_B(tab, i * 6, 3) |
			B64_B(tab, i * 6, 4) | B64_B(tab, i * 6, 5)];
	return (ret);
}

static char	*ft_cleanbuf(char *msg)
{
	int		i;
	int		a;
	int		c;
	char	*ret;

	i = 0;
	c = 0;
	while (msg[i])
		if (msg[i++] != '\n')
			c++;
	ret = ft_strnew(c);
	i = 0;
	a = 0;
	while (i < c)
	{
		while (msg[a] == '\n')
			a++;
		ret[i++] = msg[a++];
	}
	return (ret);
}

char		*ft_base64d(char *msg, int *len)
{
	char		*ret;
	char		*buf;
	int			l;
	int			b;

	buf = ft_cleanbuf(msg);
	l = ft_strlen(buf);
	while (l != 0 && buf[--l] == '=')
		;
	b = (l + 1) * 6 / 8;
	if (l)
		*len = b;
	ret = ft_strnew(b);
	b = b * 8 - 1;
	while (b >= 0)
	{
		ret[b / 8] |= ((g_db64[(uint8_t)buf[b / 6]] &
					(1 << (5 - b % 6))) > 0) << (7 - b % 8);
		b--;
	}
	free(buf);
	return (ret);
}
