/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:57:23 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 22:39:10 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void get_forks(t_params *params, int i)
{
	params->philos[i].left_fork = params->philos[i].id;
	params->philos[i].right_fork = params->philos[i].id - 1;
	if (params->philos[i].right_fork == -1)
		params->philos[i].right_fork = params->num_philos - 1;
}

static int init_philos(t_params *params)
{
	int i;

	i = 0;
	while (i < params->num_philos)
	{
		params->philos[i].id = i;
		get_forks(params, i);
		params->philos[i].last_meal_time = 0;
		params->philos[i].eat_count = 0;
		params->philos[i].status = 1;
		params->philos[i].params = params;
		i++;
	}
	return (0);
}


static int		init_mutex(t_params *params)
{
	int				i;
	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_mutex_init(&params->forks_mutex[i], NULL) != 0)
			return (error_mutex(params, "Error: mutex init failed\n"));
		if (pthread_mutex_init(&params->philos[i].status_mutex, NULL) != 0)
			return (error_mutex(params, "Error: mutex init failed\n"));
		if (pthread_mutex_init(&params->philos[i].meal_mutex, NULL) != 0)
			return (error_mutex(params, "Error: mutex init failed\n"));
		if (pthread_mutex_init(&params->philos[i].local_dead_mutex, NULL) != 0)
			return (error_mutex(params, "Error: mutex init failed\n"));
		i++;
	}
	if (pthread_mutex_init(&params->print_mutex, NULL) != 0)
		return (error_mutex(params, "Error: mutex init failed\n"));
	if (pthread_mutex_init(&params->dead_mutex, NULL) != 0)
		return (error_mutex(params, "Error: mutex init failed\n"));
	return (0);
}

static int		alloc_memory(t_params *params)
{
	params->philos = malloc(sizeof(t_philos) * params->num_philos);
	params->forks_mutex = malloc(sizeof(pthread_mutex_t) * params->num_philos);
	params->pthreads = malloc(sizeof(pthread_t) * params->num_philos);
	if (!params->philos || !params->forks_mutex || !params->pthreads)
		return (error_mem(params, "Error: malloc failed\n"));
	return (0);
}



int		init_params(t_params *params)
{
	if (alloc_memory(params) == 1)
		return (1);
	if (init_mutex(params) == 1)
		return (1);
	if (init_philos(params) == 1)
		return (1);
	params->dead_philos = 0;
	if (gettimeofday(&params->start_time, NULL) == -1)
		return (error_time(params, "Error: gettimeofday failed\n"));
	return (0);
}


