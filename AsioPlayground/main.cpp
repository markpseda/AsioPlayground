#include <iostream>
#include <sdkddkver.h>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
int main()
{
	
	boost::system::error_code ec;

	boost::asio::io_context context;

	//IP address of https://community.onelonecoder.com/ from tutorial https://youtu.be/2hNdkYInj4g
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("51.38.81.49", ec), 80);


	boost::asio::ip::tcp::socket socket(context);

	socket.connect(endpoint, ec);

	if (socket.is_open())
	{
		std::cout << "Connected!" << std::endl;


		std::string sRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

		socket.wait(socket.wait_read);

		size_t bytes = socket.available();
		std::cout << "Bytes available: " << bytes << std::endl;

		if (bytes > 0)
		{
			std::vector<char> vBuffer(bytes);
			socket.read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()), ec);

			for (auto& c : vBuffer)
			{
				std::cout << c;
			}
		}

	}
	else
	{
		std::cout << "Not connected :(" << std::endl;
	}



	std::cout << "Hello World!" << std::endl;
}