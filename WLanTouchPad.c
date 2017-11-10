#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include<arpa/inet.h>
#include<sys/socket.h>

#include <X11/X.h> 
#include <X11/Xlib.h> 
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h> 

#include <X11/keysym.h>
#include <X11/keysymdef.h>

#define BUFLEN 20  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
    
unsigned long KeySymArr [32]= {
	
	/*#define XK_Cyrillic_yu*/                   0x06c0,  /* U+044E CYRILLIC SMALL LETTER YU */
	/*#define XK_Cyrillic_a        */            0x06c1,  /* U+0430 CYRILLIC SMALL LETTER A */
	/*#define XK_Cyrillic_be         */          0x06c2,  /* U+0431 CYRILLIC SMALL LETTER BE */
	/*#define XK_Cyrillic_tse          */       0x06c3,  /* U+0446 CYRILLIC SMALL LETTER TSE */
	/*#define XK_Cyrillic_de   */                0x06c4,  /* U+0434 CYRILLIC SMALL LETTER DE */
	/*#define XK_Cyrillic_ie       */            0x06c5,  /* U+0435 CYRILLIC SMALL LETTER IE */
	/*#define XK_Cyrillic_ef         */          0x06c6,  /* U+0444 CYRILLIC SMALL LETTER EF */
	/*#define XK_Cyrillic_ghe       */           0x06c7,  /* U+0433 CYRILLIC SMALL LETTER GHE */
	/*#define XK_Cyrillic_ha         */          0x06c8,  /* U+0445 CYRILLIC SMALL LETTER HA */
	/*#define XK_Cyrillic_i            */        0x06c9,  /* U+0438 CYRILLIC SMALL LETTER I */
	/*#define XK_Cyrillic_shorti    */           0x06ca,  /* U+0439 CYRILLIC SMALL LETTER SHORT I */
	/*#define XK_Cyrillic_ka         */          0x06cb,  /* U+043A CYRILLIC SMALL LETTER KA */
	/*#define XK_Cyrillic_el          */         0x06cc,  /* U+043B CYRILLIC SMALL LETTER EL */
	/*#define XK_Cyrillic_em        */           0x06cd,  /* U+043C CYRILLIC SMALL LETTER EM */
	/*#define XK_Cyrillic_en          */         0x06ce,  /* U+043D CYRILLIC SMALL LETTER EN */
	/*#define XK_Cyrillic_o           */         0x06cf,  /* U+043E CYRILLIC SMALL LETTER O */
	/*#define XK_Cyrillic_pe        */           0x06d0,  /* U+043F CYRILLIC SMALL LETTER PE */
	/*#define XK_Cyrillic_ya        */           0x06d1,  /* U+044F CYRILLIC SMALL LETTER YA */
	/*#define XK_Cyrillic_er          */         0x06d2,  /* U+0440 CYRILLIC SMALL LETTER ER */
	/*#define XK_Cyrillic_es          */         0x06d3,  /* U+0441 CYRILLIC SMALL LETTER ES */
	/*#define XK_Cyrillic_te            */       0x06d4,  /* U+0442 CYRILLIC SMALL LETTER TE */
	/*#define XK_Cyrillic_u           */         0x06d5,  /* U+0443 CYRILLIC SMALL LETTER U */
	/*#define XK_Cyrillic_zhe        */          0x06d6,  /* U+0436 CYRILLIC SMALL LETTER ZHE */
	/*#define XK_Cyrillic_ve         */          0x06d7,  /* U+0432 CYRILLIC SMALL LETTER VE */
	/*#define XK_Cyrillic_softsign  */           0x06d8,  /* U+044C CYRILLIC SMALL LETTER SOFT SIGN */
	/*#define XK_Cyrillic_yeru        */         0x06d9,  /* U+044B CYRILLIC SMALL LETTER YERU */
	/*#define XK_Cyrillic_ze           */        0x06da,  /* U+0437 CYRILLIC SMALL LETTER ZE */
	/*#define XK_Cyrillic_sha         */         0x06db,  /* U+0448 CYRILLIC SMALL LETTER SHA */
	/*#define XK_Cyrillic_e             */       0x06dc,  /* U+044D CYRILLIC SMALL LETTER E */
	/*#define XK_Cyrillic_shcha      */          0x06dd,  /* U+0449 CYRILLIC SMALL LETTER SHCHA */
	/*#define XK_Cyrillic_che          */        0x06de,  /* U+0447 CYRILLIC SMALL LETTER CHE */
	/*#define XK_Cyrillic_hardsign   */          0x06df  /* U+044A CYRILLIC SMALL LETTER HARD SIGN */	
	
}; 

