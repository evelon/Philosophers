/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:51:13 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 16:23:17 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>

static int	smallest_number(int *list, int size)
{
	int	i;
	int	smaller;

	i = 0;
	smaller = INT32_MAX;
	while (i < size)
	{
		if (smaller > list[i])
			smaller = list[i];
		i++;
	}
	return (smaller);
}

static int	has_all_eaten(t_philo *philo)
{
	if (philo->setting->num_must_eat == -1)
		return (false);
	philo->setting->dashboard[philo->index]++;
	if (smallest_number(philo->setting->dashboard, philo->setting->num_philo) \
	>= philo->setting->num_must_eat)
	{
		philo->setting->status = ALL_ATE;
		return (true);
	}
	return (false);
}

static void	print_ms_index(unsigned long ms, int index, char *msg)
{
	ft_putlu_fd(ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putlu_fd(index + 1, 1);
	ft_putchar_fd(' ', 1);
	ft_putendl_fd(msg, 1);
}

int			print_mutex(unsigned long ms, int action, t_philo *philo)
{
	pthread_mutex_lock(&philo->setting->print_mutex);
	if (action == die)
	{
		print_ms_index(ms, philo->index, "died");
		return (DEAD);
	}
	if (philo->setting->status != DINE)
	{
		pthread_mutex_unlock(&philo->setting->print_mutex);
		return (philo->setting->status);
	}
	if (action == slp)
		if (has_all_eaten(philo))
			return (ALL_ATE);
	if (action == take)
		print_ms_index(ms, philo->index, "has taken a fork");
	else if (action == eat)
		print_ms_index(ms, philo->index, "is eating");
	else if (action == slp)
		print_ms_index(ms, philo->index, "is sleeping");
	else if (action == think)
		print_ms_index(ms, philo->index, "is thinking");
	pthread_mutex_unlock(&philo->setting->print_mutex);
	return (SUCCESS);
}