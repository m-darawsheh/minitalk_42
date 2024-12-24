/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarawsh <mdarawsh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:47:43 by mdarawsh          #+#    #+#             */
/*   Updated: 2024/12/17 12:47:43 by mdarawsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

int	 convert(const char *str)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static bool	pid_error_input(char *p_id)
{
	while (*p_id)
	{
		if (*p_id < '0' || *p_id > '9')
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		p_id++;
	}
	return (true);
}

static void	send_char(int p_id, char c)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (c & 1)
		{
			if(kill(p_id, SIGUSR2) == -1)
			{
				write (1, "Error send signal\n", 6);
				exit(1);
			}
		}
		else 
		{
			if (kill(p_id, SIGUSR1) == -1)
			{
				write (1, "Error send signal\n", 6);
				exit(1);
			}
		}
		c = c >> 1;
		i++;
		usleep(404);
	}
}

static void	send_massige(int p_id, char *massige) 
{
	int i;

	i = 0;
	while (massige[i])
	{
		send_char(p_id, massige[i]);
		i++;
	}
	send_char(p_id, '\0');
}


static void	send_len(int p_id, unsigned int len)
{
	int i;

	i = 0;
	while(i < 32)
	{
		if (len & 1)
		{
			if (kill(p_id, SIGUSR2) == -1)
			{
				write (1, "Error send signal\n", 6);
				exit(1);
			}
		}
		else
		{
			if (kill(p_id, SIGUSR1) == -1)
			{
				write (1, "Error send signal\n", 6);
				exit(1);
			}
		}
		len = len >> 1;
		i++;
		usleep(404);
	}
}

unsigned int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(int argc, char *argv[])
{
	int				p_id;
	unsigned int	len;
	char			*massige;

	if (argc != 3)
		return (1);
	
	if (pid_error_input(argv[1]))
	{
		p_id = convert(argv[1]);
	}
	len = ft_strlen(argv[2]);
	send_len(p_id, len);
	massige = argv[2];
	send_massige(p_id, massige);
	
}
