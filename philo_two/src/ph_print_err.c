/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:10:40 by jolim             #+#    #+#             */
/*   Updated: 2021/04/12 18:50:26 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	print_err(char *err_str)
{
	ft_putendl_fd(err_str, 2);
	return (false);
}

int	print_err_code(char *err_str, int err_code)
{
	ft_putstr_fd(err_str, 2);
	ft_putstr_fd(": error_code ", 2);
	ft_putlu_fd(err_code, 2);
	ft_putchar_fd('\n', 2);
	return (false);
}
