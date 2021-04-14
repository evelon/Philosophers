/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 14:58:27 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	init_philosophers(t_table *table, sem_t *forks)
{
	int	i;

	i = 0;
	while (i < table->setting->num_philo)
	{
		table->phs[i].index = i;
		table->phs[i].setting = table->setting;
		table->phs[i].forks = forks;
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
	}
	free(table->phs);
	return ;
}

int			ph_set_table(t_table *table, t_setting *setting)
{
	sem_t	*forks;

	table->setting = setting;
	table->phs = ft_calloc(setting->num_philo, sizeof(t_philo));
	if (!table->phs)
		return (ERROR);
	forks = sem_open(FORK_NAME, O_CREAT | O_EXCL, \
	S_IRWXU | S_IRWXG, setting->num_philo);
	if (!forks)
		return ((int)free_null(table->phs) + ERROR);
	init_philosophers(table, forks);
	return (SUCCESS);
}