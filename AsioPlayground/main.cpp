#include <iostream>
#include <sdkddkver.h>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


std::vector<char> vBuffer(1 * 1024);

void GrabSomeData(boost::asio::ip::tcp::socket& socket)
{
	socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()), [&] (std::error_code ec, std::size_t length) {

		if (ec)
		{
			std::cout << "error: " << ec.message() << std::endl;
			return;
		}

		std::cout << "\n\nLength: " << length << " bytes\n\n";


		for (int i = 0; i < length; i++)
		{
			std::cout << vBuffer[i];
		}

		GrabSomeData(socket);
	});
}

int main()
{
	
	boost::system::error_code ec;

	// Where asio does work
	boost::asio::io_context context;

	// Idle fake work to keep context running
	boost::asio::io_context::work idleWork(context);


	// Start context in its own thread
	std::thread thrContext = std::thread([&]() { context.run(); });

	//IP address of https://community.onelonecoder.com/ from tutorial https://youtu.be/2hNdkYInj4g
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("51.38.81.49", ec), 80);

	// Create the socket
	boost::asio::ip::tcp::socket socket(context);

	// Connect the socket
	socket.connect(endpoint, ec);

	if (socket.is_open())
	{
		std::cout << "Connected!" << std::endl;


		std::string sRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

		GrabSomeData(socket);

		std::this_thread::sleep_for(std::chrono::milliseconds(20000));

		context.stop();

	}
	else
	{
		std::cout << "Not connected :(" << std::endl;
	}
}