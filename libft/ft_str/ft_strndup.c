/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:11:54 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/14 16:11:52 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*ret;

	ret = ft_strnew(n);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}
