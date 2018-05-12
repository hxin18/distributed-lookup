objects = client monitor aws servera serverb serverc
all: client.cpp monitor.cpp aws.cpp aws.h servera.h servera.cpp serverb.h serverb.cpp serverc.h serverc.cpp
	g++ -o client client.cpp  -lnsl -lresolv
	g++ -o monitor monitor.cpp  -lnsl -lresolv
	g++ -o aws aws.cpp  -lnsl -lresolv
	g++ -o servera servera.cpp  -lnsl -lresolv
	g++ -o serverb serverb.cpp  -lnsl -lresolv
	g++ -o serverc serverc.cpp  -lnsl -lresolv
.PHONY: monitor aws servera serverb serverc		
monitor: 
	./monitor

aws:
	./aws

servera: 
	./servera

serverb: 
	./serverb

serverc:
	./serverc

clean:
	-rm $(objects)
