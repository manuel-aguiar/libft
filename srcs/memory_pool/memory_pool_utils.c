/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_pool_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:35:02 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:35:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_pool.h"

static t_uchar*	mpool_ind_to_addr(const t_mpool *pool, t_uint i)
{
	return (pool->pool_start + (i * pool->block_size));
}

static t_uint	mpool_addr_to_ind(const t_mpool *pool, const t_uchar* p)
{
	return (((t_uint)(p - pool->pool_start)) / pool->block_size);
}

void	*mpool_alloc(t_mpool *pool)
{
	t_uint	*p;
	void	*ret;

	if (pool->used_blocks < pool->block_num)
	{
		p = (t_uint *)mpool_ind_to_addr(pool, pool->used_blocks);
		*p = pool->used_blocks + 1;
		pool->used_blocks++;                           //tenta meter isto na linha de cima a ver se rebenta
	}
	ret = NULL;
	if (pool->free_blocks > 0)
	{
		ret = (void *)pool->next_empty;
		--pool->free_blocks;
		if (pool->free_blocks != 0)
			pool->next_empty = mpool_ind_to_addr(pool, *((t_uint *)pool->next_empty));
		else
			pool->next_empty = NULL;
	}
	else
	{
		if (!pool->next_pool)
			pool->next_pool = mpool_create(pool->block_size, UPSIZE(pool->block_num));
		return (mpool_alloc(pool->next_pool));
	}
	return (ret);
}

void	mpool_dealloc(t_mpool *pool, void* to_free)
{
	if (!pool || !to_free)
		return ;
	if ((t_uchar *)to_free >= pool->pool_start && (t_uchar *)to_free < pool->pool_end)
	{
		if (pool->next_empty != NULL)
		{
			(*(t_uint *)to_free) = mpool_addr_to_ind(pool, pool->next_empty);
			pool->next_empty = (t_uchar *)to_free;
		}
		else
		{
			*((t_uint *)to_free) = pool->block_num;
			pool->next_empty = (t_uchar *)to_free;
		}
		++pool->free_blocks;
	}
	else
		mpool_dealloc(pool->next_pool, to_free);
}
