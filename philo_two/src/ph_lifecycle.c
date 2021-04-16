/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_lifecycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:56:51 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 15:46:26 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	philo_eat_sleep(t_philo *philo)
{
	struct timeval	now;
	int				err;

	ph_sleep_precise(philo->setting->time_eat);
	if (act_on_fork(lay, philo))
		return (ERROR);
	ph_sleep_precise(philo->setting->time_slp);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	err = sem_print(ph_get_duration(philo->setting->start_time, now), \
	think, philo);
	return (err);
}

int			philo_liftcycle(t_philo *philo)
{
	if (act_on_fork(take, philo))
		return (ERROR);
	return (philo_eat_sleep(philo));
}
