/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 16:33:15 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_philosophers(t_table *table, t_setting *setting)
{
	int	i;

	i = 0;
	while (i < setting->num_philo)
	{
		table->phs[i].index = i;
		table->phs[i].setting = setting;
		i++;
	}
	return (SUCCESS);
}

static void	put_fork_on_table(t_table *table)
{
	int	i;

	table->phs[0].left = &table->forks[table->setting->num_philo - 1];
	table->phs[0].right = &table->forks[0];
	i = 1;
	while (i < table->setting->num_philo)
	{
		table->phs[i].right = &table->forks[i];
		table->phs[i].left = &table->forks[i - 1];
		i++;
	}
	return ;
}

static int	init_fork_mutex(t_table *table)
{
	int	i;
	int	err;

	i = 0;
	while (i < table->setting->num_philo)
	{
		err = pthread_mutex_init(&table->forks[i].mutex, NULL);
		if (err)
		{
			while (--i <= 0)
				pthread_mutex_destroy(&table->forks[i].mutex);
			return (err);
		}
		i++;
	}
	return (0);
}

void		*free_table(t_table *table, int err_code)
{
	free(table->phs);
	free(table->forks);
	if (err_code)
		print_err_code(MUTEX_INIT_FAIL, err_code);
	return (NULL);
}

int			ph_set_table(t_table *table, t_setting *setting)
{
	int		check;

	table->setting = setting;
	table->phs = ft_calloc(setting->num_philo, sizeof(t_philo));
	if (!table->phs)
		return (ERROR);
	table->forks = ft_calloc(setting->num_philo, sizeof(t_fork));
	if (!table->forks)
		return ((int)free_null(table->phs) + ERROR);
	check = init_fork_mutex(table);
	if (check)
		return ((int)free_table(table, check));
	put_fork_on_table(table);
	init_philosophers(table, setting);
	return (SUCCESS);
}