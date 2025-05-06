/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:17:30 by val               #+#    #+#             */
/*   Updated: 2025/05/06 17:56:03 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_utils.h"

/**
 * @brief Ouvre un fichier avec gestion de buffer pour lecture séquentielle
 * 
 * @param name Nom du fichier
 * @param flags Flags d'ouverture (voir open())
 * @return t_cp_file* Structure de fichier ou NULL
 * 
 * @note Utilise un buffer interne de CP_BUFFER_SIZE (4096 octets)
 */
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
