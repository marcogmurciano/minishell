/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:34:32 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/22 17:19:45 by dbarba-v         ###   ########.fr       */
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
		printf("\n--- COMMAND %d ---\n", cmd_num);
		
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("ARGV[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		
		i = 0;
		if (cmd->infiles)
		{
			while (cmd->infiles[i])
			{
				printf("INFILE[%d]: %s\n", i, cmd->infiles[i]);
				i++;
			}
		}
		
		i = 0;
		if (cmd->heredocs)
		{
			while (cmd->heredocs[i])
			{
				printf("HEREDOC[%d]: %s\n", i, cmd->heredocs[i]);
				i++;
			}
		}
		
		printf("EXPAND HEREDOC: %d\n", cmd->expand_heredoc_content);
		printf("LAST REDIR_IN TYPE: %d\n", cmd->last_in);
		
		i = 0;
		if (cmd->outfiles)
		{
			while (cmd->outfiles[i])
			{
				printf("OUTFILE[%d]: %s\n", i, cmd->outfiles[i]);
				i++;
			}
		}
		
		printf("APPEND STATUS: %d\n", cmd->append);
		printf("================\n");
		
		cmd = cmd->next;
		cmd_num++;
	}
}

void	print_envp(char **envp)
{
	int	i;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	print_environ(t_env *env)
{
	t_env *curr = env;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}
