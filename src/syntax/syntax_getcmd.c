/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_getcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:02:32 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:29:08 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * For the provided array, fill it with the command and arguments
 */
static int	fill_argv_from_tokens(char **argv, t_token *segment)
{
	t_token	*token;
	int		i;

	i = 0;
	token = segment;
	while (token && token->token_type != TOKEN_EOF)
	{
		if (token->token_type == TOKEN_CMD || token->token_type == TOKEN_ARG)
		{
			argv[i] = ft_strdup(token->value);
			if (!argv[i])
				return (1);
			i++;
		}
		token = token->next;
	}
	argv[i] = NULL;
	return (0);
}

/**
 * Count the total number of arguments plus the command
 */
static int	count_cmd_arg_tokens(t_token *segment)
{
	int		count;
	t_token	*token;

	count = 0;
	token = segment;
	while (token && token->token_type != TOKEN_EOF)
	{
		if (token->token_type == TOKEN_CMD || token->token_type == TOKEN_ARG)
			count++;
		token = token->next;
	}
	return (count);
}

/**
 * Build an array from command and arguments in the current segment/pipeline
 */
char	**get_cmd_argv(t_minishell *minishell, t_token *segment)
{
	int		argc;
	char	**argv;

	argc = count_cmd_arg_tokens(segment);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
	{
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	if (fill_argv_from_tokens(argv, segment) == 1)
	{
		free_array(argv, argc);
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	return (argv);
}
