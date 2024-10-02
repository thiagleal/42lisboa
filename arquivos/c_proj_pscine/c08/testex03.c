/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testex03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:56:00 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/05 13:01:21 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_point.h"
#include <stdio.h>

void set_point(t_point *point)
{
point->x = 42;
point->y = 21;
}

int main(void)
{
t_point point;
set_point(&point);
printf("x: %d, y: %d\n", point.x, point.y);
return (0);
}