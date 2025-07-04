/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/04 13:05:55 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t g_signal_status = 0;

int main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	
	(void)argc;
    (void)argv;
	
	initialize_minishell(&minishell, envp);

	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigint_handler);
	while (1)
	{
		minishell.input = get_prompt_input(); // Allocates memory, needs free
		if(minishell.input)
		{
			tokenization(&minishell);
			syntax_analysis(&minishell);
			//
			print_tokens(minishell.tokens_list); // DEBUG PRINTING FUNCTION //
			// > EXECUTION < //
		}
		else
			exit_minishell(&minishell);
	}
}

void syntax_analysis(t_minishell *minishell)
{
	t_cmd	*new_cmd;
	t_token	*current;
	char	*infile;
	char	*outfile;

	current = minishell->tokens_list;
	if (current->token_type == TOKEN_REDIR_IN)
	{
		infile = current->next->value;
		current = current->next->next;
	}
	while(current)
	{
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		new_cmd->argv = get_arguments_array();
		//	If first segment and infile found
		//	if (first segment && infile)
		//		cmd->infile = strdup(infile);
		// 	If last segment and '>' found at end
		//	if (last segment and '>' in tokens)
		//		cmd->outfile = strdup(outfile);
		// 	Add to linked list
	}

}

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