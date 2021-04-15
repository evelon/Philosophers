/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:58:54 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 15:31:07 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"



int			ph_kill_process(pid_t *pids, int n)
{
	int	wstatus;
	int	i;
	int	err;

	i = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &wstatus, WNOHANG) == -1 || WIFEXITED(wstatus))
			continue ;
		err = kill(pids[i++], SIGKILL);
		if (err)
			return (print_err(P_KILL_FAIL) + ERROR);
	}
	return (SUCCESS);
}

int			ph_run_process(t_table *table, sem_t *start)
{
	int		i;
	pid_t	pid;

	table->pids = ft_calloc(table->setting->num_philo, sizeof(pid_t));
	if (!table->pids)
		return (print_err(MALLOC_FAIL) + ERROR);
	i = 0;
	while (i < table->setting->num_philo)
	{
		pid = fork();
		if (pid == -1)
			return (ph_kill_process(table->pids, --i) | ERROR);
		if (pid == 0)
			return (philo_process(&table->phs[i], start));
		table->pids[i] = pid;
		i++;
	}
	i = 0;
	while (i < table->setting->num_philo)
		sem_post(start);
	return (SUCCESS);
}
