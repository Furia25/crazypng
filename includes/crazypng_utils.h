/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:22:01 by val               #+#    #+#             */
/*   Updated: 2025/05/02 16:29:34 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_UTILS_H
# define CRAZYPNG_UTILS_H
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define CP_BUFFER_SIZE	4096

typedef struct s_cp_file
{
	int		fd;
	char	buffer[4096];
	ssize_t	valid_bytes;
	size_t	pos;
}	t_cp_file;

typedef struct s_cp_buffer
{
	uint8_t	*data;
	size_t	size;
	size_t	capacity;
}	t_cp_buffer;

bool		cp_buffer_add(t_cp_buffer *buf, void *to_add, size_t len);
void		cp_buffer_free(t_cp_buffer *buffer);
void		cp_buffer_reset(t_cp_buffer *buffer);

t_cp_file	*cp_open(char *name, int flags);
void		cp_close(t_cp_file *file);
size_t		cp_fread(void *ptr, size_t size, size_t nmemb, t_cp_file *file);
uint32_t	swap_endian32(uint32_t value);
#endif
