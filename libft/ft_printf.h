/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:42:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/03/12 17:33:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>

# define BASE_SMALL_HEX "0123456789abcdef"
# define BASE_BIG_HEX "0123456789ABCDEF"
# define BASE_DECIMAL "0123456789"

int		ft_isspace(char str);
int		ft_printf(const char *format, ...);
int		ft_atoi_base(char *str, char *base);
//
int		ft_putptr_fd(size_t ptr, int fd);
int		ft_putnbr_base_fd(long nb, char *base, int fd);

#endif
