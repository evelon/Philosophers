/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:58:54 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 13:56:51 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ph_kill_process(pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
		kill(pids[i++], SIGKILL);
	return (SUCCESS);
}

static int	set_start_time(t_setting *setting)
{
	struct timeval	now;
	int				err;

	err = gettimeofday(&now, NULL);
	if (err)
		return (print_err_code(TIME_GET_FAIL, err) + ERROR);
	setting->start_time = now;
	return (SUCCESS);
}

static int	init_sem(sem_t *start, sem_t *killer, t_setting *setting)
{
	int				i;

	i = 0;
	while (i < setting->num_philo)
	{
		sem_post(start);
		i++;
	}
	i = 0;
	usleep(1000);
	while (i < setting->num_philo)
	{
		sem_post(killer);
		i++;
	}
	return (SUCCESS);
}

int			ph_run_process(t_table *table, sem_t *start)
{
	pid_t			pid;
	int				i;

	table->pids = ft_calloc(table->setting->num_philo, sizeof(pid_t));
	if (!table->pids)
		return (print_err(MALLOC_FAIL) + ERROR);
	if (set_start_time(table->setting))
		return (ERROR);
	i = 0;
	while (i < table->setting->num_philo)
	{
		pid = fork();
		if (pid == -1)
			return (ph_kill_process(table->pids, --i) | ERROR);
		if (pid == 0)
			return (philo_process(&table->phs[i], start));
		table->pids[i++] = pid;
	}
	if (init_sem(start, table->phs->killer, table->setting))
		return (ERROR);
	return (ph_monitor(table));
}
