
#include <iostream>
#include <pthread.h>
#include <queue>

/* listen task
 * */
struct listen_task_args_t{
    int listen_fd;
};

void* listen_task(void*){
}

/* protocol task
 * */
struct protocol_task_args_t{
    std::queue<int> eq;
};

void* protocol_task(void*){
}

/* service task
 * */
class protocol_t{
    int length;
    std::string data;
};

struct service_task_args_t{
    std::queue<protocol_t> eq;
};

void* service_task(void*){
}

/*  main thread
 * */
int main(int argc, char* argv[]){
    int rv = 0;
    return rv;
}
