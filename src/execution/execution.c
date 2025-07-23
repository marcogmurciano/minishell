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

// static void process_cmd_node(t_cmd *node, char **array, int *count, int *flag)
// {
//     int     i;
//     char    *temp;

//     i = 0;
//     if (node->infile)
//     {
//         array[*count] = ft_strdup(node->infile);
//         *flag += 10;
//         (*count)++;
//     }
//     while (node->argv[i])
//     {
//         if (i == 0)
//             array[*count] = ft_strdup(node->argv[i]);
//         else
//         {
//             temp = array[*count]; 
//             array[*count] = ft_strjoin(temp, " ");
//             temp = array[*count]; 
//             array[*count] = ft_strjoin(temp, node->argv[i]);
//             free(temp);
//         }
//         i++;
//     }
//     (*count)++;
// }

// static void process_final_node(t_cmd *node, char **array, int *count, int *flag)
// {
//     process_cmd_node(node, array, count, flag);
//     if (node->outfile)
//     {
//         array[*count] = ft_strdup(node->outfile);
//         *flag += 1;
//         (*count)++;
//     }
// }

// static char **create_cmd_array(t_cmd *head, int *cmd_count, int *files_flag)
// {
//     char **full_pipe_line;
//     int count;
//     t_cmd *current;

//     *cmd_count = ft_cmdsize(head);
//     full_pipe_line = (char **)malloc(sizeof(char *) * (*cmd_count + 3));
//     if (!full_pipe_line)
//         return (NULL);
//     current = head;
//     count = 0;
//     while (current && current->next)
//     {
//         process_cmd_node(current, full_pipe_line, &count, files_flag);
//         current = current->next;
//     }
//     if (current)
//         process_final_node(current, full_pipe_line, &count, files_flag);
//     full_pipe_line[count] = NULL;
//     return (full_pipe_line);
// }


// static void print_ft_pipex_arguments(int cmd_count, char **full_pipe_line, int files_flag)
// {
//     int i = 0;
//     printf("le estamos pasando a pipex:\n  cdm_count: %d\n", cmd_count);
//     while (full_pipe_line[i])
//     {
//         printf("      elemento %d de full pipeline: %s\n", i, full_pipe_line[i]);
//         i++;
//     }
//     printf("  files_flag: %d\n", files_flag);
//     // i = 0;
//     // while (minishell->envp[i])
//     // {
//     //     printf("      elemento %d de minishell->envp: %s\n", i, minishell->envp[i]);
//     //     i++;
//     // }
// }

int execution(t_minishell *minishell)
{
    t_cmd *head = minishell->cmd_pipelines;
    int cmd_count;
    int result;

    //debug
    print_cmd(head);
    cmd_count = ft_cmdsize(head);
    if (!head)
        return (1);
    result = ft_pipex(cmd_count, head, minishell);
    return (result);
}
