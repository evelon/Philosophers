/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:41:36 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 17:13:05 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	odd_philo_lifecycle(t_philo *philo)
{
	if (take_fork(LEFT, philo) != SUCCESS)
		return (ERROR);
	if (take_fork(RIGHT, philo) != SUCCESS)
		return (ERROR);
	return (philo_eat_sleep(philo));
}

static int	even_philo_lifecycle(t_philo *philo)
{
	if (take_fork(RIGHT, philo) != SUCCESS)
		return (ERROR);
	if (take_fork(LEFT, philo) != SUCCESS)
		return (ERROR);
	return (philo_eat_sleep(philo));
}

void		*odd_philo(void *philo)
{
	t_philo			*cast;
	struct timeval	*time;

	cast = (t_philo *)philo;
	time = &cast->setting->start_time;
	while (1)
	{
		usleep(5);
		if (cast->setting->status != WAIT)
			break ;
	}
	cast->last_meal = *time;
	while (1)
		if (odd_philo_lifecycle(philo) != SUCCESS)
			break ;
	return (NULL);
}

void		*even_philo(void *philo)
{
	t_philo			*cast;
	struct timeval	*time;

	cast = (t_philo *)philo;
	time = &cast->setting->start_time;
	while (1)
	{
		usleep(5);
		if (cast->setting->status != WAIT)
			break ;
	}
	cast->last_meal = *time;
	while (1)
		if (even_philo_lifecycle(philo) != SUCCESS)
			break ;
	return (NULL);
}
