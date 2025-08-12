/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:06:46 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/12 15:11:23 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * writes to the heredoc temp file
 */
static void	heredoc_ln(t_minishell *m, t_cmd *cmd, int heredoc_fd, char *line)
{
	char	*final_line;

	if (cmd->expand_heredoc_content)
	{
		final_line = expand_heredoc_line(m, line);
	}
	else
		final_line = ft_strdup(line);
	ft_putendl_fd(final_line, heredoc_fd);
	free(line);
	if (final_line)
		free(final_line);
}

/**
 * Loops that retrieves input and writes to the heredoc temp file
 */
static void	megaloop(t_minishell *minishell, t_cmd *cmd, int heredoc_fd, int i)
{
	char	*line;

	(void)minishell;
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
		heredoc_ln(minishell, cmd, heredoc_fd, line);
	}
	return ;
}

int	create_file(char *last_filepath, char **filepath, int i)
{
	int		n;
	char	*tmp_num;

	if (last_filepath)
	{
		unlink(last_filepath);
	}
	n = 0;
	while (1)
	{
		tmp_num = ft_itoa(i + n);
		*filepath = ft_strjoin("/tmp/.heredoc_minishell", tmp_num);
		free(tmp_num);
		if (access(*filepath, F_OK) == 0)
		{
			free(*filepath);
			n += 1;
		}
		else
			break ;
	}
	return (open(*filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777));
}

/**
 * Logic that gets a path for the last heredoc created
 */
char	*get_heredocs(t_minishell *minishell, t_cmd *cmd)
{
	int		i;
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
		filepath = NULL;
		heredoc_fd = create_file(last_filepath, &filepath, i);
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
