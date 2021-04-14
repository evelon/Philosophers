/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:41:36 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 17:49:50 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*odd_philo(void *philo)
{
	t_philo			*cast;
	struct timeval	*time;
	int				stat;

	cast = (t_philo *)philo;
	time = &cast->setting->start_time;
	while (1)
	{
		usleep(5);
		if (cast->setting->status != WAIT)
			break;
	}
	cast->last_meal = *time;
	while (1)
	{
		stat = philo_liftcycle(philo);
		if (stat == ALL_ATE)
			sem_post(cast->setting->print_sem);
		if (stat != SUCCESS)
			break;
	}
	return (NULL);
}

void	*even_philo(void *philo)
{
	t_philo			*cast;
	struct timeval	*time;
	int				stat;

	cast = (t_philo *)philo;
	time = &cast->setting->start_time;
	while (1)
	{
		usleep(10);
		if (cast->setting->status != WAIT)
			break;
	}
	cast->last_meal = *time;
	usleep(100);
	while (1)
	{
		stat = philo_liftcycle(philo);
		if (stat == ALL_ATE)
			sem_post(cast->setting->print_sem);
		if (stat != SUCCESS)
			break;
	}
	return (NULL);
}
