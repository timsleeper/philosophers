/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:10:17 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/15 00:39:00 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philos *philos)
{
	pthread_mutex_lock(&philos->params->forks_mutex[philos->left_fork]);
	if (is_alive(philos->params) == 0)
		print_msg(philos, FORK);
	pthread_mutex_lock(&philos->params->forks_mutex[philos->right_fork]);
	if (is_alive(philos->params) == 0)
		print_msg(philos, FORK);
}

void	*one_philo(t_philos *philos)
{
	print_msg(philos, FORK);
	ft_sleep(philos->params, philos->params->time_to_die);
	return (NULL);
}

void	*philosophers(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	if (philos->params->num_philos == 1)
		return (one_philo(philos));
	if ((philos->id + 1) % 2 == 0)
	{
		print_msg(philos, THINK);
		ft_sleep(philos->params, philos->params->time_to_eat / 2);
	}
	while (is_alive(philos->params) == 0)
	{
		take_forks(philos);
		start_eating(philos);
		if (philos->params->num_meals != -1
			&& philos->eat_count == philos->params->num_meals)
			break ;
		start_sleeping(philos);
		start_thinking(philos);
	}
	pthread_mutex_lock(&philos->status_mutex);
	philos->status = 0;
	pthread_mutex_unlock(&philos->status_mutex);
	return (NULL);
}
