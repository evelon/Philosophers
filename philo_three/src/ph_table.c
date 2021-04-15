/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:01:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 15:13:23 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static char	*done_name(int n)
{
	int		scale;
	int		len;
	int		temp;
	char	*name;
	int		i;

	temp = n / 10;
	len = 1;
	scale = 1;
	while (temp /= 10)
	{
		len++;
		scale *= 10;
	}
	name = ft_calloc(scale + 2, sizeof(char));
	name[0] = '/';
	i = 1;
	while (i < len + 1)
	{
		name[i++] = n / scale + '0';
		n -= n / scale * scale;
		scale /= 10;
	}
	name[i] = '\0';
	write(1, name, len + 1);
	return (name);
}

static int	init_philosophers(t_table *table, sem_t *forks)
{
	int		i;
	char	*phs_done_name;

	i = 0;
	while (i < table->setting->num_philo)
	{
		table->phs[i].index = i;
		table->phs[i].setting = table->setting;
		table->phs[i].forks = forks;
		if (table->setting->num_must_eat > 0)
		{
			phs_done_name = done_name(i);
			sem_unlink(phs_done_name);
			table->phs[i].done = sem_open(done_name(i), \
			O_CREAT | O_EXCL | O_TRUNC, 0777, 0);
		}
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
		ph_kill_process(table->pids, table->setting->num_philo);
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
	sem_unlink(FORK_NAME);
	forks = sem_open(FORK_NAME, O_CREAT | O_EXCL | O_TRUNC, 0700, \
	setting->num_philo);
	if (!forks)
		return ((int)free_null(table->phs) + ERROR);
	init_philosophers(table, forks);
	return (SUCCESS);
}
