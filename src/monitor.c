/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:40:07 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 23:01:36 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int is_alive(t_params *params)
{
	int dead;

	dead = 0;
	pthread_mutex_lock(&params->dead_mutex);
	if (params->dead_philos == 1)
		dead = 1;
	pthread_mutex_unlock(&params->dead_mutex);
	return (dead);
}

static int check_stuffed(t_philos *philos)
{
	int eat;

	eat = 0;
	pthread_mutex_lock(&philos->local_dead_mutex);
	pthread_mutex_lock(&philos->meal_mutex);
	if ((int)get_total_time(philos) - philos->last_meal_time >= philos->params->time_to_die)
		eat = 1;
	pthread_mutex_unlock(&philos->meal_mutex);
	pthread_mutex_unlock(&philos->local_dead_mutex);
	return (eat);
}

void *stuffed(t_params *params, int i)
{
	pthread_mutex_lock(&params->dead_mutex);
	params->dead_philos = 1;
	pthread_mutex_unlock(&params->dead_mutex);
	print_msg(&params->philos[i], DIED);
	return (NULL);
}

int check_status(t_philos *philos)
{
	int status;

	status = 0;
	pthread_mutex_lock(&philos->status_mutex);
	if (philos->status == 0)
		status = 1;
	pthread_mutex_unlock(&philos->status_mutex);
	return (status);
}


void *monitor(void *arg)
{
	t_params *params;
	int i;
	int num_dead;

	params = (t_params *)arg;
	num_dead = 0;
	while (params->dead_philos == 0)
	{
		i = 0;
		while (i < params->num_philos && num_dead != params->num_philos)
		{
			if (check_status(&params->philos[i]) == 1 && check_stuffed(&params->philos[i]) == 0)
			{
				if (++num_dead == params->num_philos)
					return (NULL) ;
			}
			if (check_status(&params->philos[i]) == 0 && check_stuffed(&params->philos[i]) == 1)
				return (stuffed(params, i));
			i++;
		}	
		usleep(7000);
	}
	return (NULL);
}