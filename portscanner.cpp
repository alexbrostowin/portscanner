#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

bool port_is_open(const std::string& ip, int port){
	sf::TcpSocket socket; //create socket struct
	bool open = (socket.connect(sf::IpAddress(ip), port) == sf::Socket::Done); //connect to socket on ip and port specified
	socket.disconnect(); //disconnect from the socket

	return open;
}

static std::vector<std::string> split_string(const std::string& s, char delim = ' ', bool allow_empty = false){
	std::vector<std::string> tokens; //create vector containing strings
	std::stringstream sstream(s); //create string stream
	std::string token;

	while (std::getline(sstream, token, delim)){ //tokens are the parts of the string separated by the delimiter
		if (allow_empty || token.size() > 0) //if allow empty is true or there are tokens, add them to the vector
			tokens.push_back(token);
	}
	return tokens; //return the vector
}

static int string_to_int(const std::string& s){
	std::stringstream sstream(s);
	int i;
	sstream >> i;
	return i;
}

template <typename T>
static void swap(T& a, T& b){ //swaps two values
	T c = a;
	a = b;
	b = c;
}

template <typename T>
static std::vector<T> range(T min, T max){ //generates vector containing a range
	//validate input
	if (min > max)
		swap(min, max);
	if (min == max)
		return std::vector<T>(1,min);

	std::vector<T> values;
	
	for (; min <= max; ++min) //add the min to the vector, then increase it by one
		values.push_back(min);
	return values;
}

static std::vector<int> parse_ports(const std::string& list){
	std::vector<int> ports;
	if (list == "all"){
		for (int port : range(0,100000))
			ports.push_back(port);
	}
	else{
		for (const std::string& token : split_string(list, ',')){ //comma denotes a list, add those specific values
			std::vector<std::string> portrange = split_string(token, '-'); //hypen denotes a range, add all values between

		switch (portrange.size()){
			case 0: //one value only
				ports.push_back(string_to_int(token));
				break;

			case 1: //also only one value
				ports.push_back(string_to_int(portrange[0]));
				break;

			case 2: //now its a real range
			{
				int min = string_to_int(portrange[0]);
				int max = string_to_int(portrange[1]);

				for (int port : range(min,max)) //add all the ports between the min and the max
					ports.push_back(port);
				break;
			}
			default:
				break;
			}
		}
	}
	return ports;

}

template <typename T>
static T max(const std::vector<T>& values){
	T max = values[0];
	for (T value : values){
		if (value > max)
			max = value;
	}
	return max;
}

template <typename T>
static size_t digits(T value){
	size_t count;

	if (value < 0)
		count = 1;
	else
		count = 0;

	if (value == 0)
		return 0;
	while (value){
		value /= 10;
		++count;
	};
	return count;
}

int main(int argc, char* argv[]){
	std::string ip;
	std::vector<int> refined_ports;
	
	if (argc == 3){ //if the user gives command-line args, use them
		ip = argv[1];
		refined_ports = parse_ports(std::string(argv[2]));
	} else{ //enter interactive mode, get the values from input
	std::string raw_ports;
	
	std::cout << "Enter IP address or domain name: ";
	std::cin >> ip;
	std::cout << "Enter ports (a,b for list, x-y for range, all for all): ";
	std::cin >> raw_ports;
	
	refined_ports = parse_ports(raw_ports);
	}

	size_t width = digits(max(refined_ports));

	std::cout << "Open ports on " << ip << ":\n";
	for (int port : refined_ports){
		if (port_is_open(ip, port))
			std::cout << std::setw(width) << port << ": OPEN\n";
	}
	return 0;
}
