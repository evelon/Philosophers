/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:41:36 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 22:39:13 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*ph_killer(void *param_philo)
{
	t_philo			*philo;
	struct timeval	now;
	int				err;

	philo = (t_philo *)param_philo;
	sem_wait(philo->killer);
	while (1)
	{
		usleep(50);
		if (philo->state == die)
			return (NULL);
		err = gettimeofday(&now, NULL);
		if (err)
			return ((void *)(long long)print_err(TIME_GET_FAIL));
		if (ph_get_duration(philo->last_meal, now) >= philo->setting->time_die)
		{
			sem_print(ph_get_duration(philo->setting->start_time, \
			now), die, philo);
			exit(0);
		}
	}
	return (NULL);
}

static int	philo_eat_sleep(t_philo *philo)
{
	struct timeval	now;
	int				err;

	ph_sleep_precise(philo->setting->time_eat);
	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
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

static int	philo_liftcycle(t_philo *philo)
{
	if (act_on_fork(take, philo))
		return (ERROR);
	return (philo_eat_sleep(philo));
}

static int	run_philo(t_philo *philo, sem_t *start_sem)
{
	// struct timeval	now;
	// int				err;

	sem_wait(start_sem);
	// err = gettimeofday(&now, NULL);
	// if (err)
	// 	return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	// philo->setting->start_time = now;
	philo->last_meal = philo->setting->start_time;
	if (philo->index % 2 == 0)
		usleep(10);
	while (1)
		if (philo_liftcycle(philo) != SUCCESS)
			break ;
	return (SUCCESS);
}

int			philo_process(t_philo *philo, sem_t *start)
{
	pthread_t		thread;
	void			*ret;
	int				err;

	err = pthread_create(&thread, NULL, ph_killer, philo);
	if (err)
		return (print_err_code(THR_CREAT_FAIL, err) + ERROR);
	err = run_philo(philo, start);
	pthread_join(thread, &ret);
	if (ret != NULL)
		return (print_err("Something wrong!!!") + ERROR);
	return (err);
}
