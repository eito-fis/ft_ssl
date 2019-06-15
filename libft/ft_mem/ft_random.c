/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:39:05 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 18:22:00 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

uint8_t		*ft_random(uint8_t *buf, int n)
{
	int		fd;
	int		br;

	if ((fd = open("/dev/urandom", O_RDONLY)) < 0)
		return (NULL);
	br = 0;
	while ((br = read(fd, buf, n - br)) < n)
		;
	return (buf);
}
