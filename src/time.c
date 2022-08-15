/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:23:17 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 22:32:45 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_sleep(t_params *params, int sleep_time)
{
	unsigned long start;
	unsigned long end;

	start = get_time();
	end = (unsigned long)sleep_time;
	while (is_alive(params) == 0)
	{
		if ((get_time() - start) >= end)
			break;
		usleep(500);
	}
}


unsigned long get_total_time(t_philos *philos)
{
	struct timeval time;
	unsigned long total_time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	total_time = ((time.tv_sec - philos->params->start_time.tv_sec) * 1000) +
					((time.tv_usec - philos->params->start_time.tv_usec) / 1000);
	return (total_time);
}