int Unicode [32] = {
	
	0x044e,
	0x0430,
	0x0431,
	0x0446,
	0x0434,
	0x0435,
	0x0444,
	0x0433,
	0x0445,
	0x0438,
	0x0439,
	0x043a,
	0x043b,
	0x043c,
	0x043d,
	0x043e,
	0x043f,
	0x044f,
	0x0440,
	0x0441,
	0x0442,
	0x0443,
	0x0436,
	0x0432,
	0x044c,
	0x044b,
	0x0437,
	0x0448,
	0x044d,
	0x0449,
	0x0447,
	0x044a
	
};

    
Display *dpy;
Window root_window;   

int number_of_screens;
int i;

Bool result;

Window *root_windows;
Window window_returned;
  
int root_x, root_y;
int win_x, win_y;
unsigned int mask_return;

XEvent event;
  
  
KeySym XUnicodeToKeySym (char buf [5]) {
	
	KeySym code;
	
	int unicode =  (int) strtol (buf, NULL, 16);
	//puts (buf);
	//printf("\nunicode: %d\n", unicode);
	//printf("\nUnicode[32]: %x\n", Unicode [0]);
	
	for (int i = 0; i < 32; i++) {
		
		if (Unicode [i] == unicode) {
			//printf("\nunicode: %d\n", unicode);
			code = KeySymArr [i];
			break;
		}	
		
	}
	
	
	return code;
	
}  

void printChar (Display *display, char c, char *unicode) {

	
     
	//printf ("\n%d\n", c);
	//wprintf (L"\n%c\n", c);	
	
	if (unicode == 0) {
	
		
		//printf("\nchar: %c\n", c);
		
		if (c == ' ') {
			
			KeySym en = XStringToKeysym ("U0020");
			KeyCode code = XKeysymToKeycode(display, en);
			
			XTestFakeKeyEvent (display, code, 1, 0);
			XFlush(display);
			XTestFakeKeyEvent (display, code, 0, 0);
			XFlush(display);	
			
		}
		              
		if (c == '\b') {
			
			KeySym en = 0xff08;
			KeyCode code = XKeysymToKeycode(display, en);
			
			XTestFakeKeyEvent (display, code, 1, 0);
			XFlush(display);
			XTestFakeKeyEvent (display, code, 0, 0);
			XFlush(display);	
			
		}
		
		if (c == '\n') {
			
			KeySym en = 0xff0d;
			KeyCode code = XKeysymToKeycode(display, en);
			
			XTestFakeKeyEvent (display, code, 1, 0);
			XFlush(display);
			XTestFakeKeyEvent (display, code, 0, 0);
			XFlush(display);	
			
		}
		
		char text[1];
		text [0]= c;
		
		KeySym en = XStringToKeysym (text);
		KeyCode code = XKeysymToKeycode(display, en);
		
		XTestFakeKeyEvent (display, code, 1, 0);
		XFlush(display);
		XTestFakeKeyEvent (display, code, 0, 0);
		XFlush(display);	
			
		}

	else {
		
		
		
		KeySym rus = XUnicodeToKeySym (unicode);
		//printf("\nkeysym: %lu\n", rus);
		
		KeyCode code = XKeysymToKeycode(display, rus);
		
		//printf ("\n%d\n", XKeysymToKeycode(display, rus));
		
		XTestFakeKeyEvent (display, code, 1, 0);
		XFlush(display);
		XTestFakeKeyEvent (display, code, 0, 0);
		XFlush(display);	
		      
	}	
	         
}    
       
                                    
void SendClick (Display *display, int button, char click) {
	
	if (click == 'l' || click == 'r') {
		
		XTestFakeMotionEvent (display, -1, root_x, root_y, CurrentTime );
		XTestFakeButtonEvent (display, button, True, CurrentTime); //Mouse down
		XTestFakeButtonEvent (display, button, False, CurrentTime); //Mouse up
		
		XFlush (display);
		
	}

	else if (click == 'd') {
		
		XTestFakeMotionEvent (display, -1, root_x, root_y, CurrentTime );
		XTestFakeButtonEvent (display, button, True, CurrentTime); //Mouse down
		
		XFlush (display);
		
	}

	else if (click == 'u') {
		
		XTestFakeMotionEvent (display, -1, root_x, root_y, CurrentTime );
		XTestFakeButtonEvent (display, button, False, CurrentTime); //Mouse up
		
		XFlush (display);
		
	}	

}    
    
