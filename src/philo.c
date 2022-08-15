/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:12:46 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/14 23:19:58 by ftadeu-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int validate_digit(char *str, int *val)
{
	int		num;
	size_t	len;
	char	*test;

	if (*str == '\0')
		return (1);
	num = ft_atoi(str);
	len = ft_strlen(str);
	test = ft_itoa(num);
	if (test == NULL || ft_strncmp(str, test, len) != 0)
		{
			free(test);
			return (1);
		}
	*val = num;
	free(test);
	return (0);
}


static int validate_input(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
		return(error_msg(USAGE_ERROR));
	if (validate_digit(argv[1], &params->num_philos) == 1)
		return(error_msg("Error: Number of philosophers must be a positive integer\n"));
	if (validate_digit(argv[2], &params->time_to_eat) == 1)
		return(error_msg("Error: Time to eat must be a positive integer\n"));
	if (validate_digit(argv[3], &params->time_to_sleep) == 1)
		return(error_msg("Error: Time to sleep must be a positive integer\n"));
	if (validate_digit(argv[4], &params->time_to_die) == 1)
		return(error_msg("Error: Time to die must be a positive integer\n"));
	params->num_meals = -1;
	if (argc == 6)
	{
		if (validate_digit(argv[5], &params->num_meals) == 1)
			return(error_msg("Error: Number of meals must be a positive integer\n"));
	}
	if (params->num_philos < 1 || params->time_to_eat < 0 || params->time_to_sleep < 0 || params->time_to_die < 0 || (argc == 6 && params->num_meals < 1))
		error_msg(USAGE_ERROR);
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (validate_input(argc, argv, &params) == 1)
		return (1);
	if (init_params(&params) == 1)
		return (1);
	if (init_philosophers(&params) == 1)
		return (1);
	join_pthreads(&params);
	free_all(&params);
	return (0);
}