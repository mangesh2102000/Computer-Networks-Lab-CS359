/* Name: Chandrawanshi Mangesh Shivaji 
Roll Number : 1801cs16
CS359 Assignment 4 
filename : README.txt
*/

Please keep all the files in same directory before compilation as well as while usage

---ALL USERS INFO----(format: name ip port)
mangesh 127.0.0.1 6032
abhijeet 127.0.0.1 5016
anirban 127.0.0.1 7048
pranay 127.0.0.1 9054
devanshu 127.0.0.1 8024
---------------------

// Compilation details
$ gcc -o p2pchat p2pchat.c
$ ./p2pchat <port_num>

; where port_num can be any one of above user's port (6032 5016 7048 9054 8024)

// Two runtime images are attached

Instance_1.png : Initially when all the users are online
Instance_2.png : Some messages are transferred and all users exit. 
(In case user has exited and some other user is trying to chat with him/her; appropriate message is printed on the stdout)

// Thank You.