/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:56:11 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/08 15:28:39 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Extracts the next command segment from a token list.
 *
 * This function takes a pointer to the current token pointer, extracts the segment of tokens
 * up to (but not including) the next TOKEN_PIPE or TOKEN_EOF, and updates the input token pointer
 * to point to the next token after the segment. The extracted segment is disconnected from the rest
 * of the list, and can be processed independently.
 *
 * @param token Double pointer to the current position in the token list. Updated after extraction.
 * @return Pointer to the head of the extracted segment, or NULL if input is invalid.
 */
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
	// NEEDS TO SKIP CONSECUTIVE PIPES
	*token = next;
	return(segment_head);
}

/**
 * @brief Builds a command structure from a given segment of tokens.
 *
 * Allocates and initializes a t_cmd structure using the provided minishell context and
 * a segment of tokens. The function extracts command arguments, input/output files,
 * heredoc delimiters, and append status from the token segment and assigns them to the new command.
 * If memory allocation fails, frees the segment and handles the error via malloc_error().
 *
 * @param minishell Pointer to the minishell structure for context and error handling.
 * @param segment Pointer to the head of a token segment representing a command and its properties.
 * @return Pointer to the newly created t_cmd structure populated with data from the segment,
 *         or NULL if allocation fails.
 */
static t_cmd *build_cmd_from_segment(t_minishell *minishell, t_token *segment)
{
	t_cmd *cmd;
	int append_status;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	cmd->argv = get_cmd_argv(minishell, segment);
	printf("ARGV[0]: %s\n", cmd->argv[0]);
	cmd->infile = get_infile(minishell, segment);
	printf("INFILE: %s\n", cmd->infile);
	cmd->outfile = get_outfile(minishell, segment);
	printf("OUTFILE: %s\n", cmd->outfile);
	append_status = get_append_status(segment);
	cmd->append = &append_status;
	printf("APPEND STATUS: %d\n", *(cmd->append));
	cmd->heredoc = get_heredoc_delimiter(minishell, segment);
	printf("================\n");
	free_tokens_list(&segment);
	return(cmd);
}

/**
 * @brief Appends a new command to the minishell's command pipeline list.
 *
 * This function adds the given command (new_cmd) to the end of the minishell's
 * command pipeline list. If the list is empty, new_cmd becomes the first element.
 * If new_cmd or minishell is NULL, the function returns immediately.
 *
 * @param minishell Pointer to the minishell structure containing the command pipeline list.
 * @param new_cmd Pointer to the command to be appended.
 */
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

/**
 * @brief Performs syntax analysis on the tokens list of the given minishell instance.
 *
 * This function iterates through the token list in the provided minishell structure,
 * processes each command segment, prints the segment, builds a command structure from it,
 * and appends it to the minishell's command list. It is responsible for parsing the input
 * tokens into executable command structures.
 *
 * @param minishell Pointer to the minishell structure containing the tokens list and command list.
 */
void syntax_analysis(t_minishell *minishell)
{
	t_cmd	*new_command;
	t_token *token;
	t_token *segment;

	token = minishell->tokens_list;
	syntax_check(minishell);
	while (token && token->token_type != TOKEN_EOF)
	{
		segment = get_next_segment(&token);
		print_segment(segment); // DEBUG PRINTING
		new_command = build_cmd_from_segment(minishell, segment); // FREE segment inside
		append_command(minishell, new_command);
	}
}


/**
 * Debug function to print segments
 */
void print_segment(t_token *token)
{
	while (token)
	{
		printf("DEBUG(print_segment): %s\n", token->value);
		token = token->next;
	}
}