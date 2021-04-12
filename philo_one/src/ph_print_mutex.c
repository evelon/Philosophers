/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:51:13 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 22:16:39 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	smallest_number(int *list, int size)
{
	int	i;
	int	smaller;

	i = 0;
	smaller = ~i - 1;
	while (i < size)
	{
		if (smaller > list[i])
			smaller = list[i];
		i++;
	}
	return (smaller);
}

int			print_mutex(int ms, int action, t_philo *philo)
{
	pthread_mutex_lock(&philo->setting->print_mutex);
	ft_putnbr_fd(ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(philo->index, 1);
	ft_putchar_fd(' ', 1);
	if (action = take)
		ft_putendl_fd("has taken a fork", 1);
	else if (action = eat)
		ft_putendl_fd("is eating", 1);
	else if (action = sleep)
	{
		philo->setting->dashboard[philo->index]++;
		if (philo->setting->num_must_eat != 0 && \
smallest_number(philo->setting->dashboard, philo->setting->num_philo) >= \
philo->setting->num_must_eat)
		{
			pthread_mutex_unlock(&philo->setting->print_mutex);
			return (true);
		}
		ft_putendl_fd("is sleeping", 1);
	}
	else if (action = think)
		ft_putendl_fd("is thinking", 1);
	else
	{
		ft_putendl_fd("died", 1);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->setting->print_mutex);
	return (false);
}