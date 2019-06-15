/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deswrite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:05:11 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/09 19:38:52 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_des.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

extern char		*g_desoutput;
extern char		*g_despass;
extern int		g_desbase64;
extern int		g_desenclength;
extern uint8_t	g_dessalt[];

static char		*ft_desbase64(char *msg)
{
	char	*ret;
	char	*b64;

	if (g_despass)
	{
		b64 = ft_strnew(16 + g_desenclength);
		ft_memcpy(b64, "Salted__", 8);
		ft_memcpy(b64 + 8, g_dessalt, 8);
		ft_memcpy(b64 + 16, msg, g_desenclength);
		g_desenclength += 16;
	}
	else
		b64 = ft_strdup(msg);
	ret = ft_base64e(b64, g_desenclength);
	ret = ft_strappend(ret, "\n", ft_strlen(ret), 1);
	free(b64);
	free(msg);
	g_desenclength = ft_strlen(ret);
	return (ret);
}

static void		ft_deswritedecode(int fd, char *enc)
{
	write(fd, (unsigned char*)enc, g_desenclength);
	close(fd);
	if (g_desoutput)
		free(g_desoutput);
	free(enc);
}

static void		ft_deswriteencode(int fd, char *enc)
{
	if (g_desbase64)
		enc = ft_desbase64(enc);
	else if (g_despass)
	{
		write(fd, "Salted__", 8);
		write(fd, g_dessalt, 8);
	}
	write(fd, (unsigned char*)enc, g_desenclength);
	close(fd);
	if (g_desoutput)
		free(g_desoutput);
	free(enc);
}

void			ft_deswrite(int d, char *enc)
{
	int		fd;

	fd = STDOUT_FILENO;
	if (g_desoutput)
	{
		fd = open(g_desoutput, O_DIRECTORY);
		if (fd > 0)
			close(fd);
		if (fd > 0 || (fd =
					open(g_desoutput, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
			ft_exit(1, "ft_ssl:", g_desoutput, ": could not be opened\n");
	}
	if (d)
		ft_deswritedecode(fd, enc);
	else
		ft_deswriteencode(fd, enc);
}
