#include<iostream>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>

using namespace std;

int main()
{
	char a;
	int fd;
	int PORT = 1500;
	int bufsize = 1024;
	char* buffer = new char (bufsize);
	bool salir = false;
	char* ip = "127.0.0.1";

	struct sockaddr_in server;
	
	fd = socket(AF_INET,SOCK_STREAM,0);
		
	if(fd <0)
	{
		cout<<"Error Al Crear Socket..."<<endl;
		exit(1);
	}
	
	cout<<"Socket Creado"<<endl;
	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	inet_pton(AF_INET,ip, &server.sin_addr);  
	
	if (connect(fd,(struct sockaddr *)&server, sizeof(server))==0)
		{
			cout<<"Conexion Con Servidor"<<inet_ntoa(server.sin_addr)<<endl;
		}
		
	cout<<"Esperando configuracion del servidor"<<endl;
	recv(fd,buffer,bufsize,0);

	cout<<"Respuesta Recibida: "<<buffer;
	cout<<"\nRecuerde utilizar * para mandar mensaje \n Escriba # para finalizar conexion"<<endl;
	
	do{
		cout<<"Escribir un mensaje: ";
		do{
			cin>>buffer;
			send(fd,buffer,bufsize,0);
				
				if(*buffer=='#')
				{
	 				send(fd,buffer,bufsize,0);
					*buffer = '*';
					salir = true;
				}
            }while(*buffer != 42);
            
            cout<<"Mensaje Recibido: ";
            
            do{
				recv(fd,buffer,bufsize,0);
				cout<<buffer<<" ";
					if(*buffer == '#')
					{
						*buffer = '*';
						salir = true;
					}
				}while(*buffer != 42);
				
			cout<<endl;
		}while(!salir);
	cout<<"CONEXION TERMINADA \n\n";
	close(fd);
	return 0;
}
 
