/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:34:39 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/05 15:59:28 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

struct s_stock_str *ft_strs_to_tab(int ac, char **av);
void ft_show_tab(struct s_stock_str *par);

int main(void)
{
    char *strings[] = {"Hello", "World", "42", "Piscine"};
    int size = 4;
    t_stock_str *array;

    array = ft_strs_to_tab(size, strings);
    if (!array)
        return (1);
    ft_show_tab(array);

    // Free allocated memory
    for (int i = 0; i < size; i++)
    {
        free(array[i].copy);
    }
    free(array);

    return (0);
}
