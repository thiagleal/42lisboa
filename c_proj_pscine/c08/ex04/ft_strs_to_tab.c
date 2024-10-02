/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:03:15 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/05 15:57:57 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

char *ft_strdup(char *src)
{
    char *dup;
    int i = 0;

    while (src[i])
        i++;
    dup = (char *)malloc((i + 1) * sizeof(char));
    if (!dup)
        return (NULL);
    i = 0;
    while (src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

struct s_stock_str *ft_strs_to_tab(int ac, char **av)
{
    t_stock_str *array;
    int i;

    array = (t_stock_str *)malloc((ac + 1) * sizeof(t_stock_str));
    if (!array)
        return (NULL);
    i = 0;
    while (i < ac)
    {
        array[i].size = 0;
        while (av[i][array[i].size])
            array[i].size++;
        array[i].str = av[i];
        array[i].copy = ft_strdup(av[i]);
        if (!array[i].copy)
        {
            while (i > 0)
                free(array[--i].copy);
            free(array);
            return (NULL);
        }
        i++;
    }
    array[i].str = 0;
    return (array);
}
