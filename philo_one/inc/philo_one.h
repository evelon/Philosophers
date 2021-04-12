/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:34:19 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 22:16:07 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdbool.h>
# define ERROR -1
# define FAIL -27
# define SUCCESS 0
# define LEFT -5
# define RIGHT -6
# define DEAD -99

# define MUTEX_INIT_FAIL "Failed to initiate mutex"
# define MUTEX_CONT_FAIL "Failed to control mutex"
# define TIME_GET_FAIL "Failed to get current time"
# define FORK_FAIL "Failed to set forks; code is wrong"
# define MALLOC_FAIL "Malloc failed"

/*
** t_setting represents setting of the simulation.
**
** t_philo and t_fork represents state of each philosopher and fork.
*/

typedef struct		s_setting
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_slp;
	int				num_must_eat;
	struct timeval	start_time;
	pthread_mutex_t print_mutex;
	int				*dashboard;
}					t_setting;

typedef enum		e_philo_st
{
	think,
	eat,
	sleep,
	die
}					t_philo_st;

typedef struct		s_philo
{
	int				index;
	enum e_philo_st	state;
	struct timeval	last_meal;
	t_fork			*left;
	t_fork			*right;
	t_setting		*setting;
}					t_philo;

enum				e_fork_st
{
	laid = die + 1,
	taken
};

typedef struct		s_fork
{
	enum e_fork_st	state;
	pthread_mutex_t	mutex;
}					t_fork;

enum				e_action
{
	lay = taken + 1,
	take
};

typedef struct		s_table
{
	t_philo			*philosophers;
	t_fork			*forks;
	t_setting		*setting;
	struct timeval	start_time;
}					t_table;

/*
**
*/

int					print_mutex(int ms, int action, t_philo *philo);

/*
**
*/

int					odd_philo_liftcycle(t_philo *philo);
int					even_philo_liftcycle(t_philo *philo);

/*
** act_on_fork can changes a state of fork. when action is lay and fork is
** taken, fork can be changed into state laid. when action is take and fork is
** laid, for can be change into state taken.
*/

int					act_on_fork(enum e_action action, t_fork *fork);

/*
** ph_set_table initializes philosophers and forks
*/

t_table				*ph_set_table(t_setting *setting);
void				*free_table(t_table *table, int err_code);

/*
** ph_get_duration returns how many ms elapsed after 'start'
*/

int					ph_get_duration(struct timeval last, struct timeval now);

/*
** Print functions
*/

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
int					print_err(const char *err_str);
int					print_err_code(const char *err_str, int err_code);


/*
** Util functions
*/

int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
void				*free_null(void *ptr);

#endif