/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 10
filename : README.txt
*/

Please keep all .c files in same folder before compilation and execution


Q1) => 	

// Compilation :
	server: gcc tcp_server_1.c -o tcp_server_1
	client: gcc tcp_client_1.c -o tcp_client_1

// Execution :

	server side: $ ./tcp_server_1

[+]Server socket created successfully.
[+]Binding successfull.
[+]Listening....
Server acccepted the client data packet

Waiting to recieve from client... 
String recieved from client: computer science and engineering

Waiting to recieve from client... 
String recieved from client: convert to uppper case

Waiting to recieve from client... 
String recieved from client: numbers from 1 to 10

Waiting to recieve from client... 
String recieved from client: ABCD EFGH

Waiting to recieve from client... 
Server Exit...
[+]Closing the connection.

	client side: $ ./tcp_client_1

[+]Server socket created successfully.
[+]Connected to Server.

Enter string to send to server ("exit" to quit) : computer science and engineering 
Received UPPER CASE string from server: COMPUTER SCIENCE AND ENGINEERING

Enter string to send to server ("exit" to quit) : convert to uppper case
Received UPPER CASE string from server: CONVERT TO UPPPER CASE

Enter string to send to server ("exit" to quit) : numbers from 1 to 10
Received UPPER CASE string from server: NUMBERS FROM 1 TO 10

Enter string to send to server ("exit" to quit) : ABCD EFGH     
Received UPPER CASE string from server: ABCD EFGH

Enter string to send to server ("exit" to quit) : exit
client is quitting...
[+]Closing the connection.


Q2) => 

// Compilation :
	server: gcc tcp_server_2.c -o tcp_server_2
	client: gcc tcp_client_2.c -o tcp_client_2

// Execution :

	server side: $ ./tcp_server_2

[+]Server socket created successfully.
[+]Binding successfull.
[+]Listening....
Server acccepted the client data packet

Waiting to recieve from client... 
String recieved from client: reverse the string

Waiting to recieve from client... 
String recieved from client: 123 mangesh abcd

Waiting to recieve from client... 
String recieved from client: finsh the program

Waiting to recieve from client... 
String recieved from client: CAPITAL STRING with numbers 123

Waiting to recieve from client... 
Server Exit...
[+]Closing the connection.


	client side: $ ./tcp_client_2

[+]Server socket created successfully.
[+]Connected to Server.

Enter string to send to server ("exit" to quit) : reverse the string
Received reversed string from server: gnirts eht esrever

Enter string to send to server ("exit" to quit) : 123 mangesh abcd
Received reversed string from server: dcba hsegnam 321

Enter string to send to server ("exit" to quit) : finsh the program
Received reversed string from server: margorp eht hsnif

Enter string to send to server ("exit" to quit) : CAPITAL STRING with numbers 123
Received reversed string from server: 321 srebmun htiw GNIRTS LATIPAC

Enter string to send to server ("exit" to quit) : exit
client is quitting...
[+]Closing the connection.



Q3) => 

// Compilation :
	server: gcc tcp_server_3.c -o tcp_server_3
	client: gcc tcp_client_3.c -o tcp_client_3

// Execution :

	server side: $ ./tcp_server_3

[+]Server socket created successfully.
[+]Binding successfull.
[+]Listening....
Server acccepted the client data packet

Waiting to recieve from client... 
Integer Array received from client: 1 2 3 4 5 6 7 8 9 10

Waiting to recieve from client... 
Integer Array received from client: -2 0 425 63128 23231 32220

Waiting to recieve from client... 
Integer Array received from client: 1111000 20 0 1

Waiting to recieve from client... 
Integer Array received from client: 3333

Waiting to recieve from client... 
Server Exit...
[+]Closing the connection.


	client side: $ ./tcp_client_3
	
[+]Server socket created successfully.
[+]Connected to Server.

Enter integer array to send to server ("exit" to quit) : 1 2 3 4 5 6 7 8 9 10
Message From Server: Integer array recieved successfully

Enter integer array to send to server ("exit" to quit) : -2 0 425 63128 23231 32220
Message From Server: Integer array recieved successfully

Enter integer array to send to server ("exit" to quit) : 1111000 20 0 1     
Message From Server: Integer array recieved successfully

Enter integer array to send to server ("exit" to quit) : 3333
Message From Server: Integer array recieved successfully

Enter integer array to send to server ("exit" to quit) : exit
client is quitting...
[+]Closing the connection.

