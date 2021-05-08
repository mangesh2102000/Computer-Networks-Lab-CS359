/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 6 
filename : README.txt
*/

Q1) Write a program for error detection and correction for ASCII codes using Hamming
Codes. Demonstrate the packets captured traces using Wireshark Packet Analyzer Tool
for peer to peer mode.

-> 

Each Character in the sent data file is subject to following steps :

	-For error detection hamming code is used.
	-Each character is converted into corresponding ASCII code of 8 bits.
	-Then it is split into 4 bits - 4 bits.
	-Both of these splits are added parity bits and send to the receiver
	-Receiver then checks if valid bits are received or not
	-corrects them if invalid
	-Using these receiver decodes the character and displays on screen.


// Compilation Instructions:

Keep all the files in same folder
send.txt file contains data to be sent, please modify data in the same file if you want to send different data.

To Compile Receiver: gcc receiver.c -o receiver
To Compile Sender: gcc sender.c -o sender 
To Execute Receiver: ./receiver
To Execute Sender: ./sender 

** Sender Side Output : 
$ ./sender 
[+]Sender side socket created successfully.
[+]Connected to Reciever
 Sent Character : H
 Hamming Code for first 4 bits : 0000111
 Hamming Code for last 4 bits : 0011001

 Sent Character : E
 Hamming Code for first 4 bits : 1010010
 Hamming Code for last 4 bits : 0011001

 Sent Character : L
 Hamming Code for first 4 bits : 0011110
 Hamming Code for last 4 bits : 0011001

 Sent Character : L
 Hamming Code for first 4 bits : 0011110
 Hamming Code for last 4 bits : 0011001

 Sent Character : O
 Hamming Code for first 4 bits : 1111111
 Hamming Code for last 4 bits : 0011001

 Sent Character : 

 Hamming Code for first 4 bits : 0101101
 Hamming Code for last 4 bits : 0000000

 Sent Character : C
 Hamming Code for first 4 bits : 1100001
 Hamming Code for last 4 bits : 0011001

 Sent Character : A
 Hamming Code for first 4 bits : 1001011
 Hamming Code for last 4 bits : 0011001

 Sent Character : T
 Hamming Code for first 4 bits : 0011001
 Hamming Code for last 4 bits : 1010010

 Sent Character :  
 Hamming Code for first 4 bits : 0000000
 Hamming Code for last 4 bits : 0101010

 Sent Character : D
 Hamming Code for first 4 bits : 0011001
 Hamming Code for last 4 bits : 0011001

 Sent Character : O
 Hamming Code for first 4 bits : 1111111
 Hamming Code for last 4 bits : 0011001

 Sent Character : G
 Hamming Code for first 4 bits : 1111000
 Hamming Code for last 4 bits : 0011001

 Sent Character : 

 Hamming Code for first 4 bits : 0101101
 Hamming Code for last 4 bits : 0000000

 Sent Character : T
 Hamming Code for first 4 bits : 0011001
 Hamming Code for last 4 bits : 1010010

 Sent Character : I
 Hamming Code for first 4 bits : 1001100
 Hamming Code for last 4 bits : 0011001

 Sent Character : G
 Hamming Code for first 4 bits : 1111000
 Hamming Code for last 4 bits : 0011001

 Sent Character : E
 Hamming Code for first 4 bits : 1010010
 Hamming Code for last 4 bits : 0011001

 Sent Character : R
 Hamming Code for first 4 bits : 0101010
 Hamming Code for last 4 bits : 1010010

 Sent Character : 

 Hamming Code for first 4 bits : 0101101
 Hamming Code for last 4 bits : 0000000

 Sent Character : L
 Hamming Code for first 4 bits : 0011110
 Hamming Code for last 4 bits : 0011001

 Sent Character : I
 Hamming Code for first 4 bits : 1001100
 Hamming Code for last 4 bits : 0011001

 Sent Character : O
 Hamming Code for first 4 bits : 1111111
 Hamming Code for last 4 bits : 0011001

 Sent Character : N
 Hamming Code for first 4 bits : 0110100
 Hamming Code for last 4 bits : 0011001

 Sent Character : 

 Hamming Code for first 4 bits : 0101101
 Hamming Code for last 4 bits : 0000000

 Sent Character : H
 Hamming Code for first 4 bits : 0000111
 Hamming Code for last 4 bits : 0011001

 Sent Character : O
 Hamming Code for first 4 bits : 1111111
 Hamming Code for last 4 bits : 0011001

 Sent Character : R
 Hamming Code for first 4 bits : 0101010
 Hamming Code for last 4 bits : 1010010

 Sent Character : S
 Hamming Code for first 4 bits : 1100001
 Hamming Code for last 4 bits : 1010010

 Sent Character : E
 Hamming Code for first 4 bits : 1010010
 Hamming Code for last 4 bits : 0011001

 Sent Character :  
 Hamming Code for first 4 bits : 0000000
 Hamming Code for last 4 bits : 0101010

 Sent Character : Z
 Hamming Code for first 4 bits : 0101101
 Hamming Code for last 4 bits : 1010010

 Sent Character : E
 Hamming Code for first 4 bits : 1010010
 Hamming Code for last 4 bits : 0011001

 Sent Character : B
 Hamming Code for first 4 bits : 0101010
 Hamming Code for last 4 bits : 0011001

 Sent Character : R
 Hamming Code for first 4 bits : 0101010
 Hamming Code for last 4 bits : 1010010

 Sent Character : A
 Hamming Code for first 4 bits : 1001011
 Hamming Code for last 4 bits : 0011001

 Sent Character :  
 Hamming Code for first 4 bits : 0000000
 Hamming Code for last 4 bits : 0101010

 Sent Character : C
 Hamming Code for first 4 bits : 1100001
 Hamming Code for last 4 bits : 0011001

 Sent Character : O
 Hamming Code for first 4 bits : 1111111
 Hamming Code for last 4 bits : 0011001

 Sent Character : W
 Hamming Code for first 4 bits : 1111000
 Hamming Code for last 4 bits : 1010010

 Sent Character : 

 Hamming Code for first 4 bits : 0101101
 Hamming Code for last 4 bits : 0000000

