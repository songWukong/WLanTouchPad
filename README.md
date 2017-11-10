# WLanTouchPad
Control your win/linux desktop PC via smartphone

WlanTouchPad is a client/server software which allows to control mouse movement and keyboard input on the desctop PC's. It implements very simple connection via UDP protocol. The server side is written in c (basic code for UDP server was taken from the public domain tutorial and then modified by me) and the client is an android app. There are many ugly places(e.g. it creates new upd session in client each time when data is sent, I know this is very bad, but I don't know how to handle it - I've used the simpliest AsynkTask class instead of creating new thread) around the code, but I've made it for my own. It works and that's fantastic. I personally use it almost every day. Windows server part is pretty trivial and the Linux one has one interesting function which converts unicode to keysym (see the reference to keysym function) - it allows to write russian chars in keyboard input mode which is useful while googling remotely))

PLEASE FEEL FREE TO CONTACT ME VIA EMAIL rozovenkoe66@gmail.com IF YOU HAVE ISSUES WITH COMPILING THE CODE OR ANY QUESTIONS
