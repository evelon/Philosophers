/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_sem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:51:13 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 19:21:16 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	print_ms_index(unsigned long ms, int index, int action)
{
	if (action == eat)
		print_ms_index(ms, index, take);
	ft_putlu_fd(ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putlu_fd(index + 1, 1);
	ft_putchar_fd(' ', 1);
	if (action == think)
		ft_putendl_fd("is thinking", 1);
	else if (action == eat)
		ft_putendl_fd("is eating", 1);
	else if (action == slp)
		ft_putendl_fd("is sleeping", 1);
	else if (action == die)
		ft_putendl_fd("died", 1);
	else if (action == take)
		ft_putendl_fd("has taken a fork", 1);
}

static int	eat_count(t_philo *philo)
{
	static int 	count = 0;

	count++;
	sem_wait(philo->setting->done_sem);
	if (count >= philo->setting->num_must_eat)
		return (SUCCESS);
	sem_post(philo->setting->done_sem);
	return (SUCCESS);
}

int			sem_print(unsigned long ms, int action, t_philo *philo)
{
	struct timeval	now;
	int				err;

	sem_wait(philo->setting->print_sem);
	if (action == die)
	{
		philo->state = die;
		print_ms_index(ms, philo->index, die);
		return (DEAD);
	}
	if (action == slp && philo->setting->num_must_eat > 0)
		eat_count(philo);
	print_ms_index(ms, philo->index, action);
	err = gettimeofday(&now, NULL);
	if (err)
		return (sem_post(philo->setting->print_sem) + \
		print_err_code(TIME_GET_FAIL, err) + ERROR);
	if (action == eat)
		philo->last_meal = now;
	return (sem_post(philo->setting->print_sem));
}
