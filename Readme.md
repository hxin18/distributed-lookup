
What have I done in this project:
	I have finished all the requirement as described in the Project requirement, including the seach, prefix and suffix. In Phase 1, aws and three backend servers will up and run, the monitor will be on as well. The client send the function to the aws and aws send it to the backend server to do the information retrival according to the function. In the phase 2, the aws gather the result and send back to client and monitor for display. For the backend servers, I have implemented a kv pair based dictionary to store the dictionary and implement four function respectively for search word, search similar, prefix and suffix.

Files implemented:
	client.cpp: it will get the function name and the query and uses TCP connection send to aws server. It will also display the result after looking up.
	monitor.cpp: it will monitor what data has been sent to the client plus it will print the word with one edit distant.
	aws.h: the header file for aws cpp.
	aws.cpp:    it will get the function name, query and send to three back end server. After getting result from three back server, it will  send the result to client and the monitor. 
	servera.h/serverb.h/serverc.h: header file to define the Dictionary class and implement several method related to the search prefix suffix.
	servera.cpp: After it get data from AWS using UDP, it will make the look up and then send back the result to aws.
	serverb.cpp: After it get data from AWS using UDP, it will make the look up and then send back the result to aws.
	serverc.cpp: After it get data from AWS using UDP, it will make the look up and then send back the result to aws.

How to run the programs:
	1. First you should open six different terminals. "make/make all" to compile all the file. 
	2. Type "make servera" using one terminal to run servera.
	3. Type "make serverb" using one terminal to run serverb.
	4. Type "make serverc" using one terminal to run serverc.
	5. Type "make aws" using one terminal to run AWS. 
	6. Type "make monitor" using one terminal to run monitor. 
	7. typing "./client function query" to run the client. 
		function are in {search prefix suffix}

Example

 1.Search

./client search Hair
The client is up and running.
The client sent < Hair > and < search > to AWS
Found a match for < Hair >:
< "Hair (human or animal) used for various purposes; as  hair for stuffing cushions." >

./servera
The Server A is up and running using UDP on port 21164
The Server A received input <Hair> and operation <search>
The Server A has found < 1 > matches and < 2 > similar words
The Server A finished sending the output to AWS

./serverb
The Server B is up and running using UDP on port 22164
The Server B received input <Hair> and operation <search>
The Server B has found < 0 > matches and < 0 > similar words
The Server B finished sending the output to AWS

./serverc
The Server C is up and running using UDP on port 23164
The Server C received input <Hair> and operation <search>
The Server C has found < 1 > matches and < 1 > similar words
The Server C finished sending the output to AWS

./aws
The AWS is up and running
The AWS received input=<Hair> and function=<search> from the client using TCP over port 25164
The AWS sent < Hair > and < search> to Backend-Server A
The AWS sent < Hair > and < search> to Backend-Server B
The AWS sent < Hair > and < search> to Backend-Server C
The AWS receives <2> similar words from Backend-Server <A> using UDP over port 24164
The AWS receives <0> similar words from Backend-Server <B> using UDP over port 24164
The AWS receives <1> similar words from Backend-Server <C> using UDP over port 24164
The aws sent < 1 > matches to client
The aws sent < Hair > and < Fair > to the monitor via TCP port 26164

./monitor
The monitor is up and running.
Found a match for < Hair >:
< "Hair (human or animal) used for various purposes; as  hair for stuffing cushions." >
One edit distance match is< Fair >
< "A competitive exhibition of wares  farm products  etc.  not primarily for purposes of sale; >

2.Prefix

./client prefix Hai
The client is up and running.
The client sent < Hai > and < prefix > to AWS
Found < 6 > matches for < Hai >:
< Hair >
< Haired >
< Hairpin >
< Hair >
< Hairbrush >
< Hairworm >

./servera 
The Server A received input <Hai> and operation <prefix>
The Server A has found < 2 > matches
The Server A finished sending the output to AWS

./serverb
The Server B received input <Hai> and operation <prefix>
The Server B has found < 1 > matches
The Server B finished sending the output to AWS

./serverc
The Server B received input <Hai> and operation <prefix>
The Server B has found < 1 > matches
The Server B finished sending the output to AWS

./aws
The AWS received input=<Hai> and function=<prefix> from the client using TCP over port 25164
The AWS sent < Hai > and < prefix> to Backend-Server A
The AWS sent < Hai > and < prefix> to Backend-Server B
The AWS sent < Hai > and < prefix> to Backend-Server C
The AWS receives <2> matches from Backend-Server <A> using UDP over port 24164
The AWS receives <1> matches from Backend-Server <B> using UDP over port 24164
The AWS receives <3> matches from Backend-Server <C> using UDP over port 24164
The aws sent < 6 > matches to client
The aws sent < 6 > matches to the monitor via TCP port 26164

./monitor
Found < 6 > match for < Hai >:
< Hair >
< Haired >
< Hairpin >
< Hair >
< Hairbrush >
< Hairworm >

3.Suffix
./client suffix air
The client is up and running.
The client sent < air > and < suffix > to AWS
Found < 5 > matches for < air >:
< Fair >
< Hair >
< Pair >
< Hair >
< Wair >

./servera
The Server A received input <air> and operation <suffix>
The Server A has found < 3 > matches
The Server A finished sending the output to AWS

./serverb
The Server B received input <air> and operation <suffix>
The Server B has found < 0 > matches
The Server B finished sending the output to AWS

./serverc
The Server C received input <air> and operation <suffix>
The Server C has found < 2 > matches
The Server C finished sending the output to AWS

./aws
The AWS is up and running
The AWS received input=<air> and function=<suffix> from the client using TCP over port 25164
The AWS sent < air > and < suffix> to Backend-Server A
The AWS sent < air > and < suffix> to Backend-Server B
The AWS sent < air > and < suffix> to Backend-Server C
The AWS receives <3> matches from Backend-Server <A> using UDP over port 24164
The AWS receives <0> matches from Backend-Server <B> using UDP over port 24164
The AWS receives <2> matches from Backend-Server <C> using UDP over port 24164
The aws sent < 5 > matches to client
The aws sent < 5 > matches to the monitor via TCP port 26164

./monitor
The monitor is up and running.
Found < 5 > match for < air >:
< Fair >
< Hair >
< Pair >
< Hair >
< Wair >

The idiosyncrasy:
	Under my test case, there is no failer. Hoever, to run the project, you must obey the order described in the project desciption. 

Reuse of the code:
    I have referenced API of "Beej's Guide to Network Programming -- Using Internet Sockets" which is a standard way for socker programming
