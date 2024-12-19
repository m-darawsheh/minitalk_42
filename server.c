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

int index_bit = 0;

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

static unsigned int	take_length(int signal)
{
	unsigned int	resutlt;
	if (signal == SIGUSR2)
	{
		resutlt = base_power(2, index_bit);
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
	index_bit++;
	return (resutlt);
}

void reset_all_values(unsigned int *len, char **massige, char *curent_char, unsigned int *index_char, bool *bit_for_len)
{
	*len = 0;
	*curent_char = 0;
	*index_char = 0;
	index_bit = 0;
	*massige = NULL;
	*bit_for_len = true;
}

static void	link_charachters(char **massige, char *curent_char, unsigned int *index_char, int signal, unsigned int *len, bool *bit_for_len)
{
	(*curent_char) += take_char(signal);
	if(index_bit == 8)
	{
		massige[index_char] = *curent_char;
		(*index_char)++;
		index_bit = 0;
		*curent_char = 0;
	}
	if (index_bit == 8 && index_char == (*len))
	{
		massige[index_char] = '\0';
		printf("%s\n", massige);
		reset_all_values(len, massige, curent_char, index_char, bit_for_len);
		free(massige);
	}
}

void    sig_handler(int signal)
{
	static unsigned int	len;
	static bool			bit_for_len;
	static char			*massige;
	static char			curent_char;
	static unsigned int	index_char;

	bit_for_len = true;
	len += take_length(signal);
	if(index_bit == 31 && bit_for_len)
	{
		len += take_length(signal);
		massige = malloc(sizeof(char)*(len + 1));
		bit_for_len = false;
		index_bit = 0;
	}
	if(!bit_for_len)
	{
		link_charachters(&massige, &curent_char, &index_char, signal, &len, &bit_for_len);
	}
	
}

int main(void)
{

	printf("PID: %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		pause();
	return (0);

}