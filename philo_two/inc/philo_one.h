/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:34:19 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 10:55:49 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# include <stdbool.h>
# define ERROR -1
# define FAIL -27
# define SUCCESS 0
# define LEFT -5
# define RIGHT -6

# define WAIT 0
# define DINE -98
# define DEAD -99
# define ALL_ATE -100

# define SEM_OPEN_FAIL "Failed to open semaphore"
# define SEM_CONT_FAIL "Failed to control semaphore"
# define SEM_CLOSE_FAIL "Failed to close semaphore"
# define SEM_UNLINK_FAIL "Failed to unlink semaphore"
# define TIME_GET_FAIL "Failed to get current time"
# define FORK_FAIL "Failed to set forks; code is wrong"
# define MALLOC_FAIL "Malloc failed"
# define THR_CREAT_FAIL "Failed to create a thread"

# define PRT_NAME "print_sem"
# define FORK_NAME "fork_sem"

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
	sem_t			print_sem;
	int				*dashboard;
	int				table_state;
}					t_setting;

typedef enum		e_philo_st
{
	think,
	eat,
	slp,
	die
}					t_philo_st;

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

typedef struct		s_philo
{
	int				index;
	enum e_philo_st	state;
	struct timeval	last_meal;
	sem_t			*forks;
	t_setting		*setting;
}					t_philo;

enum				e_action
{
	lay = taken + 1,
	take
};

typedef struct		s_table
{
	t_philo			*phs;
	t_setting		*setting;
	pthread_t		*thrds;
}					t_table;

/*
**
*/

int					ph_run_thread(t_table *table);

int					everybody_ate_enough(t_table *table);
int					free_setting(t_setting *setting);

/*
** print_mutex is a mutexed printer, which only can be used by one thread only.
*/
int					print_mutex(unsigned long ms, int action, t_philo *philo);

/*
**
*/
void				*odd_philo(void *philo);
void				*even_philo(void *philo);
int					odd_philo_liftcycle(t_philo *philo);
int					even_philo_liftcycle(t_philo *philo);

/*
** act_on_fork changes the number of forks, which equals to the value of
** the corresponding semaphore.
*/
int					act_on_fork(enum e_action action, sem_t *forks);

/*
** ph_set_table initializes philosophers and forks
*/
int					ph_set_table(t_table *table, t_setting *setting);
void				*free_table(t_table *table, int err_code);

/*
** ph_get_duration returns how many ms elapsed after 'start'
*/
unsigned long		ph_get_duration(struct timeval last, struct timeval now);
void				ph_sleep_precise(int ms);

/*
** Print functions
*/
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putlu_fd(unsigned long n, int fd);
void				ft_putstr_fd(char *s, int fd);
int					print_err(char *err_str);
int					print_err_code(char *err_str, int err_code);


/*
** Util functions
*/
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
void				*free_null(void *ptr);
int					ft_strlen(char *str);

#endif