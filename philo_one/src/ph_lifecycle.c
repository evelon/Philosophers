/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lifecycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:56:51 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 22:17:02 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	take_fork(int hand, t_philo *philo)
{
	struct timeval	now;
	int				error;

	while (1)
	{
		if (hand = RIGHT)
			error = act_on_fork(take, philo->right);
		else
			error = act_on_fork(take, philo->left);
		if (error == SUCCESS)
		{
			error = gettimeofday(&now, NULL);
			if (error)
				return (print_err_code(TIME_GET_FAIL, error) + ERROR);
			if ((philo->index % 2 == 1 && hand == LEFT) || \
				philo->index % 2 == 0 && hand == RIGHT)
				print_mutex(ph_get_duration(philo->setting->start_time, now), \
				take, philo);
			else
				print_mutex(ph_get_duration(philo->setting->start_time, now), \
				eat, philo);
			break;
		}
		if (error != FAIL)
			return (print_err_code(MUTEX_CONT_FAIL, error) + ERROR);
	}
	return (SUCCESS);
}

static int	lay_fork(t_philo *philo)
{
	int	error;
	int	count;

	count = 0;
	while (1)
	{
		error = act_on_fork(lay, philo->left);
		if (error == ERROR)
			return (print_err(FORK_FAIL) + ERROR);
		else
			count++;
		if (count == 2)
			return (SUCCESS);
		error = act_on_fork(lay, philo->right);
		if (error == ERROR)
			return (print_err(FORK_FAIL) + ERROR);
		else
			count++;
		if (count == 2)
			return (SUCCESS);
	}
}

int			odd_philo_liftcycle(t_philo *philo)
{
	int				error;
	struct timeval	now;

	if (take_fork(LEFT, philo) != SUCCESS)
		return (ERROR);
	if (gettimeofday(&now, NULL))
		return (print_err_code(TIME_GET_FAIL, error) + ERROR);
	if (take_fork(RIGHT, philo) != SUCCESS)
		return (ERROR);
	usleep(philo->setting->time_eat);
	lay_fork(philo);
	if (gettimeofday(&now, NULL))
		return (print_err_code(TIME_GET_FAIL, error) + ERROR);
	if (print_mutex(ph_get_duration(philo->setting->start_time, now), \
	sleep, philo) == true)
		return (true);
	philo->last_meal = now;
	usleep(philo->setting->time_slp);
	if (gettimeofday(&now, NULL))
		return (print_err_code(TIME_GET_FAIL, error) + ERROR);
	print_mutex(ph_get_duration(philo->setting->start_time, now), think, philo);
	return (SUCCESS);
}

int			even_philo_liftcycle(t_philo *philo)
{
	int				error;
	struct timeval	now;

	if (take_fork(RIGHT, philo) != SUCCESS)
		return (ERROR);
	if (gettimeofday(&now, NULL))
		return (print_err_code(TIME_GET_FAIL, error) + ERROR);
	if (take_fork(LEFT, philo) != SUCCESS)
		return (ERROR);
	usleep(philo->setting->time_eat);
	lay_fork(philo);
	if (gettimeofday(&now, NULL))
		return (print_err_code(TIME_GET_FAIL, error) + ERROR);
	print_mutex(ph_get_duration(philo->setting->start_time, now), sleep, philo);
	philo->last_meal = now;
	usleep(philo->setting->time_slp);
	if (gettimeofday(&now, NULL))
		return (print_err_code(TIME_GET_FAIL, error) + ERROR);
	print_mutex(ph_get_duration(philo->setting->start_time, now), think, philo);
	return (SUCCESS);
}
