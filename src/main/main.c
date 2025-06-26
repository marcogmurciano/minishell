/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 13:02:44 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// volatile sig_atomic_t	g_signal_received = 0; // Global variable for signals

int main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	
	(void)argc;
    (void)argv;
	
	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.environment = regenerate_environment(envp);

	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		minishell.input = get_prompt_input(); // Allocates memory, needs free
		if(minishell.input)
		{
			minishell.tokens_list = tokenizer(minishell.input);
			while(needs_expansion(minishell.tokens_list))
			{
				free(minishell.input);
				minishell.input = expand_tokens_list(minishell.tokens_list);
				free_tokens_list(minishell.tokens_list);
				minishell.tokens_list = tokenizer(minishell.input);
			}
		}
		else
			exit_minishell(&minishell);
	}
}
