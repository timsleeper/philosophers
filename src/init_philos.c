/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:35 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 23:27:22 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philosophers(t_params *params)
{
	int		i;

	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_create(&params->pthreads[i], NULL, &philosophers, &params->philos[i]) != 0)
			return(error_thread(params, i, "Error creating thread\n"));
		i++;
	}
	if (pthread_create(&params->control, NULL, &monitor, params) != 0)
		return (error_thread(params, i, "Error creating thread\n"));
	return (0);
}

int		join_pthreads(t_params *params)
{
	int i;

	i = 0;
	while (i < params->num_philos)
	{
		pthread_join(params->pthreads[i], NULL);
		i++;
	}
	pthread_join(params->control, NULL);
	return (0);
}