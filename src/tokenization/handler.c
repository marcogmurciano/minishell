/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:08:49 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 16:08:57 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_operator(t_token **token_head, char *trimmed_input, int i)
{
	if (trimmed_input[i] == '|')
	{
		return (add_nonword_token(token_head, TOKEN_PIPE), 1);
	}
	if (trimmed_input[i] == '<' && trimmed_input[i + 1] == '<')
	{
		return (add_nonword_token(token_head, TOKEN_HEREDOC), 2);
	}
	if (trimmed_input[i] == '<')
	{
		return (add_nonword_token(token_head, TOKEN_REDIR_IN), 1);
	}
	if (trimmed_input[i] == '>' && trimmed_input[i + 1] == '>')
	{
		return (add_nonword_token(token_head, TOKEN_APPEND), 2);
	}
	if (trimmed_input[i] == '>')
	{
		return (add_nonword_token(token_head, TOKEN_REDIR_OUT), 1);
	}
	return (1);
}

int handle_quoted_word(t_token **token_head, char *trimmed_input, int i)
{
	char	quote;
    char	*word;
	int		len;
	
	quote = trimmed_input[i];
	word = get_quoted_word(&trimmed_input[i], quote);
    add_word_token(token_head, TOKEN_WORD, word, quote);
    len = ft_strlen(word);
    free(word);
    return (len + 2);
}

int handle_nonquoted_word(t_token **token_head, char *trimmed_input, int i)
{
    char	*word;
	int		len;
	
	word = get_unquoted_word(&trimmed_input[i]);
    add_word_token(token_head, TOKEN_WORD, word, '\0');
    len = ft_strlen(word);
    free(word);
    return (len);
}