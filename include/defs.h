/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:00 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 18:33:07 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <pthread.h>
# include <inttypes.h>
# include <stdbool.h>

typedef enum e_gen
{
	NONE = 0,
	NO = 0,
	YES = 1
}	t_gen;

typedef enum e_ret
{
	SUCCESS,
	FAILURE
}	t_ret;

typedef enum e_err
{
	ARG_ERROR,
	MEM_ERROR
}	t_err;

typedef enum e_ph_status
{
	EATING,
	THINKING,
	SLEEPING,
	FORKING,
	DEAD,
}	t_ph_status;

typedef enum e_sim
{
	STOPPED,
	ONGOING
}	t_sim;

typedef enum e_sim_mode
{
	UNLIMITED,
	LIMITED
}	t_sim_mode;

typedef struct s_philo	t_philo;

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

typedef struct s_mv
{
	uint64_t		value;
	pthread_mutex_t	*mutx;
}	t_mv;

typedef struct s_data
{
	t_mv	max_meals;
	t_mv	n_philo;
	t_mv	ttd;
	t_mv	tte;
	t_mv	tts;
	t_mv	stuffed_left;
	t_mv	sim_status;
	t_mv	sim_mode;
	t_mv	start_time;
	t_mv	ph_th_left;
	t_mv	printer;
	t_philo	*ph_lst;
	t_free	*free_lst;
	t_free	*free_head;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	pthread_t	monitor_thread;
	t_mv		id;
	t_mv		meals_left;
	t_mv		die_time;
	t_mv		r_fork;
	t_mv		l_fork;
	t_philo		*next;
	t_data		*data;
}	t_philo;

t_ret		init_data(t_data *data, int argc, char *argv[]);
void		start_threads(t_data *data);
t_ret		print_error(t_err error);
void		print_status(t_philo *philo, t_ph_status status, uint64_t rel_time);
void		act_eat(t_philo *philo);
void		act_sleep(t_philo *philo);
void		act_think(t_philo *philo);
void		*ft_smalloc(t_data *data, uint64_t size);
void		ft_free(t_free *list_head);
uint64_t	get(t_mv *mv);
void		set(t_mv *mv, uint64_t value);
void		set_add(t_mv *mv, int add_value);
t_ret		cleanxit(t_data *data, t_err error);
t_ret		setmutex(t_data *data, t_mv *mv, uint64_t value);
void		demutex(t_data *data);
uint64_t	get_sys_time_ms(void);
uint64_t	get_rel_time_ms(t_philo *philo);
void		reset_die_time(t_data *data, t_philo *philo);
void		sleep_ms(uint64_t ms);
int			ft_atoi(char *str);
bool		ft_is_even(uint64_t philo_id);

#endif
