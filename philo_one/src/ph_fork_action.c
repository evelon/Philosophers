/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:14:42 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 17:18:50 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	act_on_fork(enum e_action action, t_fork *fork)
{
	int	error;

	error = pthread_mutex_lock(&fork->mutex);
	if (error)
		return (error);
	if (action == take)
	{
		if (fork->state == taken)
		{
			error = pthread_mutex_unlock(&fork->mutex);
			if (error)
				return (error);
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
