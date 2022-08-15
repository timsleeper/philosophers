/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe.tadeu <felipe.tadeu@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:28:28 by ftadeu-d          #+#    #+#             */
/*   Updated: 2022/08/15 13:17:06 by felipe.tade      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_count_nbr_len(int n)
{
	int				count;
	unsigned int	nbr;

	count = 0;
	nbr = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		nbr = -n;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long long	a;

	a = (long long)n;
	i = ft_count_nbr_len(a);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (NULL);
	str[i] = '\0';
	if (a == 0)
		str[0] = 48;
	if (a < 0)
	{
		str[0] = '-';
		a = a * -1;
	}
	while (a > 0)
	{
		str[i - 1] = a % 10 + 48;
		a = a / 10;
		i--;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	s;
	int	res;

	c = 0;
	s = 1;
	res = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\v' || str[c] == '\f' || str[c] == '\r')
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (res * 10) + (str[c] - '0');
		c++;
	}
	return (res * s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	n += 1;
	while (--n != 0)
	{
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		else if (*s1++ == 0)
			break ;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}
