/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:34:19 by jolim             #+#    #+#             */
/*   Updated: 2021/04/16 14:12:25 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# include <stdbool.h>
# define ERROR -1
# define FAIL -27
# define SUCCESS 0

# define WAIT 0
# define DINE -98
# define DEAD -99
# define ALL_ATE -100

# define SEM_OPEN_FAIL "Failed to open semaphore"
# define SEM_CLOSE_FAIL "Failed to close semaphore"
# define SEM_UNLINK_FAIL "Failed to unlink semaphore"
# define TIME_GET_FAIL "Failed to get current time"
# define P_FORK_FAIL "Failed to fork a process"
# define P_KILL_FAIL "Failed to kill a process"
# define MALLOC_FAIL "Malloc failed"
# define THR_CREAT_FAIL "Failed to create a thread"
# define THR_JOIN_FAIL "Failed to join to a thread"

# define PRT_NAME "/print_sem"
# define FORK_NAME "/fork_sem"
# define START_NAME "/start_sem"
# define KILLER_NAME "/killer_sem"
# define DONE_NAME "/done_sem"

/*
** t_setting represents setting of the simulation.
**
** t_philo and t_fork represents state of each philosopher and fork.
*/
typedef struct		s_setting
{
	int				num_philo;
	long			time_die;
	long			time_eat;
	long			time_slp;
	int				num_must_eat;
	struct timeval	start_time;
	sem_t			*print_sem;
	sem_t			*done_sem;
}					t_setting;

typedef enum		e_philo_st
{
	think,
	eat,
	slp,
	die
}					t_philo_st;

typedef struct		s_philo
{
	int				index;
	enum e_philo_st	state;
	struct timeval	last_meal;
	sem_t			*forks;
	sem_t			*killer;
	t_setting		*setting;
}					t_philo;

enum				e_action
{
	lay = die + 1,
	take
};

typedef struct		s_table
{
	t_philo			*phs;
	t_setting		*setting;
	pid_t			*pids;
	pid_t			done_monitor;
}					t_table;

/*
** ph_kill_process kills first n processes of pids.
*/
int					ph_kill_process(pid_t *pids, int n);

/*
** ph_run_process forks philosopher processes.
*/
int					ph_run_process(t_table *table, sem_t *start);

/*
** ph_monitor, if it needs, makes a child process to check wheter philosophers
** ate enough, and makes a thread for checking if any of philosophers died.
*/
int					ph_monitor(t_table *table);

int					ph_over(t_table *table);
int					free_setting(t_setting *setting);

/*
** print_sem is a printer. The counter of this function is one.
*/
int					sem_print(unsigned long ms, int action, t_philo *philo);

/*
** philo_process is the function first run after philosopher forked. it starts
** ph_killer and philosopher lifecycle.
*/
int					philo_process(t_philo *philo, sem_t *start);

/*
** act_on_fork can changes a state of fork. when action is lay and fork is
** taken, fork can be changed into state laid. when action is take and fork is
** laid, for can be change into state taken.
*/
int					act_on_fork(enum e_action action, t_philo *philo);

/*
** ph_set_table initializes philosophers and forks.
*/
int					ph_set_table(t_table *table, t_setting *setting);
void				free_table(t_table *table, int err_code);

/*
** ph_get_duration returns how many ms elapsed after 'start'.
*/
long				ph_get_duration(struct timeval last, struct timeval now);
void				ph_sleep_precise(int ms);

/*
** Print functions.
*/

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putlu_fd(unsigned long n, int fd);
void				ft_putstr_fd(char *s, int fd);
int					print_err(char *err_str);
int					print_err_code(char *err_str, int err_code);

/*
** Util functions.
*/

int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
void				*free_null(void *ptr);
int					ft_strlen(char *str);
char				*ft_itoa(long long n);

#endif
