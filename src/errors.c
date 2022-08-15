/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:21:04 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/15 00:14:52 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_mutex(t_params *params, char *str)
{
	free(params->philos);
	free(params->forks_mutex);
	kill_mutex(params);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

int	error_msg(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

int	error_mem(t_params *params, char *str)
{
	free_mem(params);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

int	error_time(t_params *params, char *str)
{
	free_all(params);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

int	error_thread(t_params *params, int num, char *str)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, str, ft_strlen(str));
	while (i < num)
	{
		pthread_join(params->pthreads[i], NULL);
		i++;
	}
	free_all(params);
	return (1);
}
