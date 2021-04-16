/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:14:42 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 15:16:40 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	act_on_fork(enum e_action action, t_fork *fork, int stat)
{
	if (stat != DINE)
		return (SUCCESS);
	if (pthread_mutex_lock(&fork->mutex))
		return (ERROR);
	if (action == take)
	{
		if (fork->state == taken)
		{
			if (pthread_mutex_unlock(&fork->mutex))
				return (ERROR);
			return (FAIL);
		}
		fork->state = taken;
		return (pthread_mutex_unlock(&fork->mutex));
	}
	if (fork->state == laid)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (ERROR);
	}
	fork->state = laid;
	return (pthread_mutex_unlock(&fork->mutex));
}
