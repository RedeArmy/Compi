#include<iostream>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;


int main()
{

	int fd, fd2;
	int bufsize = 1024;
	int PORT = 1500;
	bool salir = false;
	char* buffer = new char (bufsize);
	
	struct sockaddr_in server;
	socklen_t tamano;
	pid_t pld;

		if ((fd=socket(AF_INET, SOCK_STREAM, 0))<0)
			{
				cout<<"Error Al Crear Socket"<<endl;
				exit(1);
			}
			cout<<"Socket Servidor Ha Sido Creado"<<endl;
			
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = htons(INADDR_ANY);
			server.sin_port = htons (PORT);
			
		if (bind(fd,(struct sockaddr*)&server, sizeof(server))<0)
			{
				cout<<"Error En La Conexion Blind"<<endl;
				return (1);
			}

			tamano = sizeof(server);
			cout<<"Conectando con Cliente... \n";
			listen(fd,1);

			while ((fd2 = accept(fd,(struct sockaddr *)&server,&tamano))>0)
				{
					strcpy(buffer, "Servidor Conectado\n");
					send(fd2,buffer,bufsize,0);
					cout<<"Conexion con cliente EXITOSA\n";
					cout<<"Escriba * para enviar mensaje, escriba # para terminar conexion";
					
					cout<<"mensaje recibido: ";
					
			do{
				recv(fd2,buffer,bufsize,0);
				cout<<buffer<<"";
				   
					if(*buffer=='#')
					{
						*buffer='*';
						salir = true;
					}
			} while(*buffer != '*');
			
			do{
				cout<<"\nEscriba mensaje: ";
				do{
					cin>>buffer;
					send(fd2,buffer,bufsize,0);
						if(*buffer == '#')
						{
							send(fd2,buffer,bufsize,0);
							*buffer = '*';
							salir = true;
						}
						}while (*buffer != '*');
						
				}while(!salir);
		cout<<"\n El Servidor Termino La Conexion Con "<<inet_ntoa(server.sin_addr);
		close(fd2);
		cout<<"\n Conectar Nuevo CLiente";
		salir = false;
	}		
close(fd);
return 0;

}


