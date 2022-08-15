/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:48:30 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 22:35:31 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int start_eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->meal_mutex);
	philos->last_meal_time = (int)get_total_time(philos);
	pthread_mutex_unlock(&philos->meal_mutex);
	if (is_alive(philos->params) == 0)
	{
		pthread_mutex_lock(&philos->local_dead_mutex);
		print_msg(philos, EAT);
		pthread_mutex_unlock(&philos->local_dead_mutex);
		ft_sleep(philos->params, philos->params->time_to_eat);
		philos->eat_count++;
	}
	pthread_mutex_unlock(&philos->params->forks_mutex[philos->left_fork]);
	pthread_mutex_unlock(&philos->params->forks_mutex[philos->right_fork]);
	return (0);
}

void start_sleeping(t_philos *philos)
{
	if (is_alive(philos->params) == 0)
	{
		print_msg(philos, SLEEP);
		ft_sleep(philos->params, philos->params->time_to_sleep);
	}
}

void start_thinking(t_philos *philos)
{
	if (is_alive(philos->params) == 0)
	{
		print_msg(philos, THINK);
		usleep(300);
	}
}