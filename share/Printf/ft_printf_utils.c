/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:36:43 by engooh            #+#    #+#             */
/*   Updated: 2021/12/22 15:51:30 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = -1;
	while (str[++i])
		write(1, str + i, 1);
	return (i);
}

int	ft_putnbr_ptr(uintptr_t nbr, int count)
{
	if (nbr > 0)
		count = ft_putnbr_ptr(nbr / 16, count + 1);
	if (nbr && nbr % 16 < 10)
		ft_putchar((nbr % 16) + '0');
	else if (nbr && nbr % 16 >= 10)
		ft_putchar(((nbr % 16) - 10) + 'a');
	else if (!nbr && count)
		count += ft_putstr("0x");
	else if (!nbr && !count)
		return (ft_putstr("(null)"));
	return (count);
}

int	ft_putnbr(int n, int count)
{
	if (n < 0 && !count)
		count = ft_putchar('-');
	else
		n = -n;
	if (n)
		count = ft_putnbr(-(n / 10), count + 1);
	if (n <= -10)
		ft_putchar(-(n % 10) + '0');
	else if (n > -10 && n < 0)
		ft_putchar(-n + '0');
	if (!n && !count)
		count = ft_putchar('0');
	return (count);
}

int	ft_putnbr_base(unsigned int nbr, int base, char flag, int count)
{
	if (!nbr && !count)
		return (ft_putchar('0'));
	if (base == 16 && nbr)
	{
		if (nbr > 0)
			count = ft_putnbr_base(nbr / 16, base, flag, count + 1);
		if ((nbr % 16) < 10)
			ft_putchar((nbr % 16) + '0');
		else
			ft_putchar(((nbr % 16) - 10) + flag);
	}
	else if (base == 10 && nbr)
	{
		if (nbr > 0)
			count = ft_putnbr_base(nbr / base, base, flag, count + 1);
		ft_putchar((nbr % base) + flag);
	}
	return (count);
}
