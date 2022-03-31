# C++ Portscanner
This tool will show you the open ports on a given IP address or domain name. The application uses the sfml-network library in order to test the ports. Please use responsibly as scanning ports can be seen as malicious behavior. "scanme.nmap.org" is a website that will freely allow you to scan their ports several times a day and should be used for testing this application on non-local networks. Otherwise, test it on localhost.

##Installation
In order to compile the source code into an executable, you must have the SFML libraries installed. On Linux, check your distribution's repository. For Windows and Mac, visit [the SFML website] (https://www.sfml-dev.org/index.php). The following directions will be for compiling on Linux using g++.
First, you will need to compile the source code:
```
g++ -c portscanner.cpp
```
Then, link the compiled file to the required SFML libraries. For this code, you need only link it to lsfml-network and lsfml-system.
```
g++ portscanner.o -o portscanner -lsfml-network -lsfml-system
```
Finally, you're ready to run your compiled code.
```
./portscanner
```
## Usage
The application is run through its executable file after compilation. For Linux, use the ./ operator to run the file in your terminal emulator.
```
./portscanner
```
If you cannot run the file, make sure that it has the execute flag set. Add it with:
```
chmod +x portscanner
```

###Modes
The tool can be used in either command-line mode or interactive mode. In order to enter command line mode you need to run it with the IP/domain name and the port range as command-line arguments. For example:
```
./portscanner localhost 1-1000
```
If you don't enter any arguments, you will enter interactive mode in which the application will ask you for these values as it runs.

###Port Ranges
Port ranges can be entered by using the , and - characters.

, denotes two specific ports or ranges (think of AND).
The following command scans ports 1 and 2.
```
./portscanner localhost 1,2
```
The - character specifies a range of ports to be scanned (think of THROUGH).
The following command scans ports 1 through 1000.
```
./portscanner localhost 1-1000
```
Finally, the word "all" can be entered to scan all ports from 0-100000. Make sure all is all lowercase.
```
./portscanner localhost all
```

