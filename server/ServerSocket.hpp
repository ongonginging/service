
class ServerSocket{
    private:
        int listenfd;
        bool nonblocking;
    public:
        ServerSocket(void);
        ServerSocket(bool nonblocking);
        ~serverSocket(void);
        virtual int open(void);
        virtual int close(void);
        virtual int serve(void);
};
