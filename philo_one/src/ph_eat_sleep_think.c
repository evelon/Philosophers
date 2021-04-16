/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat_sleep_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:56:51 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 13:48:56 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	print_take(int hand, t_philo *philo)
{
	struct timeval	now;
	int				err;

	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	if ((philo->index % 2 == 1 && hand == LEFT) || \
		(philo->index % 2 == 0 && hand == RIGHT))
		return (print_mutex(ph_get_duration(philo->setting->start_time,\
			now), take, philo));
	else
		return (print_mutex(ph_get_duration(philo->setting->start_time,\
			now), eat, philo));
}

int			take_fork(int hand, t_philo *philo)
{
	int				err;

	while (1)
	{
		if (hand == RIGHT)
			err = act_on_fork(take, philo->right, philo->setting->status);
		else
			err = act_on_fork(take, philo->left, philo->setting->status);
		if (err == SUCCESS)
		{
			print_take(hand, philo);
			break ;
		}
		if (err != FAIL)
			return (print_err_code(MUTEX_CONT_FAIL, err) + ERROR);
	}
	return (SUCCESS);
}

static int	lay_fork(t_philo *philo)
{
	int	err;
	int	count;

	count = 0;
	while (1)
	{
		err = act_on_fork(lay, philo->left, philo->setting->status);
		if (err == ERROR)
			return (print_err(FORK_FAIL) + ERROR);
		else
			count++;
		if (count == 2)
			return (SUCCESS);
		err = act_on_fork(lay, philo->right, philo->setting->status);
		if (err == ERROR)
			return (print_err(FORK_FAIL) + ERROR);
		else
			count++;
		if (count == 2)
			return (SUCCESS);
	}
}

int			philo_eat_sleep(t_philo *philo)
{
	struct timeval	now;
	int				err;

	ph_sleep_precise(philo->setting->time_eat);
	lay_fork(philo);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	err = print_mutex(ph_get_duration(philo->setting->start_time, now), \
		slp, philo);
	if (err != SUCCESS)
		return (err);
	ph_sleep_precise(philo->setting->time_slp);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	err = print_mutex(ph_get_duration(philo->setting->start_time, now), \
		think, philo);
	return (err);
}
