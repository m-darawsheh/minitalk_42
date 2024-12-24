/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:38:46 by mdarawsh          #+#    #+#             */
/*   Updated: 2024/12/17 14:38:46 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	index_bit = 0;

unsigned int	base_power(int base, int power)
{
	int i;
	int result;

	i = 0;
	result = 1;
	while (i < power)
	{
		result = result * base;
		i++;
	}
	return (result);
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

static unsigned int	take_length(int signal)
{
	unsigned int	resutlt;
	if (signal == SIGUSR2)
	{
		resutlt = base_power(2, index_bit);
	}
	else
	{
		resutlt = 0;
	}
	index_bit++;
	return (resutlt);
}

static char take_char(int signal)
{
	unsigned int resutlt;
	if (signal == SIGUSR2)
	{
		resutlt = base_power(2, index_bit);
	}
	else
	{
		resutlt = 0;
	}
	index_bit++;
	return (resutlt);
}

void reset_all_values(unsigned int *len, char *curent_char, unsigned int *index_char, bool *bit_for_len)
{
	*len = 0;
	*curent_char = 0;
	*index_char = 0;
	index_bit = 0;
	*bit_for_len = true;
}

static void	link_charachters(char **massige, char *curent_char, unsigned int *index_char, int signal, unsigned int *len, bool *bit_for_len)
{
	(*curent_char) += take_char(signal);
	if (index_bit == 8 && (*curent_char == 0))
	{
		(*massige)[(*index_char)] = '\0';
		ft_putstr(*massige);
		free (*massige);
		*massige = NULL;
		reset_all_values(len, curent_char, index_char, bit_for_len);
	}
	if(index_bit == 8)
	{
		(*massige)[(*index_char)] = *curent_char;
		(*index_char)++;
		index_bit = 0;
		*curent_char = 0;
	}

}

void    sig_handler(int signal)
{
	static unsigned int	len;
	static bool			bit_for_len = true;
	static char			*massige;
	static char			curent_char;
	static unsigned int	index_char;

	if(index_bit <= 32 && bit_for_len)
	{
		len += take_length(signal);
		if (index_bit == 32)
		{
			massige = malloc(sizeof(char)*(len + 1));
			if(massige == NULL)
			{
				free(massige);
				write(1, "Error\n", 6);
				exit(1);
			}
			bit_for_len = false;
			index_bit = 0;
		}
	}
	else
		link_charachters(&massige, &curent_char, &index_char, signal, &len, &bit_for_len);
}

void	ft_putnpr(int n)
{
	if (n > 9)
		ft_putnpr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int main(void)
{
	int	pid;

	pid = getpid();
	write(1, "Server PID: ", 13);
	ft_putnpr(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		usleep(404);
	return (0);

}
