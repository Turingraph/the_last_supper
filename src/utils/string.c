#include "utils.h"

/**
 * Allocate and initialize a memory block with zero values.
 * Print a message to stdout if allocation fails and comment is provided.
 *
 * time/space: O(n) / O(n)
 *
 * status: public api
 * 
 * @param elem_size size of the memory block in bytes
 * @param comment message to print when allocation fails
 *
 * @return pointer to the initialized memory block, or NULL on failure
 */
void	*malloc_talk(size_t elem_size, const char *comment)
{
	size_t			i;
	unsigned char	*d;
	void			*dst;

	if (elem_size == 0)
		return (NULL);
	dst = (void *)malloc(elem_size);
	if (dst == NULL)
	{
		if (comment != NULL && *comment != '\0')
		{
			write(1, "Malloc Fail: ", 14);
			write(1, comment, f_strlen(comment));
		}
	}
	d = (unsigned char *)dst;
	i = 0;
	while (i < elem_size)
	{
		*d = 0;
		d += 1;
		i += 1;
	}
	return (dst);
}

/**
 * Return the length of a null-terminated string.
 * Returns 0 if str is NULL.
 *
 * time/space: O(n) / O(1)
 *
 * status: public api
 *
 * @param str string to measure
 * 
 * @return number of characters in str, excluding the terminating '\0'
 */
size_t	f_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str != NULL && *str != '\0')
	{
		i += 1;
		str += 1;
	}
	return (i);
}

/**
 * Count how many characters that the string have before 
 * encounter the target characters and/or '\0'.
 * 
 * time/space: O(n) / O(1)
 * 
 * @param str string
 * @param stop the target character
 * 
 * @return a number of all characters before the target character and/or '\0'
 */
size_t	knight_of_coin(const char *str, char stop)
{
	size_t	i;

	i = 0;
	while (str != NULL && str[i] != '\0' && str[i] != stop)
		i += 1;
	return (i);
}
