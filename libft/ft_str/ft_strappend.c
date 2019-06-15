/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 20:31:25 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/09 20:09:51 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strappend(char *str, char *add, size_t s, size_t c)
{
	size_t i;

	if (s == 0)
		str = ft_strnew(c);
	else
		str = (char*)ft_realloc(str, s, s + c + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < c)
	{
		str[s] = add[i];
		s++;
		i++;
	}
	str[s] = '\0';
	return (str);
}
