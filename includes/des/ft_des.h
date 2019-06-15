/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:30:33 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/16 10:38:32 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DES_H
# define FT_DES_H

# include "ft_ssl.h"
# define FLAGS_S 3
# define INPUTS_S 3
# define BUF_S 3
# define IS_INPUT(x) (x == 'i' || x == 'o' || x == 'p')
# define IS_BUF(x) (x == 's' || x == 'v' || x == 'k')
# define IS_READ(x) (IS_INPUT(x) || IS_BUF(x))

typedef struct		s_desflags
{
	char			f;
	int				*i;
	int				v;
}					t_desflags;

typedef struct		s_desinputs
{
	char			f;
	char			**str;
}					t_desinputs;

typedef struct		s_desbufs
{
	char			f;
	uint8_t			*buf;
	int				*flag;
}					t_desbufs;

#endif
