/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-14 12:52:31 by user              #+#    #+#             */
/*   Updated: 2025-07-14 12:52:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cmdsize(t_cmd *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

// void    print_cmd_list(t_cmd *cmd)
// {
//     int cmd_count;
    
//     if (!cmd)
//     {
//         printf("Lista de comandos vacía\n");
//         return;
//     }
//     cmd_count = 1;
//     while (cmd)
//     {
//         printf("\n========== COMANDO %d ==========\n", cmd_count);
//         print_cmd(cmd);
//         cmd = cmd->next;
//         cmd_count++;
//     }
//     printf("Total de comandos: %d\n", cmd_count - 1);
// }

int execution(t_minishell *minishell)
{
    t_cmd *head;
    int cmd_count;
    int result;

    head = minishell->cmd_pipelines;
    if (!head)
        return (1);
    //debug
    // print_cmd(head);
    cmd_count = ft_cmdsize(head);
	ignore_signals();
    result = ft_pipex(cmd_count, head, minishell);
	setup_signal_handlers();
    return (result);
}
