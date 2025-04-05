/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faresms <faresms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 06:20:16 by faresms           #+#    #+#             */
/*   Updated: 2025/03/11 10:59:00 by faresms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_buffer(char *buf)
{
	int		i;
	int		j;
	char	*updated_buf;

	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
		return (NULL);
	updated_buf = malloc(ft_strlen(buf) - i + 1);
	if (!updated_buf)
		return (NULL);
	i++;
	j = 0;
	while (buf[i])
		updated_buf[j++] = buf[i++];
	updated_buf[j] = '\0';
	free(buf);
	return (updated_buf);
}

char	*extract_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf || !*buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_fd(int fd, char *buf)
{
	char	*temp;
	char	read_buf[BUFFER_SIZE + 1];
	int		byts_read;

	while (!ft_strchr(buf, '\n'))
	{
		byts_read = read(fd, read_buf, BUFFER_SIZE);
		if (byts_read <= 0)
			return (buf);
		read_buf[byts_read] = '\0';
		temp = ft_strjoin(buf, read_buf);
		if (!temp)
			return (NULL);
		buf = temp;
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	char		*temp_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_fd(fd, buf);
	if (!buf)
		return (NULL);
	line = extract_line(buf);
	temp_buf = trim_buffer(buf);
	if (!temp_buf)
	{
		free(buf);
		buf = NULL;
	}
	else
		buf = temp_buf;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
