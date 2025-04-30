/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_managing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:48:38 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 15:33:52 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"
#include <errno.h>

static int	verify_png_signature(t_cp_file *file);

t_png	*png_open(char *file_name)
{
	t_png		*png;
	t_cp_file	*file;

	png = ft_calloc(1, sizeof(t_png));
	if (!png)
		return (NULL);
	file = cp_open(file_name, O_RDONLY);
	if (!file || !verify_png_signature(file))
	{
		png_close(png);
		return (NULL);
	}
	png->file = file;
	png->convert_endian = !ft_isbigendian();
	if (!png_parse(png))
	{
		png_close(png);
		return (NULL);
	}
	return (png);
}

void	png_close(t_png *png)
{
	if (!png)
		return ;
	if (png->file)
		cp_close(png->file);
	free(png);
}

static int	verify_png_signature(t_cp_file *file)
{
	uint64_t	signature;

	if (cp_fread(&signature, sizeof(uint64_t), 1, file) != 1)
		return (0);
	if (ft_memcmp(&signature, PNG_SIGNATURE, sizeof(uint64_t)) == 0)
	{
		return (1);
	}
	else
	{
		errno = EMEDIUMTYPE;
		return (0);
	}
}
