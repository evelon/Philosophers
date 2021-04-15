/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:14:42 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 14:43:29 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	take_fork(t_philo *philo)
{
	struct timeval	now;
	int				err;

	sem_wait(philo->forks);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	sem_print(ph_get_duration(philo->setting->start_time, now), \
	take, philo);
	sem_wait(philo->forks);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	sem_print(ph_get_duration(philo->setting->start_time, now), \
	eat, philo);
	return (SUCCESS);
}

int			act_on_fork(enum e_action action, t_philo *philo)
{
	struct timeval	now;
	int				err;

	if (action == take)
		return (take_fork(philo));
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (sem_print(ph_get_duration(philo->setting->start_time, now), \
	slp, philo));
}
