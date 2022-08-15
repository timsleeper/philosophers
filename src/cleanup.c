/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:45 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 22:36:07 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void kill_mutex(t_params *params)
{
	int i;

	i = 0;
	while (i < params->num_philos)
	{
		pthread_mutex_destroy(&params->forks_mutex[i]);
		pthread_mutex_destroy(&params->philos[i].status_mutex);
		pthread_mutex_destroy(&params->philos[i].meal_mutex);
		pthread_mutex_destroy(&params->philos[i].local_dead_mutex);
		i++;
	}
	pthread_mutex_destroy(&params->print_mutex);
	pthread_mutex_destroy(&params->dead_mutex);
}

void	free_mem(t_params *params)
{
	if (params->philos)
		free(params->philos);
	if (params->forks_mutex)
		free(params->forks_mutex);
	if (params->pthreads)
		free(params->pthreads);
}

void free_all(t_params *params)
{
	kill_mutex(params);
	free_mem(params);
}