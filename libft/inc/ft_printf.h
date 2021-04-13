/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:34:36 by mbeaujar          #+#    #+#             */
/*   Updated: 2020/12/11 18:59:56 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_flags
{
	int			dot;
	int			less;
	int			width;
	int			zero;
	int			star;
}				t_flags;

/*
** ft_printf.c
*/

int				ft_printchar(int c);
int				ft_select_type(const char *s, int *i, va_list args);
int				ft_printf(const char *format, ...);

/*
** ft_set_flags.c
*/

t_flags			ft_init_flags(void);
int				ft_is_type(const char c);
int				ft_is_digit(const char c);
int				ft_is_flags(const char c);
void			ft_set_flags(const char *s, int *i, t_flags *flags,
		va_list args);

/*
** ft_fill_flags.c
*/

void			ft_flags_less(t_flags *flags);
void			ft_flags_dot(const char *s, int *i, t_flags *flags,
		va_list args);
void			ft_flags_width(t_flags *flags, va_list args);
void			ft_flags_digit(const char *s, int *i, t_flags *flags);

/*
** ft_print_percent.c
*/

int				ft_print(int start, int end, char c);
int				ft_print_percent(t_flags flags);

/*
** ft_print_nbr.c
*/

unsigned int	ft_sig_nbr(long long nb, int *print, t_flags *flags, int *sign);
int				ft_printnbr(unsigned int nbr);
int				ft_print_nbr_dot(unsigned int nbr, t_flags flags, int sign);
int				ft_print_nbr_width(unsigned int nbr, t_flags flags, int sign);
int				ft_print_nbr(long long nb, t_flags flags);

/*
** ft_count_len.c
*/

int				ft_len_nbr(unsigned int nbr);
int				ft_len_hex(unsigned int nbr);
int				ft_len_mem(unsigned long nbr);

/*
** ft_print_put.c
*/

int				ft_strlen_printf(char *str);
int				ft_printstr(char *str, int max);
int				ft_printhex(unsigned int nb, char value);
int				ft_printaddr(unsigned long addr_l);
void			ft_putnbr(unsigned int nbr);

/*
** ft_print_hex.c
*/

int				ft_print_hex_dot(unsigned int nbr, t_flags flags, char value);
int				ft_print_hex_width(unsigned int nbr, t_flags flags, char value);
int				ft_print_hex(unsigned int nbr, t_flags flags, char value);

/*
** ft_print_char.c
*/

int				ft_print_char(char c, t_flags flags);
int				ft_print_no_type(char c, t_flags flags);

/*
** ft_print_address.c
*/

int				ft_print_address_dot(unsigned long nbr, t_flags flags);
int				ft_print_address_zero(t_flags flags);
int				ft_print_address(unsigned long nbr, t_flags flags);

/*
** ft_print_string.c
*/

int				ft_print_string_dot(char *s, t_flags flags);
int				ft_print_string(char *s, t_flags flags);

#endif
