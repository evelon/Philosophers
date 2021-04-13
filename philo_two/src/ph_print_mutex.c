/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:51:13 by jolim             #+#    #+#             */
/*   Updated: 2021/04/13 20:45:38 by jolim            ###   ########.fr       */
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
		philo->setting->table_state = ALL_ATE;
		return (true);
	}
	return (false);
}

static void	print_ms_index(unsigned long ms, int index)
{
	ft_putlu_fd(ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putlu_fd(index + 1, 1);
	ft_putchar_fd(' ', 1);
}

int			print_mutex(unsigned long ms, int action, t_philo *philo)
{
	pthread_mutex_lock(&philo->setting->print_mutex);
	if (philo->setting->table_state == ALL_ATE)
		return (ALL_ATE);
	if (action == slp)
		if (has_all_eaten(philo))
			return (ALL_ATE);
	print_ms_index(ms, philo->index);
	if (action == take || action == eat)
		ft_putendl_fd("has taken a fork", 1);
	if (action == eat)
	{
		print_ms_index(ms, philo->index);
		ft_putendl_fd("is eating", 1);
	}
	else if (action == slp)
		ft_putendl_fd("is sleeping", 1);
	else if (action == think)
		ft_putendl_fd("is thinking", 1);
	else if (action == die)
	{
		ft_putendl_fd("died", 1);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->setting->print_mutex);
	return (false);
}