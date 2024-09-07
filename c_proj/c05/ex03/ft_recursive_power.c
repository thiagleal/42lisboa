/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:08:10 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/03 16:28:36 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

int	main()
{
	int	valor;
	int	power;
	int	nb;

	nb = -2;
	power = 4;
	valor = ft_recursive_power(nb, power);
	printf("Resultado de %d elevado a %d sera: %d\n", nb, power, valor);
	return (0);	
}
