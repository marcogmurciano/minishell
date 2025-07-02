/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/02 15:51:27 by dbarba-v         ###   ########.fr       */
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
			initialize_expanded_tokens_list(&minishell);
			refine_token_roles(minishell.tokens_list);
			check_syntax(&minishell);
			print_tokens(minishell.tokens_list); // DEBUG PRINTING FUNCTION //
			// > EXECUTION < //
		}
		else
			exit_minishell(&minishell);
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