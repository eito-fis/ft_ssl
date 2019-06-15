/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filetostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:03:16 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/10 14:19:18 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_filetostr(int fd, int *r)
{
	char	buff[BUFF_SIZE];
	char	*ret;
	int		br;
	int		i;

	i = 0;
	ft_memset(buff, 0, BUFF_SIZE);
	while ((br = read(fd, buff, BUFF_SIZE)) > 0)
	{
		ret = ft_strappend(ret, buff, i, br);
		i += br;
		ft_memset(buff, 0, BUFF_SIZE);
	}
	*r = i;
	return (ret);
}
