/*Name : Chandrawanshi Mangesh Shivaji
Roll No. : 1801CS16
CS359 Assignment 2 
fileName : README.txt
*/ 

Complilation details for both server.c and client.c along with example

Example 1 : For file ex.txt

$ gcc server.c -o server
$ ./server

file descriptor 3 received

Successfully binded!

Waiting for file name...

File Name Received: ex.txt

File Successfully opened!
Word Requested by Client -- WORD0
Word Requested by Client -- WORD1
Word Requested by Client -- WORD2
Word Requested by Client -- WORD3
Word Requested by Client -- WORD4
Word Requested by Client -- WORD5


$ gcc client.c -o client
$ ./client

file descriptor 3 received

Please enter file name to receive:
ex.txt

---------Data Received---------
HELLO
CAT DOG
TIGER
LION
HORSE ZEBRA COW
END

-------------------------------


$ cat client_file.txt 
CAT DOG
TIGER
LION
HORSE ZEBRA COW


Example 2 : For filename which is not found   

$ ./server

file descriptor 3 received

Successfully binded!

Waiting for file name...

File Name Received: abc.txt

File open failed!


$ ./client

file descriptor 3 received

Please enter file name to receive:
abc.txt

---------Data Received---------
NOTFOUND
-------------------------------
