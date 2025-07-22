/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:57:28 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/22 17:13:08 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Recreates array + 1 in size and inserts the given infile in the first pos,
 * copies the rest.
 */
char  **insert_into_array(char *infile, char **array, t_minishell *minishell)
{
	char **new_array;
	int new_array_size;
	int i;

	new_array_size = 0;
	while(array && array[new_array_size])
		new_array_size++;
	new_array = ft_calloc(new_array_size + 2, sizeof(char *));
	if (!new_array)
		malloc_error(minishell);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = infile;
	ft_free_array((void **)array);
	return(new_array);
}

/**
 * From the given segments it builds an array of all infiles
 */
char **get_infile_array(t_minishell *minishell, t_token *segment)
{
	t_token *current;
	char 	*infile;
	char	**array;

	array = ft_calloc(1, sizeof(char *));
	if(!array)
		malloc_error(minishell);
	current = segment;
	while(current && current->next)
	{
		if (current->token_type == TOKEN_REDIR_IN)
		{
			current = current->next;
			infile = ft_strdup(current->value);
			if (!infile)
			{
				free_tokens_list(&segment);
				malloc_error(minishell);
			}
			array = insert_into_array(infile, array, minishell);
		}
		current = current->next;
	}
	return (array);
}

/**
 * From the given segments it builds an array of all outfiles (append and redirections)
 */
char **get_outfile_array(t_minishell *minishell, t_token *segment)
{
	t_token *current;
	char 	*outfile;
	char	**array;

	array = ft_calloc(0, sizeof(char *));
	if(!array)
		malloc_error(minishell);
	current = segment;
	while(current && current->next)
	{
		if (current->token_type == TOKEN_REDIR_OUT 
			|| current->token_type == TOKEN_APPEND)
		{
			current = current->next;
			outfile = ft_strdup(current->value);
			if (!outfile)
			{
				free_tokens_list(&segment);
				malloc_error(minishell);
			}
			array = insert_into_array(outfile, array, minishell);
		}
		current = current->next;
	}
	return (array);
}

/**
 * From the given segments it builds an array of all heredoc delimiters
 */
char **get_heredoc_array(t_minishell *minishell, t_token *segment)
{
	t_token *current;
	char 	*delimiter;
	char	**array;

	array = ft_calloc(1, sizeof(char *));
	if(!array)
		malloc_error(minishell);
	current = segment;
	while(current && current->next)
	{
		if (current->token_type == TOKEN_HEREDOC)
		{
			current = current->next;
			delimiter = ft_strdup(current->value);
			if (!delimiter)
			{
				free_tokens_list(&segment);
				malloc_error(minishell);
			}
			array = insert_into_array(delimiter, array, minishell);
		}
		current = current->next;
	}
	return (array);
}

int	get_append_status(t_token *segment)
{
	t_token	*current;

	current = segment;
	while (current && current->next != NULL
		&& current->next->token_type != TOKEN_EOF)
	{
		current = current->next;
	}
	while (current && current->prev != NULL)
	{
		if(current->token_type == TOKEN_APPEND_FILE ||
			current->token_type == TOKEN_REDIR_OUT_FILE)
		{
			if (current->token_type == TOKEN_APPEND_FILE)
				return (1);
			else
				return (0);
		}
		current = current->prev;
	}
	return (0);
}

int get_last_in_type(t_token *segment)
{
	t_token* current;
	int i;

	i = 0;
	current = segment;
	while (current)
	{
		if (current->token_type == TOKEN_REDIR_IN)
			i = 1;
		else if (current->token_type == TOKEN_HEREDOC)
			i = 0;
		current = current->next;
	}
	return (i);	
}
