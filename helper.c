/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:19:10 by mdarawsh          #+#    #+#             */
/*   Updated: 2024/12/27 18:41:27 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnpr(int n)
{
	if (n > 9)
		ft_putnpr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int	base_power(int base, int power)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (i < power)
	{
		result = result * base;
		i++;
	}
	return (result);
}

unsigned int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int	convert(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
