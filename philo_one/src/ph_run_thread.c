/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:37:20 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 11:38:19 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ph_monitor(t_table *table)
{
	struct timeval	now;
	int				err;
	int				i;
	int				duration;

	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	i = 0;
	while (i < table->setting->num_philo)
	{
		duration = ph_get_duration(table->phs[i].last_meal, now);
		if (duration >= table->setting->time_die)
		{
			table->setting->status = DEAD;
			return (print_mutex(ph_get_duration(table->setting->start_time, \
			now), die, &table->phs[i]));
		}
		i++;
	}
	if (table->setting->status == ALL_ATE)
		return (ALL_ATE);
	return (SUCCESS);
}

static int	ph_start_table(t_table *table)
{
	int	status;

	while (1)
	{
		usleep(10);
		status = ph_monitor(table);
		if (status != SUCCESS)
			return (status);
	}
}

static int	ph_destroy_table(t_table *table, pthread_t *thrds)
{
	if (thrds)
		free(thrds);
	free_table(table, 0);
	return (SUCCESS);
}

static int	ph_init_threads(t_table *table, pthread_t **thrds)
{
	int			err;
	int			i;

	*thrds = ft_calloc(table->setting->num_philo, sizeof(pthread_t));
	if (!*thrds)
		return (print_err(MALLOC_FAIL) + ERROR);
	i = 0;
	while (i < table->setting->num_philo)
	{
		if (i % 2 == 1)
			err = pthread_create(&(*thrds)[i], NULL, odd_philo, &table->phs[i]);
		else
			err = pthread_create(&(*thrds)[i], NULL, even_philo, &table->phs[i]);
		if (err)
			return (print_err_code(THR_CREAT_FAIL, err) + \
			(int)free_null(*thrds) + ERROR);
		i++;
	}
	return (SUCCESS);
}

int			ph_run_thread(t_table *table)
{
	int			err;

	if (ph_init_threads(table, &table->thrds) == ERROR)
		return (ph_destroy_table(table, table->thrds) + ERROR);
	err = gettimeofday(&table->setting->start_time, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	table->setting->status = DINE;
	return (ph_start_table(table));
}