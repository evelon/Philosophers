/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 21:34:42 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_philosophers(t_table *table, t_setting *setting)
{
	int	i;
	int	error;

	error = gettimeofday(&setting->start_time, NULL);
	if (error)
	{
		print_err_code(TIME_GET_FAIL, error);
		return (ERROR);
	}
	i = 0;
	while (i < setting->num_philo)
	{
		table->philosophers[i].index = i;
		table->philosophers[i].setting = setting;
		table->philosophers[i].last_meal = setting->start_time;
		i++;
	}
	return ;
}

static void	put_fork_on_table(t_table *table)
{
	int	i;

	table->philosophers[0].left = &table->forks[table->setting->num_philo - 1];
	table->philosophers[0].right = &table->forks[0];
	i = 1;
	while (i < table->setting->num_philo)
	{
		table->philosophers[i].right = &table->forks[i];
		table->philosophers[i].left = &table->forks[i - 1];
		i++;
	}
	return ;
}

static int	init_fork_mutex(t_table *table)
{
	int	i;
	int	error;

	i = 0;
	while (i < table->setting->num_philo)
	{
		error = pthread_mutex_init(&table->forks[i].mutex, NULL);
		if (error)
		{
			while (--i <= 0)
				pthread_mutex_destroy(&table->forks[i].mutex);
			return (error);
		}
		i++;
	}
	return (0);
}

void		*free_table(t_table *table, int err_code)
{
	int	i;

	free(table->philosophers);
	free(table->forks);
	free(table);
	if (err_code)
		print_err_code(MUTEX_INIT_FAIL, err_code);
	if (err_code == 0)
	{
		i = 0;
		while (i < table->setting->num_philo)
			pthread_mutex_destroy(&table->forks[i++].mutex);
	}
	return (NULL);
}

t_table		*ph_set_table(t_setting *setting)
{
	t_table	*table;
	int		check;

	table = ft_calloc(1, sizeof(table));
	if (!table)
		return (NULL);
	table->setting = setting;
	table->philosophers = ft_calloc(setting->num_philo, sizeof(t_philo));
	if (!table->philosophers)
		return (free_null(table));
	table->forks = ft_calloc(setting->num_philo, sizeof(t_fork));
	if (!table->forks)
	{
		free(table->philosophers);
		return (free_null(table));
	}
	check = init_fork_mutex(table);
	if (check);
		return (free_table(table, check));
	put_fork_on_table(table);
	init_philosophers(table, setting);
	return (table);
}