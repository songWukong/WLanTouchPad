#include "stdio.h"
#include "string.h"
#include "winsock2.h"
#include "locale.h"
#include "windows.h"


#define BUFLEN 20  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
    
    
void printChar (char c, int unicode) {

	//wprintf(L"%ls\n", L"erttté");
	
		
     
	//printf ("\n%d\n", c);
	//wprintf (L"\n%c\n", c);	
	
	if (unicode == 0) {
	
		//printf ("\nenglish symbol: %c\n", c);
		/*INPUT input;
		HKL kbl = GetKeyboardLayout(0);
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = MapVirtualKey (VkKeyScanEx (c ,kbl), MAPVK_VK_TO_VSC);
		input.ki.time = 0;
		input.ki.dwExtraInfo = 0;
		input.ki.wVk = VkKeyScanEx (c ,kbl);
		input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
		SendInput(1, &input, sizeof(INPUT));

		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));*/
		
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = c;
		 input.ki.time = 0;
		 input.ki.dwExtraInfo = 0;
		 input.ki.wVk = 0;
		 input.ki.dwFlags = KEYEVENTF_UNICODE;
		SendInput(1, &input, sizeof(INPUT));
		
	}

	else {
		
		//printf ("\nrussian symbol: %x\n", unicode);
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = unicode;
		 input.ki.time = 0;
		 input.ki.dwExtraInfo = 0;
		 input.ki.wVk = 0;
		 input.ki.dwFlags = KEYEVENTF_UNICODE;
		 SendInput(1, &input, sizeof(INPUT));
		
	}	
	
}    
    
void SendClick (long dX, long dY, char click) {

	int *n = 0;
	
	if (click == 'l') {

	        mouse_event (MOUSEEVENTF_LEFTDOWN, dX, dY, 0, GetMessageExtraInfo());
		mouse_event (MOUSEEVENTF_LEFTUP, dX, dY, 0, GetMessageExtraInfo());

	}

	else if (click == 'r') {
		
	        mouse_event (MOUSEEVENTF_RIGHTDOWN, dX, dY, 0, GetMessageExtraInfo());
	        mouse_event (MOUSEEVENTF_RIGHTUP, dX, dY, 0, GetMessageExtraInfo());

	}
	
	else if (click == 'd') {
		
	        mouse_event (MOUSEEVENTF_LEFTDOWN, dX, dY, 0, GetMessageExtraInfo());
	     //   mouse_event (MOUSEEVENTF_RIGHTUP, dX, dY, 0, GetMessageExtraInfo());

	}
	
	else if (click == 'u') {
		
	      //  mouse_event (MOUSEEVENTF_RIGHTDOWN, dX, dY, 0, GetMessageExtraInfo());
	        mouse_event (MOUSEEVENTF_LEFTUP, dX, dY, 0, GetMessageExtraInfo());

	}

}    
    
