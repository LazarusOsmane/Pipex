/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:40:49 by engooh            #+#    #+#             */
/*   Updated: 2021/12/22 15:44:36 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include	<stdint.h>

int	ft_parse(char c, va_list arg, int count);
int	ft_printf(const char *s, ...);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n, int count);
int	ft_putnbr_ptr(uintptr_t nbr, int count);
int	ft_putnbr_base(unsigned int nbr, int base, char flag, int count);

#endif 
