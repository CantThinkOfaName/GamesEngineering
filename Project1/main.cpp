#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>


std::mutex m;
int i = 0;
std::atomic <long long> atom;

 class TicketLock {
public:
	int nowServing = 0;
	int nextTicket = 0;

	void init() {
		nowServing = 0;
		nextTicket = 0;
	}
	void aquire(int myTicket) {
		myTicket = atom.fetch_add(1);
		while (nowServing !=myTicket) {
			std::cout << myTicket << " Now Waiting" << std::endl;
		}
		std::cout << "Now Serving: " << myTicket << std::endl;
	}
	void release() {
		nowServing++;
		
	}
};

TicketLock ticket;


void UseTicket()
{
	ticket.aquire(i);
	std::cout << i << " Is now picking up purchase" << std::endl;
	i++;
	ticket.release();
}
int main()
{
	
	ticket.init();
	
	std::thread customer1(UseTicket);
	
	std::thread customer2(UseTicket);

	std::thread customer3(UseTicket);

	customer1.join();
	customer2.join();
	customer3.join();
	system("PAUSE");
	return 0;
}