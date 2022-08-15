/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:14:30 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 23:05:21 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(t_philos *philos, enum e_msg msg)
{
	const char *prompt[] = {
		"is eating",
		"is sleeping",
		"is thinking",
		"has taken a fork",
		"died"};
	
	pthread_mutex_lock(&philos->params->print_mutex);
	if (msg == DIED)
		printf("\033[0;31m%lu %d %s\033[0m\n", get_total_time(philos), (philos->id + 1), prompt[msg]);
	else if (is_alive(philos->params) == 0)
		printf("%lu %d %s\n", get_total_time(philos), (philos->id + 1), prompt[msg]);
	pthread_mutex_unlock(&philos->params->print_mutex);
}