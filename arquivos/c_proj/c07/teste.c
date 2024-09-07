/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:13:17 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/05 16:38:59 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	**ft_split(char *str, char *charset);

int is_separator(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
		{
			return 1;
		}
		i++;
	}
	return (0);
}

int count_substrings(char *str, char *charset)
{
	int	count;
	int	in_substring;
	int	i;


	count = 0;
	in_substring = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!is_separator(str[i], charset))
		{
			if (!in_substring)
			{
				count++;
				in_substring = 1;
			}
		}
		else
		{
			in_substring = 0;
		}
		i++;
	}
	return count;
}

char *copy_substring(char *start, char *end)
{
	int length;
	char *substring;
	int i;

	length = end - start;
	substring = (char *)malloc((length + 1) * sizeof(char));
	i = 0;
	while (i < length)
	{
		substring[i] = start[i];
		i++;
	}
	substring[length] = '\0';
	return (substring);
}

char **ft_split(char *str, char *charset)
{
	int substr_count;
	char **result;
	int index;
	char *start;

	substr_count = count_substrings(str, charset);
	result = (char **)malloc((substr_count + 1) * sizeof(char *));
	index = 0;
	start = NULL;

	while (*str)
	{
		if (!is_separator(*str, charset))
		{
			if (!start)
			{
				start = str;
			}
		}
		else
		{
			if (start)
			{
				result[index++] = copy_substring(start, str);
				start = NULL;
			}
		}
		str++;
	}
	if (start)
    {
		result[index++] = copy_substring(start, str);
	}
	result[index] = NULL;
	return (result);
}

int main()
{
	char str[] = "Hello, world! This is a test.";
	char charset[] = " ,!";
	char **result;
	int i;

	result = ft_split(str, charset);

	i = 0;
	while (result[i] != NULL)
	{
		printf("Substring %d: %s\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	return (0);
}