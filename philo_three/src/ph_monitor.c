/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:07:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 18:16:38 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*ph_kill_monitor(void *param_table)
{
	t_table	*table;
	int		i;
	int		wstatus;

	table = (t_table *)param_table;
	i = 0;
	while (1)
	{
		waitpid(table->pids[i++], &wstatus, WNOHANG);
		if (WIFEXITED(wstatus))
			break;
		if (i == table->setting->num_philo)
		{
			usleep(50);
			i = 0;
		}
	}
	i = 0;
	while (i < table->setting->num_philo)
		sem_post(table->phs[i++].done);
	return (NULL);
}

void	*ph_monitor(void *param_table)
{
	t_table		*table;
	pthread_t	thread;
	int			i;

	pthread_create(&thread, NULL, ph_kill_monitor, param_table);
	pthread_detach(thread);
	table = (t_table *)param_table;
	i = 0;
	while (i < table->setting->num_philo)
	{
		// ft_putlu_fd((unsigned long)i, 1);
		// ft_putlu_fd((unsigned long)table->phs[i].done, 1);
		sem_wait(table->phs[i++].done);
	}
	ph_kill_process(table->pids, table->setting->num_philo);
	return (SUCCESS);
}

void	*ph_killer(void *param_philo)
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
