/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 19:24:04 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	init_philosophers(t_table *table, sem_t *forks, sem_t *killer)
{
	int		i;

	i = 0;
	while (i < table->setting->num_philo)
	{
		table->phs[i].index = i;
		table->phs[i].setting = table->setting;
		table->phs[i].forks = forks;
		table->phs[i].killer = killer;
		i++;
	}
	return (SUCCESS);
}

void		free_table(t_table *table, int err_code)
{
	if (err_code == 0)
	{
		if (sem_close(table->phs->forks))
			print_err(SEM_CLOSE_FAIL);
		if (sem_unlink(FORK_NAME))
			print_err(SEM_UNLINK_FAIL);
		if (sem_close(table->phs->killer))
			print_err(SEM_CLOSE_FAIL);
		if (sem_unlink(KILLER_NAME))
			print_err(SEM_UNLINK_FAIL);
	}
	ph_kill_process(table->pids, table->setting->num_philo);
	free(table->phs);
	return ;
}

int			ph_set_table(t_table *table, t_setting *setting)
{
	sem_t	*forks;
	sem_t	*killer;

	table->setting = setting;
	table->phs = ft_calloc(setting->num_philo, sizeof(t_philo));
	if (!table->phs)
		return (ERROR);
	sem_unlink(FORK_NAME);
	forks = sem_open(FORK_NAME, O_CREAT | O_EXCL | O_TRUNC, 0777, \
		setting->num_philo);
	if (!forks)
		return ((int)free_null(table->phs) + ERROR);
	sem_unlink(KILLER_NAME);
	killer = sem_open(KILLER_NAME, O_CREAT | O_EXCL | O_TRUNC, 0777, 0);
	init_philosophers(table, forks, killer);
	return (SUCCESS);
}
