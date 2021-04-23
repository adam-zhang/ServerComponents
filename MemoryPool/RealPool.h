/********************************************************************************
> FileName:	RealPool.h
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Apr 23 09:15:36 2021
********************************************************************************/
#ifndef __REALPOOL__H
#define __REALPOOL__H

#include <list>
#include <vector>
#include <tuple>
#include <mutex>
#include <iostream>

namespace ServerComponents
{

	template<typename T, int number = 1024>
	class RealPool
	{
		template<typename Y>
		struct Pair
		{
			public:
				Pair()
					:isUsed(false)
				{}
			bool isUsed;
			Y object;
		};
		public:
			RealPool()
			{
				std::vector<T> v(1024);
				list_.push_back(v);
			}
			~RealPool(){};
		private:
			std::list<std::vector<Pair<T>>> list_;
			std::mutex mutex_;
		public:
			T* alloc()
			{
				for(auto v = list_.begin(); v != list_.end(); ++v)
					for(auto e = v->begin(); e != v->end(); ++e )
					{
						if (!e->isUsed)
						{
							std::lock_guard<std::mutex> lock(mutex_);
							e->isUsed = true;
							return &e->object;
						}
					}
				std::cout << "add new" << std::endl;
				std::vector<T> v(number);
				list_.emplace_back(v);
				return alloc();
			}

			void dealloc(T* p)
			{
				for(auto v = list_.begin(); v != list_.end(); ++v)
					for(auto e = v->begin(); e != v->end(); ++e)
					{
						if (&e->object == p)
						{
							std::lock_guard<std::mutex> lock(mutex_);
							e->isUsed = false;
						}
					}

			}

	};
}

#endif//__REALPOOL__H
