/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_unfilter_algos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:40:50 by val               #+#    #+#             */
/*   Updated: 2025/06/23 00:21:30 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

void	png_filter_sub(t_png_unfilter_context *context, uint8_t *raw_line)
{
	size_t	i;
	uint8_t	left;

	i = 0;
	while (i < context->lines_bytes)
	{
		if (i < context->bpp)
			left = 0;
		else
			left = context->current_line[i - context->bpp];
		context->current_line[i] = raw_line[i] + left;
		i++;
	}
}

void	png_filter_up(t_png_unfilter_context *context,
	uint8_t *raw_line)
{
	size_t	i;

	i = 0;
	while (i < context->lines_bytes)
	{
		context->current_line[i] = raw_line[i] + context->prev_line[i];
		i++;
	}
}

void	png_filter_average(t_png_unfilter_context *context, uint8_t *raw_line)
{
	size_t	i;
	uint8_t	left;
	uint8_t	up;

	i = 0;
	while (i < context->lines_bytes)
	{
		if (i < context->bpp)
			left = 0;
		else
			left = context->current_line[i - context->bpp];
		up = context->prev_line[i];
		context->current_line[i] = raw_line[i] + ((left + up) >> 1);
		i++;
	}
}

static uint8_t	paeth_predictor(int a, int b, int c)
{
	int	p;
	int	pa;
	int	pb;
	int	pc;

	p = a + b - c;
	pa = p - a;
	if (pa < 0)
		pa = -pa;
	pb = p - b;
	if (pb < 0)
		pb = -pb;
	pc = p - c;
	if (pc < 0)
		pc = -pc;
	if (pa <= pb && pa <= pc)
		return ((uint8_t)a);
	if (pb <= pc)
		return ((uint8_t)b);
	return ((uint8_t)c);
}

void	png_filter_paeth(t_png_unfilter_context *context, uint8_t *raw_line)
{
	size_t	i;
	uint8_t	left;
	uint8_t	up_left;
	uint8_t	up;

	i = 0;
	while (i < context->lines_bytes)
	{
		if (i < context->bpp)
		{
			left = 0;
			up_left = 0;
		}
		else
		{
			left = context->current_line[i - context->bpp];
			up_left = context->prev_line[i - context->bpp];
		}
		up = context->prev_line[i];
		context->current_line[i] = raw_line[i]
			+ paeth_predictor(left, up, up_left);
		i++;
	}
}
