/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbigendian.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:32:53 by val               #+#    #+#             */
/*   Updated: 2025/04/30 15:33:43 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int	ft_isbigendian(void)
{
	const uint32_t		x = 1;
	const unsigned char	*c = (const unsigned char*) &x;

	return (!((int)(*c)));
}
