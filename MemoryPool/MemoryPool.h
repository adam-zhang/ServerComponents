/********************************************************************************
> FileName:	MemoryPool.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Apr 23 09:06:35 2021
********************************************************************************/
#ifndef __MEMORYPOOL__H
#define __MEMORYPOOL__H

#include "RealPool.h"
#include <memory>

namespace ServerComponents
{
	template<typename T>
	class MemoryPool
	{
	public:
		MemoryPool() {}
		~MemoryPool() {}
	public:
		T* alloc()
		{
			return realPool_.alloc();
		}
		void dealloc(T* p)
		{
			realPool_.dealloc(p);
		}
	private:
		RealPool<T> realPool_;
	};
}

#endif//__MEMORYPOOL__H
