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

static void	for_len(int signal, int *cur_bit_i, int *is_len,
		char **final_str)
{
	static int	len_value = 0;

	if (signal == SIGUSR2)
		len_value += base_power(2, *cur_bit_i);
	if (*cur_bit_i == 31)
	{
		*is_len = 1;
		*cur_bit_i = 0;
		*final_str = malloc(sizeof(char) * (len_value + 1));
		len_value = 0;
		return ;
	}
	(*cur_bit_i)++;
}

static void	restart_variables(int *is_len, char **str, int *i)
{
	*is_len = 0;
	if (str)
	{
		ft_putstr(*str);
		free(*str);
		*str = NULL;
	}
	*i = 0;
}

static void	signal_handler(int signal)
{
	static int	cur_bit_i = 0;
	static char	char_value = 0;
	static int	is_len = 0;
	static char	*final_str = 0;
	static int	i = 0;

	if (!is_len)
		for_len(signal, &cur_bit_i, &is_len, &final_str);
	else
	{
		if (signal == SIGUSR2)
			char_value += base_power(2, cur_bit_i);
		if (cur_bit_i == 7)
		{
			final_str[i++] = char_value;
			cur_bit_i = 0;
			if (char_value == 0)
				return (restart_variables(&is_len, &final_str, &i));
			char_value = 0;
			return ;
		}
		cur_bit_i++;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "Server PID: ", 13);
	ft_putnpr(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		usleep(404);
	return (0);
}
