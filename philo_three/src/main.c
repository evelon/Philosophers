/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:39:15 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 17:40:51 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			free_setting(t_setting *setting)
{
	if (sem_close(setting->print_sem))
		return (print_err(SEM_CLOSE_FAIL) + ERROR);
	if (sem_unlink(PRT_NAME))
		return (print_err(SEM_UNLINK_FAIL) + ERROR);
	// if (sem_close(setting->elapsed_time))
	// 	return (print_err(SEM_CLOSE_FAIL) + ERROR);
	// if (sem_unlink(TIME_NAME))
	// 	return (print_err(SEM_UNLINK_FAIL) + ERROR);
	return (SUCCESS);
}

static int	init_setting(t_setting *setting)
{
	sem_unlink(PRT_NAME);
	setting->print_sem = sem_open(PRT_NAME, O_CREAT | O_EXCL | O_TRUNC, \
		0700, 1);
	if (!setting->print_sem)
		return (print_err(SEM_OPEN_FAIL) + ERROR);
	// sem_unlink(TIME_NAME);
	// setting->elapsed_time = sem_open(TIME_NAME, O_CREAT | O_EXCL | O_TRUNC, \
	// 	0700, 0);
	// if (!setting->elapsed_time)
	// {
	// 	sem_close(setting->print_sem);
	// 	sem_unlink(PRT_NAME);
	// 	return(print_err(SEM_OPEN_FAIL) + ERROR);
	// }
	return (SUCCESS);
}

static int	set_philo(t_setting *setting, int argc, char *argv[])
{
	setting->num_philo = ft_atoi(argv[1]);
	if (setting->num_philo < 1)
		return (ERROR);
	setting->time_die = ft_atoi(argv[2]);
	if (setting->time_die < 1)
		return (ERROR);
	setting->time_eat = ft_atoi(argv[3]);
	if (setting->time_eat < 1)
		return (ERROR);
	setting->time_slp = ft_atoi(argv[4]);
	if (setting->time_slp < 1)
		return (ERROR);
	if (argc != 6)
	{
		setting->num_must_eat = -1;
		return (SUCCESS);
	}
	setting->num_must_eat = ft_atoi(argv[5]);
	if (setting->num_must_eat < 1)
		return (ERROR);
	return (SUCCESS);
}

int			ph_run(t_table *table)
{
	sem_t		*start;
	pthread_t	monitor;
	int			err;
	void		*ret;

	sem_unlink(START_NAME);
	start = sem_open(START_NAME, O_CREAT | O_EXCL | O_TRUNC, 0777, 0);
	if (!start)
		return (print_err(SEM_OPEN_FAIL) + ERROR);
	if (ph_run_process(table, start) != SUCCESS)
		return (print_err("Something wrong!!!") + ERROR);
	err = pthread_create(&monitor, NULL, ph_monitor, table);
	if (err)
		return (print_err(THR_CREAT_FAIL) +ERROR);
	err = pthread_join(monitor, &ret);
	if (ret != NULL)
		return (print_err(THR_JOIN_FAIL) + ERROR);
	return (SUCCESS);
}

int			main(int argc, char *argv[])
{
	t_setting	setting;
	t_table		table;
	int			check;

	if (argc != 5 && argc != 6)
		return (print_err("Wrong number of arguments") + 1);
	if (set_philo(&setting, argc, argv) == ERROR)
		return (print_err("Non-integer or non-positive argument") + 1);
	if (init_setting(&setting) == ERROR)
		return (1);
	if (ph_set_table(&table, &setting) == ERROR)
		free_setting(&setting);
	check = ph_run(&table);
	if (check == ERROR)
	{
		free_setting(&setting);
		free_table(&table, 0);
		return (1);
	}
	if (ph_over(&table) == ERROR)
		return (1);
	return (0);
}
