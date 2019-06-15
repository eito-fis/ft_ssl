/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desprint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 09:56:36 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 15:56:26 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DESPRINT_H
# define FT_DESPRINT_H

# include "ft_des.h"

char				*g_desmode = "";
char				*g_desinput = NULL;
char				*g_desoutput = NULL;
char				*g_despass = NULL;
uint8_t				g_dessalt[8];
uint8_t				g_desiv[8];
uint8_t				g_deskey[8];
int					g_desdecode = 0;
int					g_desbase64 = 0;
int					g_dessaltset = 0;
int					g_desivset = 0;
int					g_deskeyset = 0;
int					g_desenclength = 0;
t_desflags			g_desflags[] =
{
	{'a', &g_desbase64, 1},
	{'d', &g_desdecode, 1},
	{'e', &g_desdecode, 0},
};
t_desinputs			g_desinputs[] =
{
	{'i', &g_desinput},
	{'o', &g_desoutput},
	{'p', &g_despass},
};
t_desbufs			g_desbufs[] =
{
	{'s', g_dessalt, &g_dessaltset},
	{'v', g_desiv, &g_desivset},
	{'k', g_deskey, &g_deskeyset},
};

#endif
