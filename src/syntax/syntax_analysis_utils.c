/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:57:28 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/07 17:10:42 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **get_cmd_argv(t_minishell *minishell, t_token *segment)
{
	char **new_strings_array;
	t_token *token;
	int i;
	
	i = 0;
	token = segment;
	while(token && token->token_type != TOKEN_EOF)
	{
		if (token->token_type == TOKEN_CMD || token->token_type == TOKEN_ARG)
			i++;
		token = token->next;
	}
	new_strings_array = ft_calloc(i, sizeof(char *) + 1);
	if(!new_strings_array)
	{
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	i = 0;
	token = segment;
	while(token && token->token_type != TOKEN_EOF)
	{
		if (token->token_type == TOKEN_CMD || token->token_type == TOKEN_ARG)
		{
			new_strings_array[i] = ft_strdup(token->value);
			if(!new_strings_array[i])
			{
				free_array(new_strings_array, i);
				free_tokens_list(&segment);	
				malloc_error(minishell);
			}
			i++;
		}
		token = token->next;
	}
	return (new_strings_array);
}

char *get_infile(t_minishell *minishell, t_token *segment)
{
	t_token *current;
	char	*infile;

	current = segment;
	if (current && current->token_type == TOKEN_REDIR_IN)
	{
		current = current->next;
		infile = ft_strdup(current->value);
		if(!infile)
		{
			free_tokens_list(&segment);
			malloc_error(minishell);
		}
		return(infile);
	}
	return (NULL);
}

char *get_outfile(t_minishell *minishell, t_token *segment)
{
	t_token *current;
	char	*outfile;

	current = segment;
	while (current->next && current->next->token_type != TOKEN_EOF)
	{
		current = current->next;
	}
	if (current && (current->next == NULL || 
		current->next->token_type == TOKEN_EOF) &&
		(current->token_type == TOKEN_REDIR_OUT_FILE ||
		current->token_type == TOKEN_APPEND_FILE))
	{
		outfile = ft_strdup(current->value);
		if(!outfile)
		{
			free_tokens_list(&segment);
			malloc_error(minishell);
		}
		return(outfile);
	}
	return (NULL);
}

int get_append_status(t_token *segment)
{
	t_token *current;

	current = segment;
	while (current->next != NULL || current->next->token_type != TOKEN_EOF)
		current = current->next;
	if (current->prev->prev->token_type == TOKEN_APPEND)
	{
		return(1);
	}
	return (0);
}

char *get_heredoc_delimiter(t_minishell *minishell, t_token *segment)
{
	t_token *current;
	char	*delimeter;

	current = segment;
	if(current && current->token_type == TOKEN_HEREDOC)
	{
		current = current->next;
		delimeter = ft_strdup(current->value);
		if(!delimeter)
		{
			free_tokens_list(&segment);
			malloc_error(minishell);
		}
		return(delimeter);
	}
	return(NULL);
}
