/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:39:15 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 10:56:22 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>

int			free_setting(t_setting *setting)
{
	if (setting->dashboard)
		return ((int)free_null(setting->dashboard));
	if (sem_close(&setting->print_sem))
		return (print_err(SEM_CLOSE_FAIL) + ERROR);
	if (sem_unlink(PRT_NAME))
		return (print_err(SEM_UNLINK_FAIL) + ERROR);
	return (SUCCESS);
}

static int	init_setting(t_setting *setting)
{
	int	err;

	setting->dashboard = ft_calloc(setting->num_philo, sizeof(int));
	if (!setting->dashboard)
		return (print_err(MALLOC_FAIL) + ERROR);
	setting->print_sem = sem_open(PRT_NAME, O_CREAT, S_IRWXU | S_IRWXG, 1);
	if (setting->print_sem)
	{
		free(setting->dashboard);
		return (print_err(SEM_OPEN_FAIL) + ERROR);
	}
	setting->table_state = WAIT;
	return (SUCCESS);
}

static int	set_philo(t_setting *setting, int argc, char *argv[])
{
	setting->num_philo = ft_atoi(argv[1]);
	if (setting->num_philo < 2)
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

int			destroy_sem(t_table *table)
{
	int	i;

	free_setting(table->setting);
	i = 0;
	free_table(table, 0);
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
	check = ph_set_table(&table, &setting);
	if (check == ERROR)
		free_setting(&setting);
	check = ph_run_thread(&table);
	if (check == ERROR)
	{
		free_table(&table, 0);
		free_setting(&setting);
		return (1);
	}

	return (0);
}
