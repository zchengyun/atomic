#include <iostream>
//原子数据类型不会发生数据竞争，能直接用在多线程中而不必我们用户对其进行添加互斥资源锁的类型。
//可以理解为这些原子类型内部自己加了锁。
#include <atomic>
#include <thread>
#include <vector>

int int_count = 0;
std::atomic_int atomic_count = 0;

void foo1() {
	int i = 0;
	while (i<100)
	{
		i++;
		int_count++;
		atomic_count++;
	}
}

void foo2() {
	int i = 0;
	while (i < 100)
	{
		i++;
		int_count--;
		atomic_count--;
	}
}

int main()
{
	int i = 0,j=0;
	std::vector<std::thread> thread_list;
	while (i<1000)
	{
		thread_list.push_back(std::thread(foo1));
		i++;
	}

	while (j < 1000)
	{
		thread_list.push_back(std::thread(foo2));
		j++;
	}

	for (auto& thread : thread_list) {
		thread.join();
	}

	std::cout << "int_count=" << int_count << "\tatomic=" << atomic_count << std::endl;

}
