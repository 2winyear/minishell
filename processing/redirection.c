#include "../include/minishell.h"

/*
int		check_redirection(t_deque_node *node, t_info *info)
{
	if ()

	return (1);
}
*/
void	redirection(t_deque_node *node, t_info *info)
{
	int		fd;
	int		byte;
	char	buf[BUF_SIZE];

	fd = open(node->command[0], O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("Open error\n");
		exit(1);
	}
	byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	while (byte > 0)
	{
		buf[byte] = '\0';
		printf("%s\n", buf);
		write(fd, buf, byte);
		byte = read(STDIN_FILENO, buf, BUF_SIZE - 1);
	}
	close(fd);
	exit(0);
}
