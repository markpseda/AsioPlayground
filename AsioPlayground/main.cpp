#include <iostream>
#include <sdkddkver.h>
#include <boost/asio.hpp>

int main()
{
	boost::asio::io_context context;
	std::cout << "Hello World!" << std::endl;
}