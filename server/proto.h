
#include "iproto.h"
#include <iostream>

class Header{
    private:
	int length;
    public:
	int& read_length(void);
	void write_length(const int& length);
};

class Body{
    private:
	std::string data;
    public:
	std::string& read_data(void);
	void write_data(const std::string& data);
};

class Protocol:public IProtocol{
    private:
	Header header;
	Body body;
    public:
	bool write(const char*& output_buffer);
	bool read(const int& length, const char*& input_buffer);
};

