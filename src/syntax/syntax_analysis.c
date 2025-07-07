/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:56:11 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/07 16:42:43 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token *get_next_segment(t_token **token)
{
	t_token	*segment_head;
	t_token	*segment_tail;
	t_token	*next;
	
	if(!token || !*token)
		return (NULL);
	segment_head = *token;
	segment_tail = segment_head;
	next = NULL;
	while (segment_tail && 
		segment_tail->token_type != TOKEN_EOF &&
		segment_tail->token_type != TOKEN_PIPE)
		segment_tail = segment_tail->next;
	if (segment_tail && 
		(segment_tail->token_type == TOKEN_EOF ||
		segment_tail->token_type == TOKEN_PIPE))
	{
		next = segment_tail->next;
		if (segment_tail->prev)
			segment_tail->prev->next = NULL;
		segment_tail->prev = NULL;
	}
	*token = next;
	return(segment_head);
}

static t_cmd *build_cmd_from_segment(t_minishell *minishell, t_token *segment)
{
	t_cmd *cmd;

	cmd = ft_calloc(1, sizeof(cmd));
	if (!cmd)
	{
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	cmd->argv = get_cmd_argv(minishell, segment);
	printf("%s\n", cmd->argv[0]);
	cmd->infile = get_infile(minishell, segment);
	printf("%s\n", cmd->infile);
	cmd->outfile = get_outfile(minishell, segment);
	printf("%s\n", cmd->outfile);
	*(cmd->append) = get_append_status(segment);
	printf("%d\n", *(cmd->append));
	cmd->heredoc = get_heredoc_delimiter(minishell, segment);
	free_tokens_list(&segment);
	return(cmd);
}

static void append_command(t_minishell *minishell, t_cmd *new_cmd)
{
	t_cmd *current;

	current = minishell->cmd_pipelines;
	if(current == NULL)
		current = new_cmd;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}

void syntax_analysis(t_minishell *minishell)
{
	t_cmd	*new_command;
	t_token *token;
	t_token *segment;

	token = minishell->tokens_list;
	// TODO: Check token list for correct syntax // Parse errors
	while (token && token->token_type != TOKEN_EOF)
	{
		segment = get_next_segment(&token);
		print_segment(segment);
		new_command = build_cmd_from_segment(minishell, segment); // FREE segment inside
		append_command(minishell, new_command);
	}
}

void print_segment(t_token *token)
{
	while (token)
	{
		printf("DEBUG(print_segment): %s\n", token->value);
		token = token->next;
	}
}