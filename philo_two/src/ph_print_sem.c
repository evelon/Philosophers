/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_sem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:51:13 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 14:11:50 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

static void	print_ms_index(unsigned long ms, int index, int action)
{
	if (action == eat)
		print_ms_index(ms, index, take);
	ft_putlu_fd(ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putlu_fd(index + 1, 1);
	ft_putchar_fd(' ', 1);
	if (action == think)
		ft_putendl_fd("is thinking", 1);
	else if (action == eat)
		ft_putendl_fd("is eating", 1);
	else if (action == slp)
		ft_putendl_fd("is sleeping", 1);
	else if (action == die)
		ft_putendl_fd("died", 1);
	else if (action == take)
		ft_putendl_fd("has taken a fork", 1);
}

int			sem_print(unsigned long ms, int action, t_philo *philo)
{
	struct timeval	now;
	int				err;

	sem_wait(philo->setting->print_sem);
	if (action == die)
	{
		print_ms_index(ms, philo->index, die);
		return (sem_post(philo->setting->print_sem) + DEAD);
	}
	if (philo->setting->status != DINE)
	{
		sem_post(philo->forks);
		return (sem_post(philo->setting->print_sem) + philo->setting->status);
	}
	if (action == slp)
		if (has_all_eaten(philo))
			return (sem_post(philo->setting->print_sem) + ALL_ATE);
	print_ms_index(ms, philo->index, action);
	err = gettimeofday(&now, NULL);
	if (err)
		return (sem_post(philo->setting->print_sem) + \
			print_err_code(TIME_GET_FAIL, err) + ERROR);
	if (action == eat)
		philo->last_meal = now;
	return (sem_post(philo->setting->print_sem));
}
