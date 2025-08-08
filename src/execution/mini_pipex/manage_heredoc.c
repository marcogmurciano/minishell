/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:06:46 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/08 11:17:43 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Loops that retrieves input and writes to the heredoc temp file
 */
static void	megaloop(t_minishell *minishell, t_cmd *cmd, int heredoc_fd, int i)
{
	char	*final_line;
	char	*line;

	(void)minishell;
	final_line = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("minishell: warning: here-document delimited \
			by end-of-file (wanted `%s')\n", cmd->heredocs[i]);
			close(heredoc_fd);
			break ;
		}
		if (ft_strcmp(line, cmd->heredocs[i]) == 0)
		{
			free(line);
			close(heredoc_fd);
			break ;
		}
		if (cmd->expand_heredoc_content)
			final_line = expand_heredoc_line(minishell, line);
		else
			final_line = ft_strdup(line);
		ft_putendl_fd(line, heredoc_fd);
		free(line);
		if (final_line)
			free(final_line);
	}
	return ;
}

/**
 * Logic that gets a path for the last heredoc created
 */
char	*get_heredocs(t_minishell *minishell, t_cmd *cmd)
{
	int		i;
	int		n;
	char	*filepath;
	char	*last_filepath;
	int		heredoc_fd;

	if (!cmd->heredocs || !cmd->heredocs[0])
		return (NULL);
	i = 0;
	heredoc_fd = -1;
	last_filepath = NULL;
	while (cmd->heredocs[i])
	{
		if (last_filepath)
		{
			unlink(last_filepath);
			free(last_filepath);
			last_filepath = NULL;
		}
		n = 0;
		while (1)
		{
			filepath = ft_strjoin("/tmp/.heredoc_minishell", ft_itoa(i + n));
			if (access(filepath, F_OK) == 0)
			{
				free(filepath);
				n += 1;
			}
			else
				break ;
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

/**
 * Logic to get a file descriptor from the heredoc temp file
 */
int	manage_heredocs(t_cmd *cmd, t_fds *fd)
{
	int	heredoc_fd;

	(void)fd;
	if (cmd->last_heredoc_filepath != NULL)
	{
		heredoc_fd = open(cmd->last_heredoc_filepath, O_RDONLY);
		if (heredoc_fd == -1)
		{
			perror("minishell: heredoc");
			unlink(cmd->last_heredoc_filepath);
			return (-1);
		}
		else
		{
			unlink(cmd->last_heredoc_filepath);
			return (heredoc_fd);
		}
	}
	return (-1);
}
