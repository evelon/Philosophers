/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 20:14:42 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 10:42:06 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	act_on_fork(enum e_action action, sem_t *forks)
{
	int	err;

	if (action = take)
		if (sem_wait(forks) + sem_wait(forks))
			return (print_err(SEM_CONT_FAIL) + ERROR);
	else
		if (sem_post(forks) + sem_post(forks))
			return (print_err(SEM_CONT_FAIL) + ERROR);
	return (SUCCESS);
}
