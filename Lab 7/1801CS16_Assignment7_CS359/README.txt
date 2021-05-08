/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 7
filename : README.txt
*/

Q1) Write a program for error detection using Cyclic redundancy check(CRC). Demonstrate
the packets captured traces using Wireshark Packet Analyzer Tool for peer to peer
mode.

-> 
Each Character in the sent data file is subject to following steps :

	-For error detection CRC is used.
	-Each character is converted into corresponding ASCII code of 8 bits.
	-Then it is split into 4 bits - 4 bits.
	-Both of these splits are added 3 CRC bits and send to the receiver
	-4 bit CRC divisor is used to find CRC bits
	-Receiver then checks if valid bits are received or not
	-Using these receiver decodes the character and displays on screen.

// Compilation Instructions:

Keep all the files in same folder
send.txt file contains data to be sent, please modify data in the same file if you want to send different data.

To Compile Receiver: gcc receiver.c -o receiver
To Compile Sender: gcc sender.c -o sender 
To Execute Receiver: ./receiver
To Execute Sender: ./sender 

** Sender Side Output : 
$ gcc sender.c -o sender
$ ./sender
[+]Sender side socket created successfully.
[+]Connected to Reciever
 Sent Character : H
 CRC Code for first 4 bits : 0001011	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : E
 CRC Code for first 4 bits : 1010011	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : L
 CRC Code for first 4 bits : 0011101	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : L
 CRC Code for first 4 bits : 0011101	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : O
 CRC Code for first 4 bits : 1111111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : 

 CRC Code for first 4 bits : 0101100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0000000		[+]Received Positive Acknowledgement

 Sent Character : C
 CRC Code for first 4 bits : 1100010	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : A
 CRC Code for first 4 bits : 1000101	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : T
 CRC Code for first 4 bits : 0010110	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character :  
 CRC Code for first 4 bits : 0000000	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0100111		[+]Received Positive Acknowledgement

 Sent Character : D
 CRC Code for first 4 bits : 0010110	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : O
 CRC Code for first 4 bits : 1111111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : G
 CRC Code for first 4 bits : 1110100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : 

 CRC Code for first 4 bits : 0101100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0000000		[+]Received Positive Acknowledgement

 Sent Character : T
 CRC Code for first 4 bits : 0010110	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : I
 CRC Code for first 4 bits : 1001110	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : G
 CRC Code for first 4 bits : 1110100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : E
 CRC Code for first 4 bits : 1010011	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : R
 CRC Code for first 4 bits : 0100111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : 

 CRC Code for first 4 bits : 0101100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0000000		[+]Received Positive Acknowledgement

 Sent Character : L
 CRC Code for first 4 bits : 0011101	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : I
 CRC Code for first 4 bits : 1001110	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : O
 CRC Code for first 4 bits : 1111111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : N
 CRC Code for first 4 bits : 0111010	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : 

 CRC Code for first 4 bits : 0101100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0000000		[+]Received Positive Acknowledgement

 Sent Character : H
 CRC Code for first 4 bits : 0001011	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : O
 CRC Code for first 4 bits : 1111111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : R
 CRC Code for first 4 bits : 0100111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : S
 CRC Code for first 4 bits : 1100010	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : E
 CRC Code for first 4 bits : 1010011	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character :  
 CRC Code for first 4 bits : 0000000	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0100111		[+]Received Positive Acknowledgement

 Sent Character : Z
 CRC Code for first 4 bits : 0101100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : E
 CRC Code for first 4 bits : 1010011	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : B
 CRC Code for first 4 bits : 0100111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : R
 CRC Code for first 4 bits : 0100111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : A
 CRC Code for first 4 bits : 1000101	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character :  
 CRC Code for first 4 bits : 0000000	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0100111		[+]Received Positive Acknowledgement

 Sent Character : C
 CRC Code for first 4 bits : 1100010	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : O
 CRC Code for first 4 bits : 1111111	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0010110		[+]Received Positive Acknowledgement

 Sent Character : W
 CRC Code for first 4 bits : 1110100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 1010011		[+]Received Positive Acknowledgement

 Sent Character : 

 CRC Code for first 4 bits : 0101100	[+]Received Positive Acknowledgement
 CRC Code for last 4 bits : 0000000		[+]Received Positive Acknowledgement

[+]Data sent successfully.
[+]Closing the connection.

** Receiver Side Output :

$ gcc receiver.c -o receiver
$ ./receiver
[+]Receiver side socket created successfully.
[+]Binding successfull.
[+]Listening...
[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0001011
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : H

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1010011
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : E

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0011101
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : L

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0011101
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : L

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1111111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : O

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0101100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0000000
 Received Character : 


[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1100010
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : C

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1000101
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : A

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0010110
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : T

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0000000
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0100111
 Received Character :  

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0010110
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : D

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1111111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : O

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1110100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : G

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0101100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0000000
 Received Character : 


[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0010110
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : T

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1001110
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : I

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1110100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : G

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1010011
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : E

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0100111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : R

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0101100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0000000
 Received Character : 


[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0011101
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : L

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1001110
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : I

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1111111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : O

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0111010
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : N

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0101100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0000000
 Received Character : 


[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0001011
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : H

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1111111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : O

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0100111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : R

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1100010
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : S

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1010011
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : E

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0000000
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0100111
 Received Character :  

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0101100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : Z

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1010011
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : E

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0100111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : B

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0100111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : R

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1000101
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : A

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0000000
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0100111
 Received Character :  

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1100010
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : C

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1111111
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0010110
 Received Character : O

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 1110100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 1010011
 Received Character : W

[+]Remainder is zero. No error while transmission of data	 CRC Code for first 4 bits : 0101100
[+]Remainder is zero. No error while transmission of data	 CRC Code for last 4 bits : 0000000
 Received Character : 

[+]Data received successfully.

Wireshark Packet Capture is also attached in the zip.
Total Number of Packets Captured : 334

Thank You.
***********************************************************************************************************