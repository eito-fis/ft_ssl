# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otahirov <otahirov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/10 12:11:18 by otahirov          #+#    #+#              #
#    Updated: 2019/01/09 17:02:49 by eito-fis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
LIB = libft.a
LIB_N = lft
LIB_P = libft

P_MD5 = md5
_SRC_MD5 = ft_md5.c ft_md5print.c
SRC_MD5 = $(addprefix $(P_MD5)/,$(_SRC_MD5))
P_SHA256 = sha256
_SRC_SHA256 = ft_sha256.c ft_sha256print.c
SRC_SHA256 = $(addprefix $(P_SHA256)/,$(_SRC_SHA256))
P_BASE64 = base64
_SRC_BASE64 = ft_base64.c ft_base64print.c
SRC_BASE64 = $(addprefix $(P_BASE64)/,$(_SRC_BASE64))
P_DES = des
_SRC_DES = ft_desalg.c ft_deskey.c ft_desmake.c ft_desparse.c ft_desprint.c \
		   ft_desread.c ft_deswrite.c
SRC_DES = $(addprefix $(P_DES)/,$(_SRC_DES))
P_DATA= data
_SRC_DATA = ft_data.c
SRC_DATA = $(addprefix $(P_DATA)/,$(_SRC_DATA))
P_MAIN = main
_SRC_MAIN = main.c
SRC_MAIN = $(addprefix $(P_MAIN)/,$(_SRC_MAIN))

SRC = $(SRC_MD5) $(SRC_DATA) $(SRC_MAIN) $(SRC_SHA256) $(SRC_BASE64) $(SRC_DES)

INC = includes/
INC_I = -I $(INC) -I $(INC)/$(P_MD5) -I $(INC)/$(P_SHA256) -I $(INC)/$(P_BASE64) -I $(INC)/$(P_DES)
INC_LIB = libft/includes/

CFLAGS = -Wall -Wextra -Werror
CLANG = gcc

all : $(NAME)

$(NAME) : $(LIB)
	@$(CLANG) $(CFLAGS) -o $@ $(SRC) $(INC_I) -I $(INC_LIB) -L $(LIB_P) -$(LIB_N)
	@echo "$(NAME) was compiled!"

debug : $(LIB)
	@$(CLANG) $(CFLAGS) -g -o $@ $(SRC) $(INC_I) -I $(INC_LIB) -L $(LIB_P) -$(LIB_N)
	@echo "$(NAME) was compiled!"

$(LIB) :
	@make -C $(LIB_P)

clean :
	@make -C $(LIB_P) clean

fclean :
	@make -C $(LIB_P) fclean
	@rm -f $(NAME)
	@echo "$(NAME) was removed!"

re : fclean all
