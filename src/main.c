/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/30 16:00:05 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int g_signal_status = 0;

int main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	
	(void)argc;
    (void)argv;
	
	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.environment = regenerate_environment(envp);
	// minishell.envp = get_environment_array(minishell);

	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigint_handler);
	while (1)
	{
		minishell.input = get_prompt_input(); // Allocates memory, needs free
		if(minishell.input)
		{
			minishell.tokens_list = tokenizer(minishell.input);
			if(needs_expansion(minishell.tokens_list))
			{
				free(minishell.input);
				minishell.input = NULL;
				minishell.input = expand_tokens_list(&minishell);
				free_tokens_list(&(minishell.tokens_list));
				minishell.tokens_list = NULL;
				minishell.tokens_list = tokenizer(minishell.input);
			}
			print_tokens(minishell.tokens_list);
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