/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 09:47:11 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/14 13:08:13 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "ft_ssl.h"
# include <strings.h>
# define C_SIZE 6
# define S_SIZE 0
# define M_SIZE 2
# define CI_SIZE 4

typedef struct	s_look
{
	const char	*s;
	void		(*func)();
}				t_look;

const t_look	g_commands[] =
{
	{"md5", &(ft_md5print)},
	{"sha256", &(ft_sha256print)},
	{"base64", &(ft_base64print)},
	{"des", &(ft_descbc)},
	{"des-ecb", &(ft_desecb)},
	{"des-cbc", &(ft_descbc)},
	{NULL, NULL},
};

#endif
