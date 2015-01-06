CHAT SERVER and CLIENT build and use instructions.

1. To build:
	run the command "make" from the folder where the files are stored
	this will create two executables, the chatserver and chatclient

2. To clean:
	run the command "make clean" from the folder where the files are stored
	this will remove the executables

3. To run:
	start the server first using the following syntax:
		./chatserver portnumber
	where the portnumber is the port on which the chat server should listen

	start the client next using the following syntax:
		./chatclient host portnumber
	where the portnumber is the port the server is listening to 
	and the host is the computer name or ip address 
	'localhost' might work, it does on some target systems but not all	
	it is better practice to use the full computer name like flip.engr.oregonstate.edu
	this was built and tested on flip.engr.oregonstate.edu

4. To control:
	Once chatclient is launched enter a handle (as prompted)
	Then type messages back and forth. Client must go first and then
	the server, and then repeat that cycle. Either the server or client can
	end the session by typing '\quit' when it is their turn to chat
