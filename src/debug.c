/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:34:32 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/11 15:57:57 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_tokens(t_token *token_head)
{
    t_token *token;

    token = token_head;
    while (token)
    {
        printf("Token type: %d\n", token->token_type);
        printf("Token quote: %d\n", token->quote_type);
        printf("Token value: %s\n", token->value);
        printf("==================\n");
        token = token->next;
    }
}

void print_segment(t_token *token)
{
	while (token)
	{
		printf("DEBUG PRINT SEGMENT: %s\n", token->value);
		token = token->next;
	}
}

void print_cmd(t_cmd *cmd)
{
	int i;
	i = 0;

	printf("COMMAND\n");
	while (cmd->argv[i])
		printf("ARGV[%d]: %s\n", i, cmd->argv[i]);
	printf("INFILE: %s\n", cmd->infile);
	printf("OUTFILE: %s\n", cmd->outfile);
	printf("APPEND STATUS: %d\n", cmd->append);
	printf("HEREDOC DELIMETERS: %s\n", cmd->heredoc);
	printf("================\n");
}