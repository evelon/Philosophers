/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:14:42 by jolim             #+#    #+#             */
/*   Updated: 2021/04/12 15:41:06 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	act_on_fork(enum e_action action, t_fork *fork)
{
	int	err;

	err = pthread_mutex_lock(&fork->mutex);
	if (err)
		return (err);
	if (action == take)
	{
		if (fork->state == taken)
		{
			err = pthread_mutex_unlock(&fork->mutex);
			if (err)
				return (err);
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
