/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsetters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:00:23 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 19:18:22 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

uint64_t	get(t_mv *mv)
{
	uint64_t	ret;

	pthread_mutex_lock(mv->mutx);
	ret = mv->value;
	pthread_mutex_unlock(mv->mutx);
	return (ret);
}

void	set(t_mv *mv, uint64_t value)
{
	pthread_mutex_lock(mv->mutx);
	mv->value = value;
	pthread_mutex_unlock(mv->mutx);
}

void	set_add(t_mv *mv, int add_value)
{
	uint64_t	_get_value;

	pthread_mutex_lock(mv->mutx);
	_get_value = mv->value;
	mv->value = _get_value + add_value;
	pthread_mutex_unlock(mv->mutx);
}
