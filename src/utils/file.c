/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:17:30 by val               #+#    #+#             */
/*   Updated: 2025/05/06 00:44:00 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_utils.h"

t_cp_file	*cp_open(char *name, int flags)
{
	t_cp_file	*file;

	file = malloc(sizeof(t_cp_file));
	if (!file)
		return (NULL);
	file->fd = open(name, flags);
	if (file->fd == -1)
	{
		free(file);
		return (NULL);
	}
	file->valid_bytes = 0;
	file->pos = 0;
	return (file);
}

void	cp_close(t_cp_file *file)
{
	if (!file)
		return ;
	if (file->fd != -1)
		close(file->fd);
	free(file);
}
