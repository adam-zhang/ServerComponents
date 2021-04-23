#include <iostream>
#include <thread>
#include <cstdlib>
#include "Queue.h"

using namespace std;


class Random
{
	public:
		Random()
		{
			srand(time(NULL));
		}

		int random()
		{
			return rand();
		}
};



int getNumber()
{
	static Random random;
	return random.random() % 100;
}

void producer(Queue<int>& queue)
{
	for(auto i = 0; i != 100; ++i)
	{
		//int n = getNumber();
		queue.push(i);	
		cout << "pushed:" << i << endl;
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void consumer(Queue<int>& queue)
{
	while(queue.size() > 0)
	{
		int n = queue.pop();
		cout << "consumed:" << n << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}


int main(int argc, char** argv)
{
	Queue<int> queue;
	thread t1(producer, ref(queue));
	thread t2(producer, ref(queue));
	thread t3(consumer, ref(queue));

	t1.join();
	t2.join();
	t3.join();
	return 0;
}
