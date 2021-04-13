/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:41:36 by jolim             #+#    #+#             */
/*   Updated: 2021/04/13 20:04:14 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*odd_philo(void *philo)
{
	t_philo			*cast;
	struct timeval	*time;

	cast = (t_philo *)philo;
	time = &cast->setting->start_time;
	while (1)
	{
		usleep(5);
		if (cast->setting->table_state != WAIT)
			break;
	}
	cast->last_meal = *time;
	while (1)
		if (odd_philo_liftcycle(philo) == true)
			break;
	return (NULL);
}

void	*even_philo(void *philo)
{
	t_philo			*cast;
	struct timeval	*time;

	cast = (t_philo *)philo;
	time = &cast->setting->start_time;
	while (1)
	{
		usleep(5);
		if (cast->setting->table_state != WAIT)
			break;
	}
	cast->last_meal = *time;
	while (1)
		if (even_philo_liftcycle(philo) == true)
			break;
	return (NULL);
}
