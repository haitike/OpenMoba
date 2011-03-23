// Listado: servidor.cpp
//
// Servidor TCP usando SDL_net

#include <iostream>
#include <SDL/SDL.h>

#include <SDL/SDL_net.h>

using namespace std;

int main() {

    // Inicializamos SDL_net

    if(SDLNet_Init() < 0)  {
	
	cerr << "SDL_Init: " << SDLNet_GetError();
	exit(1);
    
    }

    atexit(SDLNet_Quit);

    // Modo servidor

    IPaddress ip;

    // Configuramos el servidor para escuchar el puerto 2000

    if(SDLNet_ResolveHost(&ip, NULL, 2000) < 0) {
	
	cerr << "SDLNet_ResolveHost(): " << SDLNet_GetError();
	exit(1);

    }

    // Abrimos una conexión
    
    TCPsocket socket;

    socket = SDLNet_TCP_Open(&ip);

    if(!socket) {

	cerr << "SDLNet_TCP_Open(): " << SDLNet_GetError();
	exit(1);
    }


    cout << "Servidor activo" << endl;

    // Bucle de control de la conexión

    bool salir = false;
    TCPsocket socket_cliente;

    while(salir == false) {
	
	// ¿Tenemos una conexión pendiente?
	// La aceptamos
	
	if((socket_cliente = SDLNet_TCP_Accept(socket))) {

	    // Ahora realizamos la comunicación con el cliente

	    IPaddress *ip_remota;

	    // Mostramos la información

	    if((ip_remota = SDLNet_TCP_GetPeerAddress(socket_cliente))) 

		cout << "Cliente conectado "
		     << SDLNet_Read32(&ip_remota->host)
		     << " : " 
		     << SDLNet_Read16(&ip_remota->port) << endl;
		
	    else

		cerr << "SDLNet_TCP_GetPeerAddress(): " << SDLNet_GetError() << endl;


	    // Mostramos lo que envía el cliente

	    bool terminar = false;
	    char buffer[512];

	    while(terminar == false) {

		// Leemos de la conexión

		if (SDLNet_TCP_Recv(socket_cliente, buffer, 512) > 0) {
		    
		    cout << "Cliente dice: " << buffer << endl;;

		    // Si da orden de salir, cerramos
 
		    if(strcmp(buffer, "exit\n") == 0) {
			
			terminar = true;
			cout << "Desconectando" << endl;
		    
		    }
		    
		    if(strcmp(buffer, "quit\n") == 0) {
			
			terminar = true;
			salir = true;
			cout << "Server Down" << endl;
		    }
		}
	    }

	    // Cierro el socket
	    
	    SDLNet_TCP_Close(socket_cliente);
	}

    }
    
    SDLNet_TCP_Close(socket);
    
    return 0;
}
