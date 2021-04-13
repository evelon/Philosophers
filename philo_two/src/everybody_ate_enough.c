/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everybody_ate_enough.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:49:16 by jolim             #+#    #+#             */
/*   Updated: 2021/04/13 21:57:44 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	everybody_ate_enough(t_table *table)
{
	int	i;
	int	*ret;

	pthread_mutex_unlock(&table->setting->print_mutex);
	i = 0;
	while (i < table->setting->num_philo)
	{
		pthread_join(table->thrds[i++], (void **)&ret);
		if ((int)ret != ALL_ATE)
		{
			print_err("something wrong!!!!");
			return (ERROR);
		}
	}
	free_table(table, 0);
	free_setting(table->setting);
	return (SUCCESS);
}