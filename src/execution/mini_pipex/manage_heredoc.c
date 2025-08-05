/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:06:46 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/05 17:59:31 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	megaloop(t_minishell *minishell, t_cmd *cmd, int heredoc_fd, int i)
{
	char	*final_line;
	char	*line;

	final_line = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (ft_strcmp(line, cmd->heredocs[i]) == 0)
			{
				free(line);
				close(heredoc_fd);
				heredoc_fd = -1;
				break ;
			}
			if (cmd->expand_heredoc_content)
				final_line = expand_heredoc_line(minishell, line);
			else
				final_line = ft_strdup(line);
			ft_putendl_fd(line, heredoc_fd);
			free(line);
			free(final_line);
		}
		else
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
				cmd->heredocs[i]);
			close(heredoc_fd);
			heredoc_fd = -1;
			break ;
		}
	}
}

char	*get_heredocs(t_minishell *minishell, t_cmd *cmd)
{
	int		i;
	int		n;
	char	*filepath;
	char	*last_filepath;
	int		heredoc_fd;

	i = 0;
	n = 0;
	heredoc_fd = -1;
	last_filepath = NULL;
	while (cmd->heredocs[i])
	{
		while (1)
		{
			n = 0;
			filepath = ft_strjoin("/tmp/.heredoc_minishell", ft_itoa(i + n));
			if (access(filepath, F_OK) == 0)
			{
				free(filepath);
				n += 1;
			}
			else
				break;
		}
		heredoc_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (heredoc_fd == -1)
			perror("");
		megaloop(minishell, cmd, heredoc_fd, i);
		if (last_filepath)
			free(last_filepath);
		last_filepath = filepath;
		i++;
	}
	return (last_filepath);
}

int manage_heredocs(t_cmd *cmd, t_fds *fd)
{
	int heredoc_fd;

	(void)fd;
	heredoc_fd = open(cmd->last_heredoc_filepath, O_RDONLY);
	if(heredoc_fd == -1)
		perror("minishell: heredoc");
	else
		return (heredoc_fd);
	return (-1);
}