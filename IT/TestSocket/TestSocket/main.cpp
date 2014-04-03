//
//  main.cpp
//  TestSocket
//
//  Created by Дмитрий Богомолов on 28.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>

int SERVER_SOCKET;
int CLIENT_SOCKET;
struct sockaddr_in SERVER_ADDR;
struct sockaddr_in CLIENT_ADDR;
char i_buffer[1024];
socklen_t CLIENT_ADDR_SIZE = sizeof(CLIENT_ADDR);
using namespace std;

int main(int argc, const char * argv[])
{
    bzero(&SERVER_ADDR, sizeof(SERVER_ADDR));
    SERVER_SOCKET = socket(AF_INET, SOCK_STREAM, 0);
    bind(SERVER_SOCKET, (struct sockaddr *)&SERVER_ADDR, sizeof(SERVER_ADDR));
    listen(SERVER_SOCKET, SERVER_MAX_CONN);
    
    for(;;)
    {
        CLIENT_SOCKET = accept(SERVER_SOCKET, (struct sockaddr *)&CLIENT_ADDR, &CLIENT_ADDR_SIZE);
        
        if(fork() == 0)
        {
            for(;;)
            {
                if(recv(CLIENT_SOCKET, &i_buffer, sizeof(i_buffer), 0) == 0) return 0;
                send(CLIENT_SOCKET, i_buffer, sizeof(i_buffer), 0);
            }
        }
        
        close (CLIENT_SOCKET);
    }
    
    close (SERVER_SOCKET);
    return 0;
}