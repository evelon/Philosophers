/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_over.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:49:16 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 17:42:19 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdio.h>

int	ph_over(t_table *table)
{
	int	i;
	int	*ret;

	i = 0;
	while (i < table->setting->num_philo)
	{
		pthread_join(table->thrds[i++], (void **)&ret);
		ft_putlu_fd((unsigned long)i, 1);
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