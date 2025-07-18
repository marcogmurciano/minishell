/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:34:32 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/18 12:08:53 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_token *token_head)
{
	t_token	*token;

	token = token_head;
	while (token)
	{
		printf("\n--- TOKEN ---\n");
		printf("Token type: %d\n", token->token_type);
		printf("Token quote: %d\n", token->quote_type);
		printf("Space before: %d\n", token->spaced);
		printf("Token value: %s\n", token->value);
		printf("==================\n");
		token = token->next;
	}
}

void	print_segment(t_token *token)
{
	printf("\n--- SEGMENT ---\n");
	while (token)
	{
		printf("Segment: %s\n", token->value);
		token = token->next;
	}
	printf("--- END SEGMENT ---\n\n");
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	cmd_num;

	cmd_num = 0;
	while (cmd)
	{
		i = 0;
		printf("\n--- COMMAND %d ---\n", cmd_num);
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("ARGV[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		printf("INFILE: %s\n", cmd->infile);
		printf("OUTFILE: %s\n", cmd->outfile);
		printf("APPEND STATUS: %d\n", cmd->append);
		printf("HEREDOC DELIMETERS: %s\n", cmd->heredoc);
		printf("================\n");
		cmd = cmd->next;
		cmd_num++;
	}
}
