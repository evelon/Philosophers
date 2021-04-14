/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 10:57:21 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_philosophers(t_table *table, t_setting *setting, sem_t *forks)
{
	int	i;

	i = 0;
	while (i < setting->num_philo)
	{
		table->phs[i].index = i;
		table->phs[i].setting = setting;
		table->phs[i].forks = forks;
		i++;
	}
	return (SUCCESS);
}

void		*free_table(t_table *table, int err_code)
{
	int	i;

	free(table->phs);
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

int			ph_set_table(t_table *table, t_setting *setting)
{
	int		check;
	sem_t	*forks;

	table->setting = setting;
	table->phs = ft_calloc(setting->num_philo, sizeof(t_philo));
	if (!table->phs)
		return (ERROR);
	if (sem_open(FORK_NAME, O_CREAT, S_IRWXU | S_IRWXG, setting->num_philo));
		return ((int)free_null(table->phs) + ERROR);
	init_philosophers(table, setting);
	return (SUCCESS);
}