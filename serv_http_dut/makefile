#Makefile de serv_http :

all : http

http : outils_snmp.o outils_html.o serv_http.o snmputils.32.o
	gcc -o serv_http outils_snmp.o outils_html.o serv_http.o snmputils.32.o

outils_snmp.o : outils_snmp.c
	gcc -c outils_snmp.c

outils_html.o : outils_html.c
	gcc -c outils_html.c

serv_http.o : serv_http.c
	gcc -c serv_http.c