[+]Data sent successfully.
[+]Closing the connection.

** Receiver Side Output :

$ ./receiver 
[+]Receiver side socket created successfully.
[+]Binding successfull.
[+]Listening...
[+]No error while transmission of data	 Hamming Code for first 4 bits : 0000111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : H

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1010010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : E

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0011110
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : L

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0011110
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : L

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : O

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101101
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0000000
 Received Character : 


[+]No error while transmission of data	 Hamming Code for first 4 bits : 1100001
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : C

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1001011
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : A

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0011001
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : T

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0000000
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0101010
 Received Character :  

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0011001
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : D

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : O

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111000
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : G

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101101
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0000000
 Received Character : 


[+]No error while transmission of data	 Hamming Code for first 4 bits : 0011001
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : T

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1001100
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : I

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111000
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : G

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1010010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : E

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : R

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101101
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0000000
 Received Character : 


[+]No error while transmission of data	 Hamming Code for first 4 bits : 0011110
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : L

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1001100
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : I

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : O

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0110100
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : N

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101101
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0000000
 Received Character : 


[+]No error while transmission of data	 Hamming Code for first 4 bits : 0000111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : H

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : O

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : R

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1100001
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : S

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1010010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : E

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0000000
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0101010
 Received Character :  

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101101
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : Z

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1010010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : E

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : B

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101010
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : R

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1001011
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : A

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0000000
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0101010
 Received Character :  

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1100001
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : C

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111111
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0011001
 Received Character : O

[+]No error while transmission of data	 Hamming Code for first 4 bits : 1111000
[+]No error while transmission of data	 Hamming Code for last 4 bits : 1010010
 Received Character : W

[+]No error while transmission of data	 Hamming Code for first 4 bits : 0101101
[+]No error while transmission of data	 Hamming Code for last 4 bits : 0000000
 Received Character : 

[+]Data received successfully.


Wireshark Packet Capture is also attached in the zip.
Total Number of Packets Captured : 170

Thank You.
***********************************************************************************************************