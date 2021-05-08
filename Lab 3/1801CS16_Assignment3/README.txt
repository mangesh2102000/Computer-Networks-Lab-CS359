/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 3 
filename : README.txt
*/

// Compilation details for TCP server-client (Port = 8048)
$ gcc -o tcpserver tcp_server.c -lssl -lcrypto
$ gcc -o tcpclient tcp_client.c -lssl -lcrypto

Type the filename which is to be sent 
Server will acknowledge the client with "Hello Client" msg.
During process of sending, the client and server both will calculate MD5 checksum
The server-side will send the final MD5 Checksum to the client, and client will match with its own checksum to verify

// Compilation details for UDP server-client (Port = 6032)
$ gcc -o udpserver udp_server.c -lssl -lcrypto
$ gcc -o udpclient udp_client.c -lssl -lcrypto

Type the filename to which is to be sent
Server will receive the filename and the file size and the number of chunks.
Client side will send the packets in chunks of 1KB, and the server will use 'recvfrom()' to receive, recvfrom() blocks the execution, so select() is used to timeout the recvfrom() after 1 sec, to resume execution.
After process of sending, the client and server both will calculate MD5 checksum,
The server-side will send the final MD5 Checksum to the client, and client will match with its own checksum to verify


// Wireshark Analyisis on ex1.txt for both TCP and UDP, wireshark captures are attached within zip
(Packets are capture till program asks from next file input in both cases; so some extra segments will also be captured)
filesize : 4123 bytes

a. Total number of segments received for TCP and the segment size distribution
->  21; 

header size : 40 bytes for initial 2 and 32 bytes for remaining 19
data size : 0 0 0 1024 0 4 0 1024 0 1024 0 1024 0 1024 0 1024 0 27 0 16 0 (sequentially)
total size for segement : header size + data size 

b. Total number of datagrams received for UDP and the datagram size​ ​distribution
-> 9; 

header size : 8 bytes for all
data size : 1024 4 4 1032 1032 1032 1032 1032 16 (sequentially)
total size for datagram : header size + data size 


// In both these cases as I have used same machine for client and server, retransmissions are likely to be 0
c. Total number of retransmitted segments for TCP
-> 0

g. Total number of retransmitted datagrams for UDP
-> 0

h. Total time to receive the file for TCP and UDP. Give justifications if you see​ ​ any time
difference between the two protocols.
-> 
	For UDP : 0.000102356 seconds (8th segment)
	For TCP : 7.001916098 seconds (19th segment)

Most of the time required in TCP is consumed initially for establishing a connection; in UDP we directly send the data (though here we have used some level of reliability), due to these transfer in case of TCP is much slower compared to UDP.
But TCP is more reliable compared to UDP.  

