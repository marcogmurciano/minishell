/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:06:46 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/04 12:10:09 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	elbuclaso(char *line, t_cmd *cmd, t_fds *fd, int i)
{
	char	*final_line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (ft_strcmp(line, cmd->heredocs[i]) == 0)
			{
				free(line);
				close(fd->heredoc);
				fd->heredoc = -1;
				break ;
			}
			if (cmd->expand_heredoc_content)
				final_line = expand_heredoc_line(fd->minishell, line);
			else
				final_line = ft_strdup(line);
			ft_putendl_fd(line, fd->heredoc);
			free(line);
			free(final_line);
		}
		else
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
			cmd->heredocs[i]);
			close(fd->heredoc);
			fd->heredoc = -1;
			break ;
		}
	}
}

int	manage_heredocs(t_cmd *cmd, t_fds *fd)
{
	int		i;
	char	*line;
	char	*filepath;
	char	*final_line;
	char	*last_filepath;

	i = 0;
	final_line = NULL;
	line = NULL;
	while (cmd->heredocs[i])
	{
		filepath = ft_strjoin("/tmp/.heredoc_minishell", ft_itoa(i));
		if (fd->heredoc != -1)
		{
			close(fd->heredoc);
			fd->heredoc = -1;
		}
		if (access(filepath, F_OK) == 0)
			unlink(filepath);
		fd->heredoc = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd->heredoc == -1)
			perror("");
		elbuclaso(line, cmd, fd, i);
		if (last_filepath)
			free(last_filepath);
		last_filepath = filepath;
		i++;
	}
	if (cmd->last_in == 0 && last_filepath)
	{
		if (fd->in != 0 && fd->in != -1)
			close(fd->in);
		fd->in = open(last_filepath, O_RDONLY);
		if (fd->in == -1)
			perror("Error opening heredoc file for reading");
	}
	if (last_filepath)
		free(last_filepath);
	return (fd->heredoc);
}
