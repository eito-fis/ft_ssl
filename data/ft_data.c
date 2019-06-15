/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 11:08:33 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/05 14:12:36 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdlib.h>

t_data	*ft_datanew(int i)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->hash = malloc(sizeof(uint32_t) * i);
	ft_memset(data->hash, 0, sizeof(uint32_t) * i);
	data->tmp = malloc(sizeof(uint32_t) * i);
	ft_memset(data->tmp, 0, sizeof(uint32_t) * i);
	return (data);
}

t_data	*ft_datatmp(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		data->tmp[i] = data->hash[i];
		i++;
	}
	return (data);
}

t_data	*ft_datarot(t_data *data, int n)
{
	uint32_t	tmp;
	int			i;

	i = n - 1;
	tmp = data->tmp[0];
	data->tmp[0] = data->tmp[i];
	data->tmp[i] = tmp;
	while (--i > 0)
	{
		tmp = data->tmp[i + 1];
		data->tmp[i + 1] = data->tmp[i];
		data->tmp[i] = tmp;
	}
	return (data);
}

t_data	*ft_dataadd(t_data *data, int i)
{
	int	save;

	save = i;
	while (--i >= 0)
		data->hash[i] += data->tmp[i];
	data = ft_datatmp(data, save);
	return (data);
}

void	ft_datafree(t_data **data)
{
	t_data *del;

	del = *data;
	free(del->hash);
	free(del->tmp);
	free(del);
	*data = NULL;
}
