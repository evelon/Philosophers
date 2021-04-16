/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lifecycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:56:51 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 14:05:25 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	take_fork(int hand, t_philo *philo)
{
	struct timeval	now;
	int				err;

	while (1)
	{
		if (hand == RIGHT)
			err = act_on_fork(take, philo->right, philo->setting->status);
		else
			err = act_on_fork(take, philo->left, philo->setting->status);
		if (err == SUCCESS)
		{
			err = gettimeofday(&now, NULL);
			if (err)
				return (print_err_code(TIME_GET_FAIL, err) + ERROR);
			if ((philo->index % 2 + hand))
				print_mutex(ph_get_duration(philo->setting->start_time, now), \
					take, philo);
			else
				print_mutex(ph_get_duration(philo->setting->start_time, now), \
					eat, philo);
			return (SUCCESS);
		}
		if (err != FAIL)
			return (print_err_code(MUTEX_CONT_FAIL, err) + ERROR);
	}
}

static int	lay_fork(t_philo *philo)
{
	int	err;
	int	count;

	count = 0;
	while (1)
	{
		err = act_on_fork(lay, philo->left);
		if (err == ERROR)
			return (print_err(FORK_FAIL) + ERROR);
		else
			count++;
		if (count == 2)
			return (SUCCESS);
		err = act_on_fork(lay, philo->right);
		if (err == ERROR)
			return (print_err(FORK_FAIL) + ERROR);
		else
			count++;
		if (count == 2)
			return (SUCCESS);
	}
}

static int	philo_eat_sleep(t_philo *philo)
{
	struct timeval	now;
	int				err;

	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	philo->last_meal = now;
	ph_sleep_precise(philo->setting->time_eat);
	lay_fork(philo);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	if (print_mutex(ph_get_duration(philo->setting->start_time, now), \
		slp, philo) == ALL_ATE)
		return (ALL_ATE);
	ph_sleep_precise(philo->setting->time_slp);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	print_mutex(ph_get_duration(philo->setting->start_time, now), think, philo);
	return (SUCCESS);
}

int			odd_philo_liftcycle(t_philo *philo)
{
	if (take_fork(LEFT, philo) != SUCCESS)
		return (ERROR);
	if (take_fork(RIGHT, philo) != SUCCESS)
		return (ERROR);
	return (philo_eat_sleep(philo));
}

int			even_philo_liftcycle(t_philo *philo)
{
	if (take_fork(RIGHT, philo) != SUCCESS)
		return (ERROR);
	if (take_fork(LEFT, philo) != SUCCESS)
		return (ERROR);
	return (philo_eat_sleep(philo));
}
