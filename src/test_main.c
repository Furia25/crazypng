/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/01 02:28:58 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

int	main(void)
{
	t_png	*png;

	png = png_open("test_files/bad_chunk_length_truncated.png");
	png_close(png);
}
