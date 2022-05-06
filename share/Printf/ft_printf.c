/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 08:41:54 by engooh            #+#    #+#             */
/*   Updated: 2021/12/22 15:42:29 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_parse(char c, va_list arg, int count)
{
	if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(arg, int), 0);
	else if (c == 'x')
		count += ft_putnbr_base(va_arg(arg, unsigned int), 16, 'a', 0);
	else if (c == 'X')
		count += ft_putnbr_base(va_arg(arg, unsigned int), 16, 'A', 0);
	else if (c == 'c')
		count += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		count += ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		count += ft_putnbr_ptr(va_arg(arg, long ), 0);
	else if (c == 'u')
		count += ft_putnbr_base(va_arg(arg, unsigned int), 10, '0', 0);
	else if (c == '%')
		count += ft_putchar('%');
	else
		return (0);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	va_list	args;

	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%' && *(++s))
			count += ft_parse(*s, args, 0);
		else
			count += ft_putchar(*s);
		s++;
	}
	va_end(args);
	return (count);
}
