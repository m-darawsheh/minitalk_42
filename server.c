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
	printf("base_power\n");
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
	printf("take_length\n");
	unsigned int	resutlt;
	if (signal == SIGUSR2)
	{
		printf("SIGUSR2\n");
		resutlt = base_power(2, index_bit);
	}
	else
	{
		printf("SIGUSR1\n");
		resutlt = 0;
	}
	index_bit++;
	return (resutlt);
}

static char take_char(int signal)
{
	printf("take_char\n");
	unsigned int resutlt;
	if (signal == SIGUSR2)
	{
		printf("SIGUSR2\n");
		resutlt = base_power(2, index_bit);
	}
	else
	{
		printf("SIGUSR1\n");
		resutlt = 0;
	}
	index_bit++;
	return (resutlt);
}

void reset_all_values(unsigned int *len, char **massige, char *curent_char, unsigned int *index_char, bool *bit_for_len)
{
	printf("reset_all_values\n");
	*len = 0;
	*curent_char = 0;
	*index_char = 0;
	index_bit = 0;
	*massige = NULL;
	*bit_for_len = true;
}

static void	link_charachters(char **massige, char *curent_char, unsigned int *index_char, int signal, unsigned int *len, bool *bit_for_len)
{
	(void) (*len);
	(void) (*bit_for_len);
	printf("link_charachters\n");
	(*curent_char) += take_char(signal);
	if(index_bit == 8)
	{
		(*massige)[(*index_char)] = *curent_char;
		printf("take_char did it\t ");
		printf("%c\t", (*massige)[(*index_char)]);
		(*index_char)++;
		printf("index_char %d\t", (*index_char));
		printf("index_bit %d\t", index_bit);
		index_bit = 0;
		*curent_char = 0;
	}
	if (index_bit == 8 && (*curent_char == 0))
	{
		(*massige)[(*index_char)] = '\0';
		printf("take_char did it\t ");
		printf("%c\t", (*massige)[(*index_char)]);
		(*index_char)++;
		printf("index_char %d\t", (*index_char));
		printf("index_bit %d\t", index_bit);
		index_bit = 0;
		*curent_char = 0;
	}
	// else if ((*massige)[(*index_char)] == '\0')
	// {

	// 	printf ("you on null");
	// 	printf("%s\n", (*massige));

	// 	reset_all_values(len, massige, curent_char, index_char, bit_for_len);
	// 	free((*massige));
	// }
	// printf("string:  %s\n", (*massige));
	// printf("index_char %d\n", (*index_char));
	// printf("len %d\n", (*len));
	// if ((*massige)[(*index_char)] == '\0')
	// {

	// 	printf ("you on null");
	// 	printf("%s\n", (*massige));

	// 	reset_all_values(len, massige, curent_char, index_char, bit_for_len);
	// 	free((*massige));
	// }
}

void    sig_handler(int signal)
{
	static unsigned int	len;
	static bool			bit_for_len = true;
	static char			*massige;
	static char			curent_char;
	static unsigned int	index_char;

	static int i = 0;
	printf("signal received %d \n", i);
	if(index_bit <= 32 && bit_for_len)
	{
		len += take_length(signal);
		if (index_bit == 32)
		{
			massige = malloc(sizeof(char)*(len + 1));
			printf("did it...........................................................................\n");
			bit_for_len = false;
			index_bit = 0;
		}
	}
	else
	{
		link_charachters(&massige, &curent_char, &index_char, signal, &len, &bit_for_len);
	}
	i++;
	
}

int main(void)
{

	printf("PID: %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		usleep(404);
	return (0);

}