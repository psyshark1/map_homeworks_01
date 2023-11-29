#include <iostream>
#include<thread>
#include<chrono>

int clients{0};

void clients_queue(int max_clnts)
{
	while (true)
	{
		if (clients == max_clnts) { break; }
		++clients;
		std::cout << "Queue is " << clients << " clients" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void operationist()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	while (true)
	{
		if (!clients) { break; }
		--clients;
		std::cout << "Queue is " << clients << " clients" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

}

int main()
{
	std::thread th1(clients_queue, 20);
	std::thread th2(operationist);

	th1.detach();
	th2.detach();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	while (true)
	{
		if (!clients) { break; }
	}
	return 0;
}
