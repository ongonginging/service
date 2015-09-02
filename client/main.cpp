
#include<iostream>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<arpa/inet.h>

#include<event.h>

static unsigned char readBuffer[65535];
static unsigned char writeBuffer[65535];

void cb(evutil_socket_t fd, short event, void* arg){
    std::cout<<"in client callback fn."<<std::endl;
}

int main(int arc, char* argv[]){
    int rv = 0;
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        std::cout<<__func__<<" created client socket failed. errno = "<<errno<<std::endl;
        return -1;
    }else{
        std::cout<<__func__<<" successful created client socket "<<fd<<std::endl;
    }
    /*
    int result = fcntl(fd, F_SETFL, O_NONBLOCK|fcntl(fd, F_GETFL));
    if (result == -1){
        std::cout<<__func__<<" set nonblocking to client socket "<<fd<<" failed. errno = "<<errno<<std::endl;
        rv = -1;
    }
    */
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;                 
    addr.sin_port = htons(9544);          
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    int ret = connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if (ret == -1){
        std::cout<<__func__<<" connect server failed. errno = "<<errno<<std::endl;
        rv = -1;
    }
    ret = read(fd, readBuffer, sizeof(readBuffer));
    if (ret == -1){
        std::cout<<__func__<<" read -1. errno = "<<errno<<std::endl;
    }
    close(fd);
    //struct event_base* base = event_base_new();
    //struct event* ev;
    //ev = event_new(base, fd, EV_READ|EV_PERSIST, cb, NULL);
    //event_add(ev, NULL);
    //event_base_dispatch(base);
    //event_free(ev);
    //event_base_free(base);
    //base = NULL;
    //ev = NULL;
    return rv;
}
