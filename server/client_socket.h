
#include<unistd.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>

class ClientSocket{
    private:
        int fd;
        bool reopen;
        bool nonblocking;
    public:
        ClientSocket(void);
        ClientSocket(bool reopen, bool nonblocking);
        ClientSocket(int fd);
        ~ClientSocket(void);
        virtual int open(void);
        virtual int close(void);
        virtual int read(const char* input_buffer);
        virtual int write(const char* outup_buffer);
};
