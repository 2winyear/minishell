#include "../include/minishell.h"

env_queue   *create_queue(void)
{
    env_queue   *env_que;

    env_que = malloc(sizeof(env_queue));
    if (!env_que)
        return (NULL);
    else
    {
        env_que->curr_ele_cnt = 0;
        env_que->header_node.prev_node = NULL;
        env_que->header_node.next_node = &(env_que->tailer_node);
        env_que->tailer_node.prev_node = &(env_que->header_node);
        env_que->tailer_node.next_node = NULL;
    }
    return (env_que);
}

int     push_queue(env_queue *env_queue, env_node element)
{
    env_node    *new_node;

    new_node = malloc(sizeof(env_node));
    if (!new_node)
        return (-1);
	new_node->key = element.key;
	new_node->value = element.value;
    new_node->prev_node = env_queue->tailer_node.prev_node;
    new_node->next_node = &(env_queue->tailer_node);
    new_node->prev_node->next_node = new_node;
    new_node->next_node->prev_node = new_node;
    env_queue->curr_ele_cnt++;
    return (1);
}

env_node     *pop_queue(env_queue *env_que)
{
    env_node    *node;

    if (!env_que || !env_que->curr_ele_cnt)
        return (NULL);
    else
    {
        node = env_que->header_node.next_node;
        env_que->header_node.next_node = node->next_node;
        node->next_node->prev_node = &(env_que->header_node);
        env_que->curr_ele_cnt--;
        return (node);
    }
}

env_node     *peak_queue(env_queue *env_que)
{
    env_node    *node;

    if (!env_que || !env_que->curr_ele_cnt)
        return (NULL);
    else
    {
        node = env_que->header_node.next_node;
        return (node);
    }
}

void    delete_queue(env_queue *env_que)
{
    env_node    *node;

    if (!env_que)
        return ;
    while ((node = pop_queue(env_que)))
    {
        free(node->key);
        free(node->value);
        free(node);
    }
    free(env_que);
}

env_queue   *init_env(char **env)
{
    env_queue   *env_que;
    env_node    node;
    int         idx;
    int         i;

    env_que = create_queue();
    if (!env_que)
        return(NULL);
    idx = -1;
    while (env[++idx])
    {
        i = -1;
        while (env[idx][++i])
        {
            if (env[idx][i] == '=')
            {
                node.key = ft_strndup(env[idx], i);
                node.value = ft_strdup(env[idx] + i + 1);
                push_queue(env_que, node);
                break ;
            }
        }
    }
    return(env_que);
}