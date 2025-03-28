/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:28:35 by doom              #+#    #+#             */
/*   Updated: 2025/03/28 14:40:13 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1;

    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;

    if (*str == '-' || *str == '+')
	{
        if (*str == '-')
            sign = -1;
        str++;
    }

    while (ft_isdigit(*str))
	{
        result = result * 10 + (*str - '0');
        str++;
    }

    return (result * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i < n)
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		(void)!write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

