/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 9
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
String recieved from client: Indian Institute of Technology Patna
Number of vowels in recieved string is 13

Waiting to recieve from client... 
Server Exit...
[+]Closing the connection.

	client side: $ ./tcp_client_1 

[+]Server socket created successfully.
[+]Connected to Server.

Enter string to send to server ("exit" to quit) : Indian Institute of Technology Patna
Message From Server: String recieved successfully

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
String recieved from client: Mangesh Chandrawanshi
Received string is not a palindrome

Waiting to recieve from client... 
String recieved from client: aabbaa
Received string is a palindrome

Waiting to recieve from client... 
String recieved from client: aba
Received string is a palindrome

Waiting to recieve from client... 
String recieved from client: x
Received string is a palindrome

Waiting to recieve from client... 
String recieved from client: query
Received string is not a palindrome

Waiting to recieve from client... 
Server Exit...
[+]Closing the connection.


	client side: $ ./tcp_client_2
[+]Server socket created successfully.
[+]Connected to Server.

Enter string to send to server ("exit" to quit) : Mangesh Chandrawanshi
Message From Server: String recieved successfully

Enter string to send to server ("exit" to quit) : aabbaa
Message From Server: String recieved successfully

Enter string to send to server ("exit" to quit) : aba
Message From Server: String recieved successfully

Enter string to send to server ("exit" to quit) : x
Message From Server: String recieved successfully

Enter string to send to server ("exit" to quit) : query
Message From Server: String recieved successfully

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
Integer Array received from client: 1 2 3 4 5

Waiting to recieve from client... 
Integer Array received from client: 12 245 8741 8 3567 1331 321 222

Waiting to recieve from client... 
Integer Array received from client: 1

Waiting to recieve from client... 
Integer Array received from client: 0 256 -235 0

Waiting to recieve from client... 
Integer Array received from client: -1 -2 -3 -4 -5 10

Waiting to recieve from client... 
Server Exit...
[+]Closing the connection.

	client side: $ ./tcp_client_3

[+]Server socket created successfully.
[+]Connected to Server.

Enter integer array to send to server ("exit" to quit) : 1 2 3 4 5
Message From Server: Integer array recieved successfully
Sum of integer array elements: 15

Enter integer array to send to server ("exit" to quit) : 12 245 8741 8 3567 1331 321 222
Message From Server: Integer array recieved successfully
Sum of integer array elements: 14447

Enter integer array to send to server ("exit" to quit) : 1
Message From Server: Integer array recieved successfully
Sum of integer array elements: 1

Enter integer array to send to server ("exit" to quit) : 0 256 -235 0 
Message From Server: Integer array recieved successfully
Sum of integer array elements: 21

Enter integer array to send to server ("exit" to quit) : -1 -2 -3 -4 -5 10
Message From Server: Integer array recieved successfully
Sum of integer array elements: -5

Enter integer array to send to server ("exit" to quit) : exit
client is quitting...
[+]Closing the connection.

