/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 15:28:32 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

int	main(void)
{
	t_png	*png;

	png = png_open("test.png");
	if (!png)
		perror(PNG_ERROR);
	png_close(png);
}
