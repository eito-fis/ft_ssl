/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:38:53 by eito-fis          #+#    #+#             */
/*   Updated: 2019/06/14 20:16:28 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_des.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

extern char		*g_desinput;
extern char		*g_despass;
extern uint8_t	g_dessalt[];
extern int		g_desbase64;
extern int		g_dessaltset;
extern int		g_deskeyset;
extern int		g_desenclength;

static char		*ft_desbase64(char *msg)
{
	char	*ret;

	ret = ft_base64d(msg, &g_desenclength);
	free(msg);
	return (ret);
}

static void		ft_desgetsalt(char *tmp)
{
	if (g_desenclength < 16 || ft_strncmp(tmp, "Salted__", 8))
		ft_exit(1, "ft_ssl: bad magic number\n", "", "");
	ft_memcpy(g_dessalt, tmp + 8, 8);
	g_desenclength -= 16;
	g_dessaltset = 1;
}

static char		*ft_desreaddecode(int fd)
{
	char	*msg;
	char	*tmp;

	tmp = ft_filetostr(fd, &g_desenclength);
	if (g_desbase64)
		tmp = ft_desbase64(tmp);
	msg = tmp;
	if (g_despass || !g_deskeyset)
	{
		ft_desgetsalt(tmp);
		msg = malloc(sizeof(char) * g_desenclength);
		ft_memcpy(msg, tmp + 16, g_desenclength);
		free(tmp);
	}
	close(fd);
	if (g_desinput)
		free(g_desinput);
	return (msg);
}

static char		*ft_desreadencode(int fd)
{
	char	*msg;

	msg = ft_filetostr(fd, &g_desenclength);
	close(fd);
	if (g_desinput)
		free(g_desinput);
	return (msg);
}

char			*ft_desread(int d)
{
	int		fd;
	char	*msg;

	fd = STDIN_FILENO;
	if (g_desinput)
	{
		fd = open(g_desinput, O_DIRECTORY);
		if (fd > 0)
			close(fd);
		if (fd > 0 || (fd = open(g_desinput, O_RDONLY)) < 0)
			ft_exit(1, "ft_ssl: ", g_desinput, ": could not be opened\n");
	}
	if (d)
		msg = ft_desreaddecode(fd);
	else
		msg = ft_desreadencode(fd);
	return (msg);
}
