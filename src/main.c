/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/18 18:36:33 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

static void	minishell_loop(t_minishell *minishell)
{
	while (1)
	{
		free_cmds(&(minishell->cmd_pipelines)); /// ONLY FOR DEBUGGING WITHOUT EXECUTION
		minishell->input = get_prompt_input();
		if (!minishell->input)
		{
			exit_minishell(minishell);
		}
		tokenization(minishell);
		if (syntax_analysis(minishell) == 1)
			continue ;
		// > EXECUTION < //
		// printf("entramos a execution");
		minishell->last_exit_status = execution(minishell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	initialize_minishell(&minishell, envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(&minishell);
	return (0);
}
