#include "shell.h"

/**
<<<<<<< HEAD
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: string field
 * @num: node index used by history
 * Return: size of list
=======
 * add_node - a node is added to the start of the list
 * @head: the head node to address of pointer
 * @str: nodes of str field
 * @num: history is used by node index
 *
 * Return: list of sizes
>>>>>>> refs/remotes/origin/master
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
<<<<<<< HEAD
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: string field
 * @num: node index used by history
 * Return: size of list
=======
 * add_node_end - a node is added to the end of the list
 * @head: the head node to address of pointer
 * @str: nodes of str field
 * @num: history is used by node index
 *
 * Return: list of sizes
>>>>>>> refs/remotes/origin/master
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/*
 * print_list_str - prints only the str element
 * @h: pointer to first node
 * Return: size of list
=======
*
 * print_list_str - the str element of a list_t linked list is only printed
 * @h: first node to pointer
 *
 * Return: list of sizes
>>>>>>> refs/remotes/origin/master
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
<<<<<<< HEAD
 * delete_node_at_index - deletes node
 * @head: address first node  pointer
 * @index: index of node to delete
 * Return: 1 on success, 0 on otherwise
=======
 * delete_node_at_index - node is deleted at given index
 * @head: first node to address of pointer
 * @index: delete index node
 *
 * Return: success on 1, failure on 0
>>>>>>> refs/remotes/origin/master
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
<<<<<<< HEAD
 * free_list - frees all nodes
 * @head_ptr: address of pointer
 * Return: nothing
=======
 * free_list - all list of nodes are freed
 * @head_ptr: head node to address of pointer
 *
 * Return: void
>>>>>>> refs/remotes/origin/master
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

