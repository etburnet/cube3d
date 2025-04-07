/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samraoui <samraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:51:50 by samraoui          #+#    #+#             */
/*   Updated: 2025/04/07 14:57:10 by samraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*substr;
	char	*new_str;
	int		s_len;
	int		i;

	s_len = ft_strlen(s);
	if (s == NULL || s_len < start)
		return (ft_strdup(""));
	if (start + len < s_len)
		substr = (char *)malloc((len + 1) * sizeof(char));
	else
		substr = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = start;
	new_str = substr;
	while (i < (start + len) && *(s + i))
		*new_str++ = *(s + i++);
	*new_str = '\0';
	return (substr);
}

char	*ft_strrjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len;
	int		j;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}
