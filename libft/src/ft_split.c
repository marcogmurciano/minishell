/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:20:07 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:02:18 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Completely free array.
 * @param array The array to be freed.
 * @param j Last valid index to free.
 * @return NULL pointer.
 */
static char	**free_array(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	array = NULL;
	return (array);
}

/**
 * @brief Calculate length of the word.
 * @param s Pointer to character in a string.
 * @param c Character that marks word end.
 * @return Number of characters in the word.
 */ 
static size_t	word_len(char *s, char c)
{
	size_t	i;
	
	i = 0;
	while (s[i] && s[i] != c)
	i++;
	return (i);	
}	

/**
 * @brief Function that fills the array with split words.
 * @param o_array The already allocated array of specified size.
 * @param s String to split and write into the array.
 * @param c Delimiter character that separates words.
 * @return On success: Array filled with words; On failure: NULL.
 */
static char	**fill_array(char **o_array, char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		len = word_len(s + i, c);
		o_array[j] = malloc(sizeof(char) * (len + 1));
		if (!o_array[j])
		{
			free_array(o_array, j - 1);
			return NULL;
		}
		ft_strlcpy(o_array[j], s + i, len + 1);
		j++;
		i += len;
	}
	o_array[j] = NULL;
	return (o_array);
}

/**
 * @brief Count the number of words separated by the given delimiter.
 * @param s String to be parsed.
 * @param c Character used as delimiter.
 * @return Number of words.
 */ 
static size_t	word_count(char *s, char c)
{
	size_t	i;
	size_t	count;
	bool	in_word;

	i = 0;
	count = 0;
	in_word = false;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = true;
			count++;
		}	
		else if (s[i] == c)
		{
			in_word = false;
		}	
		i++;
	}	
	return (count);
}	

char	**ft_split(char *s, char c)
/**
 * @brief Creates an array of strings from a given string.
 * @param s String to be split.
 * @param c Delimiter character.
 * @return If successful: Array of new strings; If unsuccessful: NULL.
 */ 
{
	size_t	words;
	char	**array;
	
	if (s == NULL)
	return (NULL);
	words = word_count(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = fill_array(array, s, c);	
	if (array == NULL || array[0] == NULL)
	{
		free_array(array, words - 1);
		return (NULL);
	}	
	return (array);
}	
