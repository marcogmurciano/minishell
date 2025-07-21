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
 * @brief Extracts the next segment of tokens up to TOKEN_PIPE or TOKEN_EOF.
 *
 * @param token Double pointer to the current token; updated to the next segm.
 * @return Pointer to the head of the new segment, or NULL if input is invalid.
 */
static t_token	*get_next_segment(t_token **token)
{
	t_token	*segment_ends[2];
	t_token	*next;

	if (!token || !*token)
		return (NULL);
	segment_ends[0] = *token;
	segment_ends[1] = segment_ends[0];
	next = NULL;
	while (segment_ends[1] && segment_ends[1]->token_type != TOKEN_EOF
		&& segment_ends[1]->token_type != TOKEN_PIPE)
		segment_ends[1] = segment_ends[1]->next;
	if (segment_ends[1] && (segment_ends[1]->token_type == TOKEN_EOF
			|| segment_ends[1]->token_type == TOKEN_PIPE))
	{
		if (segment_ends[1]->token_type == TOKEN_EOF)
			next = segment_ends[1];
		else
			next = segment_ends[1]->next;
		if (segment_ends[1]->prev)
			segment_ends[1]->prev->next = NULL;
		segment_ends[1]->prev = NULL;
	}
	*token = next;
	return (segment_ends[0]);
}

/**
 * @brief Builds a t_cmd structure from a segment of tokens.
 *
 * @param minishell Pointer to the minishell context.
 * @param segment Head of the token segment for the command.
 * @return Pointer to the new t_cmd, or NULL on allocation failure.
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
	cmd->last_in = get_last_in_type(segment);
	cmd->outfiles = get_outfile_array(minishell, segment);
	cmd->append = get_append_status(segment);
	free_tokens_list(&segment);
	return (cmd);
}

/**
 * @brief Appends a command to the end of the minishell's pipeline list.
 *
 * @param minishell Pointer to the minishell structure.
 * @param new_cmd Pointer to the command to append.
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
 * @brief Parses the token list and builds the command pipeline.
 *
 * @param minishell Pointer to the minishell structure.
 * @return 0 on success, 1 on syntax error.
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
	free_tokens_list(&token);
	minishell->tokens_list = NULL;
	return (0);
}
