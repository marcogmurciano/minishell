/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:56:11 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:30:57 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Sets start of next segment, if current is a pipe, it lso frees it
 */
static void	set_next_segment_start(t_token *current, t_token **next_segment_start)
{
	t_token	*pipe_token;

	if (current->token_type == TOKEN_EOF)
	{
		*next_segment_start = current;
		unlink_token(current);
	}
	else if (current->token_type == TOKEN_PIPE)
	{
		pipe_token = current;
		*next_segment_start = pipe_token->next;
		unlink_token(pipe_token);
		if (*next_segment_start)
			(*next_segment_start)->prev = NULL;
		if (pipe_token->value)
			free(pipe_token->value);
		free(pipe_token);
	}
}

/**
 * Forms a detached list from the tokens that are part of the current segment
 */
static t_token	*get_next_segment(t_token **token)
{
	t_token	*segment_ends[2];
	t_token	*next_segment_start;

	if (!token || !*token)
		return (NULL);
	segment_ends[0] = *token;
	segment_ends[1] = segment_ends[0];
	next_segment_start = NULL;

	while (segment_ends[1] && segment_ends[1]->token_type != TOKEN_EOF
		&& segment_ends[1]->token_type != TOKEN_PIPE)
		segment_ends[1] = segment_ends[1]->next;

	if (segment_ends[1])
		set_next_segment_start(segment_ends[1], &next_segment_start);
	*token = next_segment_start;
	return (segment_ends[0]);
}

/**
 * From the provided segment builds a cmd
 */
static t_cmd	*build_cmd_from_segment(t_minishell *minishell,
		t_token *segment)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	cmd->argv = get_cmd_argv(minishell, segment);
	cmd->infiles = get_infile_array(minishell, segment);
	cmd->heredocs = get_heredoc_array(minishell, segment);
	cmd->expand_heredoc_content = get_heredoc_expansion_status(segment);
	cmd->last_heredoc_filepath = get_heredocs(minishell, cmd);
	cmd->last_in = get_last_in_type(segment);
	cmd->outfiles = get_outfile_array(minishell, segment);
	cmd->append = get_append_status(segment);
	free_tokens_list(&segment);
	return (cmd);
}

/**
 * Append providedd command to the end of the commands list
 */
static void	append_command(t_minishell *minishell, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!minishell || !new_cmd)
		return ;
	if (minishell->cmd_pipelines == NULL)
		minishell->cmd_pipelines = new_cmd;
	else
	{
		current = minishell->cmd_pipelines;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}

/**
 * Checks for correct syntax and builds the list of command pipelines
 */
int	syntax_analysis(t_minishell *minishell)
{
	t_cmd	*new_command;
	t_token	*token;
	t_token	*segment;

	if (syntax_check(minishell))
		return (1);
	token = minishell->tokens_list;
	while (token && token->token_type != TOKEN_EOF)
	{
		segment = get_next_segment(&token);
		new_command = build_cmd_from_segment(minishell, segment);
		append_command(minishell, new_command);
	}
	if (token)
		free_tokens_list(&token);
	minishell->tokens_list = NULL;
	return (0);
}
