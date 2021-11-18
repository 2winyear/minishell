#include "../include/minishell.h"

void    display_logo(void)
{
    int     fd;
    int     bytes;
    char    buf[1025];

    // /Users/{USER_NAME}/Downloads/minishell/minishell/util/front_logo
    fd = open("/Users/byeukim/Downloads/minishell/minishell/minishell/util/front_logo",O_RDONLY);
    if (fd < 0)
        return ;
    bytes = read(fd, buf, 1024);
    buf[bytes] = '\0';
    if (bytes == -1)
    {
        close(fd);
        return ;
    }
    printf("%s", buf);
    close(fd);
}
