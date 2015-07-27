
class IProtocol{
    public:
	virtual bool write(const char*& output_buffer) = 0;
	virtual bool read(const int& length, const char*& input_buffer) = 0;
};

