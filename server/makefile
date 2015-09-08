
TARGET=service
ROOT_DIR=$(shell pwd)
CPPFLAGS=-std=c++11 -gdwarf-2 -DNO_FCGI_DEFINES -DBOOST_LOG_DYN_LINK  -Werror -O0 -DDEBUG #-pg 

DEP_LIBS=-lpthread\
	-lhiredis\
	-ljson-c\
	-levent\
	-lboost_regex\
	-lboost_system\
	-lboost_filesystem\
	-lboost_log\
	-lboost_thread\
	-lboost_log_setup\
	-L/usr/lib\
	-L/usr/local/lib\

DEP_INCS=-I.\
	-I/usr/include\
	-I/usr/include/hiredis\
	-I/usr/local/include\
	-I/usr/local/include/boost\
	-I/usr/local/include/hiredis\
	-I/usr/local/include/json-c\
	-I/usr/local/include\

DIRS=$(shell find . -maxdepth 3 -type d)
FILES=$(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS=$(patsubst %.cpp,%.o, $(FILES))
GCHS=$(patsubst %.cpp,%.o.gch, $(FILES))
HPPS=$(foreach dir,$(DIRS),$(wildcard $(dir)/*.hpp))

VPATH = .
.cpp.o: 
	$(CXX) -c $(CPPFLAGS) $< -o $@ $(DEP_LIBS) $(DEP_INCS) 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX)  -o $@ $(OBJS) $(CPPFLAGS) $(DEP_LIBS) $(DEP_INCS)

clean:
	rm -rf $(TARGET) $(OBJS) $(GCHS) nohup.out
