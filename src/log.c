/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:04:37 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 19:37:25 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "defs.h"

#define ARG_ERROR_MSG	"Argument error. Exiting.\n"
#define MEM_ERROR_MSG	"Memory error. Exiting.\n"
#define FORK_MSG		"has taken a fork\n"
#define EAT_MSG			"is eating\n"
#define THINK_MSG		"is thinking\n"
#define SLEEP_MSG		"is sleeping\n"
#define DIE_MSG			"died\n"

t_ret	print_error(t_err error)
{
	const char	*msg;

	if (error == ARG_ERROR)
		msg = ARG_ERROR_MSG;
	else if (error == MEM_ERROR)
		msg = MEM_ERROR_MSG;
	printf("%s", msg);
	return (FAILURE);
}

void	print_status(t_philo *philo, t_ph_status status, uint64_t rel_time)
{
	const char	*msg;
	uint64_t	_id;

	if (status == EATING)
		msg = EAT_MSG;
	else if (status == THINKING)
		msg = THINK_MSG;
	else if (status == SLEEPING)
		msg = SLEEP_MSG;
	else if (status == FORKING)
		msg = FORK_MSG;
	else if (status == DEAD)
		msg = DIE_MSG;
	_id = get(&philo->id);
	pthread_mutex_lock(philo->data->printer.mutx);
	if (get(&philo->data->sim_status) == ONGOING)
		printf("%010llu %llu %s", rel_time, _id, msg);
	pthread_mutex_unlock(philo->data->printer.mutx);
}
