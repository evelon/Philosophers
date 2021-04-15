/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:07:56 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 18:10:13 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static long long	get_scale(int n)
{
	int	scale;

	scale = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		scale++;
	}
	return (scale);
}

static char			get_digit(long long i, int scale)
{
	int	n;
	int	tenpower;

	n = 1;
	tenpower = 1;
	while (n < scale)
	{
		tenpower *= 10;
		n++;
	}
	i /= tenpower;
	i %= 10;
	if (i < 0)
		i *= -1;
	return (i + '0');
}

static long long	write_num(long long i, int scale, char *num)
{
	int	ind;

	ind = 0;
	while (scale != 0)
	{
		num[ind++] = get_digit(i, scale);
		scale--;
	}
	num[ind] = '\0';
	return (1);
}

char				*ft_itoa(long long n)
{
	char	*str;
	int		scale;

	scale = get_scale(n);
	if (n < 0)
	{
		str = malloc((scale + 2) * sizeof(char));
		if (!str)
			return (NULL);
		*str = '-';
		write_num(n, scale, str + 1);
	}
	else
	{
		str = malloc((scale + 1) * sizeof(char));
		if (!str)
			return (NULL);
		write_num(n, scale, str);
	}
	return (str);
}
