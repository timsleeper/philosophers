/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe.tadeu <felipe.tadeu@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:13:43 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/15 13:15:38 by felipe.tade      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USAGE_ERROR "Usage: ./philo <number of philosophers> <time to eat>\
<time to sleep> <time to die> [time to eat while eating]\n"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

enum	e_msg
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED,
};

typedef struct s_philos
{
	int				id;
	int  			eat_count;
	int				last_meal_time;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t status_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t local_dead_mutex;
	int				status;
	struct s_params	*params;
}				t_philos;

typedef struct s_params
{
	int					num_philos;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					num_meals;
	struct timeval		start_time;
	pthread_t			*pthreads;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		print_mutex;
	int					dead_philos;
	pthread_t			control;
	pthread_mutex_t 	dead_mutex;
	t_philos			*philos;
}				t_params;

void			*stuffed(t_params *params, int i);
void			*monitor(void *arg);
int				check_status(t_philos *philos);

int				ft_count_nbr_len(int n);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);

int				init_params(t_params *params);
int				error_mutex(t_params *params, char *str);
int				error_msg(char *str);
int				error_mem(t_params *params, char *str);
int				error_time(t_params *params, char *str);
int				error_thread(t_params *params, int num, char *str);
void			kill_mutex(t_params *params);
void			free_mem(t_params *params);
void			free_all(t_params *params);

void			take_forks(t_philos *philos);
void			*one_philo(t_philos *philos);
void			*philosophers (void *arg);

int				start_eating(t_philos *philos);
void			start_sleeping(t_philos *philos);
void			start_thinking(t_philos *philos);

int				is_alive(t_params *params);
int				join_pthreads(t_params *params);
int				init_philosophers(t_params *params);

void			print_msg(t_philos *philos, enum e_msg msg);

unsigned long	get_time(void);
void			ft_sleep(t_params *params, int sleep_time);
unsigned long	get_total_time(t_philos *philos);

#endif
