/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:07:14 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 14:12:55 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*ph_kill_monitor(void *param_table)
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
			break ;
		if (i == table->setting->num_philo)
		{
			usleep(50);
			i = 0;
		}
	}
	i = 0;
	if (table->done_monitor)
		kill(-1 * table->done_monitor, SIGKILL);
	return (NULL);
}

static void	ph_done_monitor(t_table *table)
{
	pid_t	table_done;
	int		wstatus;

	while (1)
	{
		table_done = fork();
		if (table_done == 0)
		{
			sem_wait(table->setting->done_sem);
			sem_post(table->setting->done_sem);
			exit(0);
		}
		else
		{
			usleep(200);
			waitpid(table_done, &wstatus, WNOHANG);
			if (WIFEXITED(wstatus))
				break ;
		}
	}
	kill(table_done, SIGKILL);
	exit(0);
}

int			ph_monitor(t_table *table)
{
	pthread_t	kill_monitor;
	int			wstatus;

	if (table->setting->num_must_eat > 0)
	{
		table->done_monitor = fork();
		if (table->done_monitor == 0)
			ph_done_monitor(table);
	}
	pthread_create(&kill_monitor, NULL, ph_kill_monitor, table);
	pthread_detach(kill_monitor);
	waitpid(table->done_monitor, &wstatus, 0);
	return (SUCCESS);
}
