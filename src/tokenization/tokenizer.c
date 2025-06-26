/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 16:03:09 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *tokenizer(char *input)
{
	char 		*trimmed_input;
	t_token 	*token_head;
	int i;

	trimmed_input = ft_strtrim(input, "\n\t ");
	token_head = NULL;
	i = 0;
	while(input && input[i])
	{
		if(ft_isspace(input[i]))
			i++;
		else if(is_operator(trimmed_input, i))
			i += handle_operator(&token_head, trimmed_input, i);
		else if(is_quote(trimmed_input, i))
			i += handle_quoted_word(&token_head, trimmed_input, i);
		else
			i += handle_nonquoted_word(&token_head, trimmed_input, i);
	}
	add_eof_token(&token_head);
	free(trimmed_input);
	return (token_head);
}