void MoveCursor (long x, long y, long oldx, long oldy) {
	
	number_of_screens = XScreenCount(dpy);
	root_windows = malloc(sizeof(Window) * number_of_screens);
	
	for (i = 0; i < number_of_screens; i++) 
		root_windows[i] = XRootWindow(dpy, i);
	
	for (i = 0; i < number_of_screens; i++) {
		
		result = XQueryPointer(dpy, root_windows[i], &window_returned, &window_returned, &root_x, &root_y, &win_x, &win_y, &mask_return);
		
		if (result == True) 
		    break;
		
	}
	  
	//printf("Mouse is at (%d,%d)\n", root_x, root_y);

	    	
	if (x > oldx) 
		root_x += (int)x - (int)oldx;
		
	if (x < oldx) 
		root_x -= (int)oldx - (int)x;

	if (y > oldy) 
		root_y += (int)y - (int)oldy;

	if (y < oldy) 
		root_y -= (int)oldy - (int)y;
	
	
	XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, root_x, root_y);
	XFlush(dpy);	
	
}

void die(char *s) {
	
    perror(s);
    exit(1);
	
}
        
int main() {
	
	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	
	int server_socket;
	struct sockaddr_in server, client;
	int slen , recv_len;
	char buf [BUFLEN];
	char *ptr;
	long x, y;
	long oldx, oldy;
	long dx, dy;
	
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
	printf("\nInitialising socket...");
	
     
	//Create a socket
	if ((server_socket = socket (AF_INET , SOCK_DGRAM , 0 )) == -1) 
		die ("socket error");
	
    
	printf("Socket created.\n");
     
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons (PORT);
     
	//Bind
	if (bind (server_socket ,(struct sockaddr *)&server , sizeof(server)) == -1) 
		die ("bind failed");
	
	puts("Bind done");
	
	//keep listening for data
	while(1) {
		
		
		
		//printf("Waiting for data...");
		fflush(stdout);
		 
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		 
		//try to receive some data, this is a blocking call
		if ((recvfrom (server_socket, buf, BUFLEN, 0, (struct sockaddr *) &client, &slen)) == -1) 
			die ("not received");
		
			
		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa (client.sin_addr), ntohs (client.sin_port));
		//printf("Data: %s\n" , buf);
		
		if (buf [0] == 'l') {
			//printf ("\nleftclick\n");
			SendClick (dpy, Button1, 'l');
			continue;
			
		}	
		
		else if (buf [0] == 'r') {
			//printf ("\nrightclick\n");
			SendClick (dpy, Button3, 'r');
			continue;
			
		}
		
		else if (buf [0] == 'd') {
		//	printf ("\nrightclick\n");
			SendClick (dpy, Button1, 'd');
			continue;
			
		}
		
		else if (buf [0] == 'u') {
			//printf ("\nrightclick\n");
			SendClick (dpy, Button3, 'u');
			continue;
			
		}
		
		else if (buf [0] == 'm') {
			
			if (buf [2] == '0') {
				
				//int rus;
				
				
				token = strtok(buf, search);
				token = strtok(NULL, search);
				//rus =  strtol (token, NULL, 16);
					
				
				printChar (dpy, 0, token);
			}

			else {
				//printf ("\nen\n");
				printChar (dpy, buf [1], 0);
			
			}
			
			continue;
			
		}
		
		else if (buf [0] == 'b') {
			//printf ("\nbackspace\n");
			printChar (dpy, '\b', 0);
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
		
	
		
		MoveCursor (x, y, oldx, oldy);
		
		
		
		
		
		
		
		

		
		
		
		
		/*	
		//now reply the client with the same data
		if (sendto (server_socket, " ", 1, 0, (struct sockaddr*) &client, slen) == SOCKET_ERROR) {
			
		    printf("sendto() failed with error code : %d" , WSAGetLastError());
		    exit(EXIT_FAILURE);
			
		}
		*/
	}	
		
     
    return 0;
	
}