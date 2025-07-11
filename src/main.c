/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/11 10:36:50 by dbarba-v         ###   ########.fr       */
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
		minishell.input = get_prompt_input();
		if(minishell.input)
		{
			tokenization(&minishell);
			//print_tokens(minishell.tokens_list); // DEBUG PRINTING FUNCTION //
			if(syntax_analysis(&minishell) == -1)
				continue;

			// > EXECUTION < //
		}
		else
			exit_minishell(&minishell);
	}
}
