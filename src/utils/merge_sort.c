/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phsottat <phsottat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 11:05:28 by phsottat          #+#    #+#             */
/*   Updated: 2026/08/11 12:14:28 by phsottat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// time : O(n)
// space: O(1)
void	copy_intarr(int *src, int *dst, size_t length)
{
	size_t	i;

	i = 0;
	while (src != NULL && dst != NULL && i < length)
	{
		dst[i] = src[i];
		i += 1;
	}
}

// time : O(1)
// space: O(1)
void	update_2_ints(int *dst, size_t *i, int src)
{
	if (dst != NULL && i != NULL)
	{
		*dst = src;
		*i += 1;
	}
}

// time : O(n)
// space: O(1)
void	linear_merge(int *src, int *dst,
	size_t start, size_t stop)
{
	size_t	mid;
	size_t	i;
	size_t	j;
	size_t	k;

	if (start <= stop && src != NULL && dst != NULL)
	{
		mid = (stop + start) / 2;
		k = start;
		i = start;
		j = mid + 1;
		while (i <= mid && j <= stop)
		{
			if (src[i] <= src[j])
				update_2_ints(dst + k, &i, src[i]);
			else
				update_2_ints(dst + k, &j, src[j]);
			k += 1;
		}
		if (i <= mid)
			copy_intarr(src + i, dst + k, mid - i + 1);
		if (j <= stop)
			copy_intarr(src + j, dst + k, stop - j + 1);
	}
}

// time : O(n log n)
// space: O(1)
void	space_free_merge_sort(int *src, int *dst, size_t start, size_t stop)
{
	size_t	mid;
	size_t	i;

	if (start < stop && src != NULL && dst != NULL)
	{
		mid = (stop + start) / 2;
		space_free_merge_sort(src, dst, start, mid);
		space_free_merge_sort(src, dst, mid + 1, stop);
		linear_merge(src, dst, start, stop);
		i = start;
		while (i <= stop)
		{
			src[i] = dst[i];
			i += 1;
		}
	}
}

// time : O(n log n)
// space: O(n)
int	*merge_sort(int *src, size_t length)
{
	int	*dst;

	if (src == NULL || length == 0)
		return (NULL);
	dst = (int *)malloc(sizeof(int) * length);
	if (dst == NULL)
		return (NULL);
	if (length == 1)
		dst[0] = src[0];
	else
		space_free_merge_sort(src, dst, 0, length - 1);
	return (dst);
}
