/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:39:15 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 21:43:39 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_setting(t_setting *setting)
{
	int	error;

	setting->dashboard = ft_calloc(setting->num_philo, sizeof(int));
	if (!setting->dashboard)
		return (print_err(MALLOC_FAIL) + ERROR);
	error = pthread_mutex_init(&setting->print_mutex, NULL);
	if (error)
	{
		free(setting->dashboard);
		return (print_err_code(MUTEX_INIT_FAIL, error) + ERROR);
	}
	return (SUCCESS);
}

static int	set_philo(t_setting *setting, int argc, char *argv[])
{
	setting->num_philo = ft_atoi(argv[1]);
	if (setting->num_philo < 2)
		return(ERROR);
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
		return (setting);
	setting->num_must_eat = ft_atoi(argv[5]);
	if (setting->num_must_eat < 1)
		return (ERROR);
	return (SUCCESS);
}

int			main(int argc, char *argv[])
{
	t_setting	setting;
	int			error;

	if (argc != 5 || argc != 6)
		return (print_err("Wrong number of arguments") + 1);
	if (set_philo(&setting, argc, argv) == ERROR)
		return (print_err("Non-integer argument") + 1);
	if (init_setting(&setting) == ERROR)
		return (1);
	return (0);
}