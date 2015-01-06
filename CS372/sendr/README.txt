FTP SERVER and CLIENT build and use instructions.

1. To build:
	run the command "make" from the folder where the files are stored
	this will create two executables, the ftpserver and ftpclient

2. To clean:
	run the command "make clean" from the folder where the files are stored
	this will remove the executables and various working files

3. To run:
	start the server first using the following syntax:
		./ftpserver portnumber
	where the portnumber is the port on which the ftp server should listen

	start the client next using the following syntax:
		./ftpclient host portnumber command dataport [filename]
	where the portnumber is the port the server is listening to 
	and the host is the computer name or ip address 
	'localhost' might work, it does on some target systems but not all	
	it is better practice to use the full computer name like flip.engr.oregonstate.edu
	this was built and tested on flip.engr.oregonstate.edu
	command is either -l for list or -g for get
	-l "list" will list the files in the ftp server directory on the client display
	-g "get" will down load the specified file as FILENAME.copy to the directory of ftp client
	if FILENAME.copy already exists the client will exit with an error
	both the -l and -g requires use of a dataport greater than 10000 but less than 65535
	the -g also requires a filename specified
	if the file doesn't exist the server will let the client know of the error

	use make rmcopy to remove copied files easily

	****NOTE**** 
	the client and server MUST run on the same machine and session; they MUST share the localhost value

4. Example Use:
	ftpserver 44444												#starts server
	ftpclient flip.engr.oregonstate.edu 44444 -l 44445			#queries server for file listing
	ftpclient flip.engr.oregonstate.edu 44444 -g short.txt 44445#gets short.txt from server
