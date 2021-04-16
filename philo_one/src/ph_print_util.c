/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:23:59 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 13:49:02 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putendl_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

static void	putdigit_re(unsigned long n, int fd)
{
	int	digit;

	if (n == 0)
		return ;
	digit = n % 10;
	if (digit < 0)
		digit = -1 * digit;
	digit += '0';
	putdigit_re(n / 10, fd);
	write(fd, &digit, 1);
}

void		ft_putlu_fd(unsigned long n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	putdigit_re(n, fd);
}

void		ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}
