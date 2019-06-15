/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:07:00 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/18 15:26:34 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdarg.h>
# include "libft.h"
# include "ft_printf.h"
# define CHECK_NULL(x, y) if (!x) return (y)
# define LKUP(x, y, z, i) while (z < i && x != y) z++
# define ROT_L(x, n) ((x << n) | (x >> (32 - n)))
# define ROT_L_N(x, y, z) ((x << y) | (x >> (z - y)))
# define ROT_R(x, n) ((x >> n) | (x << (32 - n)))
# define ROT_R_N(x, y, z) ((x >> y) | (x << (z - y)))
# define FLIP(x) (FLIP1(x) | FLIP2(x) | FLIP3(x) | FLIP4(x))
# define FLIP1(x) ((x & 0xFF) << 24)
# define FLIP2(x) ((x & 0xFF00) << 8)
# define FLIP3(x) ((x & 0xFF0000) >> 8)
# define FLIP4(x) ((x & 0xFF000000) >> 24)

typedef struct	s_data
{
	uint32_t	*hash;
	uint32_t	*tmp;
}				t_data;

char			*ft_md5(char *msg, int len);
void			ft_md5print(int argc, char **args);
char			*ft_sha256(char *msg);
void			ft_sha256print(int argc, char **args);
char			*ft_base64e(char *msg, int l);
char			*ft_base64d(char *msg, int *len);
void			ft_base64print(int argc, char **args);
void			ft_desecb(int argc, char **argv);
void			ft_descbc(int argc, char **argv);
char			*ft_desread(int d);
void			ft_deswrite(int d, char *enc);
void			ft_desparse(int argc, char **argv);
char			*ft_desmake(char *msg, uint8_t *key, uint8_t *iv, int cbc);
void			ft_dessubkey(uint8_t *rkey, uint8_t keys[16][6], int decrypt);
uint8_t			*ft_deskeygen(char *password, uint8_t *salt, int set);
uint8_t			*ft_desalg(uint8_t *buf, uint8_t keys[16][6]);
t_data			*ft_datanew(int i);
t_data			*ft_datatmp(t_data *data, int n);
t_data			*ft_datarot(t_data *data, int n);
t_data			*ft_dataadd(t_data *data, int i);
void			ft_datafree(t_data **data);
void			ft_exit(int error, char *f, char *s, char *t);

#endif