void MoveCursorWithKeyboard (long x, long y, long oldx, long oldy) {
	
	POINT p;
	
	GetCursorPos (&p);
		
	if (x > oldx) 
		p.x += x - oldx;
		
	if (x < oldx) 
		p.x -= oldx - x;

	if (y > oldy) 
		p.y += y - oldy;

	if (y < oldy) 
		p.y -= oldy - y;
		
			
	SetCursorPos (p.x, p.y);
	
		
}
    
    
int main() {
	
	
	SOCKET server_socket;
	struct sockaddr_in server, client;
	int slen , recv_len;
	char buf [BUFLEN];
	WSADATA wsa;
	char *ptr;
	long x, y;
	long oldx, oldy;
	long dx, dy;
	POINT p;
	
	char *token;
	char *search = " ";
	
	/*while (1) {
		
		GetCursorPos (&p);
		oldx = p.x;
		oldy = p.y;
		
		GetCursorPos (&p);
		
		if (p.x != oldx || p.y != oldy) {
		printf ("\np.x: %ld\n", p.x);
		printf ("\np.y: %ld\n", p.y);
			
			if ((p.x - oldx) > 0)
				printf ("right");
			if ((p.x - oldx) < 0)
				printf ("left");
			if ((p.y - oldy) > 0)
				printf ("down");
			if ((p.y - oldy) < 0)
				printf ("up");
		}
	}*/
	
	slen = sizeof (client) ;
	     
	//Initialise winsock
	//printf("\nInitialising Winsock...");
	
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
	    
		printf ("Failed. Error Code : %d",WSAGetLastError());
		exit (EXIT_FAILURE);
	    
	}
    
	//printf("Initialised.\n");
     
	//Create a socket
	if ((server_socket = socket (AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET) 
		printf("Could not create socket : %d" , WSAGetLastError());
	
    
	//printf("Socket created.\n");
     
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons (PORT);
     
	//Bind
	if (bind (server_socket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR) {

		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);

	}
	
	//puts("Bind done");
	
	//keep listening for data
	while(1) {
		
		
		
		//printf("Waiting for data...");
		fflush(stdout);
		 
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		 
		//try to receive some data, this is a blocking call
		if ((recvfrom (server_socket, buf, BUFLEN, 0, (struct sockaddr *) &client, &slen)) == SOCKET_ERROR) {
		    
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
			
		}
		
			
		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa (client.sin_addr), ntohs (client.sin_port));
		//printf("Data: %s\n" , buf);
		//printf("russian char: %c%c\n" , buf [1], buf [2]);
		
		
		if (buf [0] == 'l') {
			//printf ("\nleftclick\n");
			GetCursorPos (&p);
			SendClick (p.x, p.y, 'l');
			continue;
			
		}	
		
		else if (buf [0] == 'r') {
			//printf ("\n\n");
			GetCursorPos (&p);
			SendClick (p.x, p.y, 'r');
			continue;
			
		}
		
		else if (buf [0] == 'd') {
			//printf ("\nrightclick\n");
			GetCursorPos (&p);
			SendClick (p.x, p.y, 'd');
			continue;
			
		}
		
		else if (buf [0] == 'u') {
			//printf ("\nup\n");
			GetCursorPos (&p);
			SendClick (p.x, p.y, 'u');
			continue;
			
		}
		
		else if (buf [0] == 'm') {
			
			if (buf [2] == '0') {
				
				int rus;
	
				token = strtok(buf, search);
				token = strtok(NULL, search);
				rus =  (int)strtol (token, NULL, 16);

				printChar (' ', rus);
				//printf ("\nru: %X\n", rus);
				
			}

			else {
				//printf ("\nen\n");
				printChar (buf [1], 0);
			
			}
			
			continue;
			
		}
		
		else if (buf [0] == 'b') {
			//printf ("\nbackspace\n");
			printChar ('\b', 0);
			continue;
			
		}
		
		token = strtok(buf, search);
		//printf("x: %s\n" , token);
		x = strtol (token, &ptr, 10);
		//printf ("\nx: %ld\n", x);

		
		token = strtok(NULL, search);
		//printf("y: %s\n" , token);
		y = strtol (token, &ptr, 10);
		//printf ("\ny: %ld\n", y);
		
		token = strtok(NULL, search);
		//printf("y: %s\n" , token);
		oldx = strtol (token, &ptr, 10);
		//printf ("\noldx: %ld\n", oldx);
		
		token = strtok(NULL, search);
		//printf("y: %s\n" , token);
		oldy = strtol (token, &ptr, 10);
		//printf ("\noldy: %ld\n", oldy);
		
	
		
		MoveCursorWithKeyboard (x, y, oldx, oldy);
		
		
		
		
		
		
		
		

		
		
		
		
		/*	
		//now reply the client with the same data
		if (sendto (server_socket, " ", 1, 0, (struct sockaddr*) &client, slen) == SOCKET_ERROR) {
			
		    printf("sendto() failed with error code : %d" , WSAGetLastError());
		    exit(EXIT_FAILURE);
			
		}
		*/
	}	
		
	
 
	closesocket (server_socket);
	WSACleanup();
     
    return 0;
	
}
