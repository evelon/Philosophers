/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_over.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:49:16 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 16:17:13 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ph_over(t_table *table)
{
	int	i;
	int	*ret;

	pthread_mutex_unlock(&table->setting->print_mutex);
	i = 0;
	while (i < table->setting->num_philo)
	{
		pthread_join(table->thrds[i++], (void **)&ret);
		if (ret != NULL)
		{
			print_err("something wrong!!!!");
			return (ERROR);
		}
	}
	free_table(table, 0);
	free_setting(table->setting);
	return (SUCCESS);
}