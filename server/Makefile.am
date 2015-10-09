bin_PROGRAMS = server
server_SOURCES = Buffer.cpp Configure.hpp Event.hpp Listener.cpp main.cpp Protocol.cpp ProtoEventHandler.hpp ServiceEventHandler.cpp Buffer.hpp Connection.cpp Heartbeat.cpp Listener.hpp Protocol.hpp ServerSocket.cpp ServiceEventHandler.hpp ClientSocket.cpp Connection.hpp Heartbeat.hpp ListenEventHandler.cpp ProtoEngine.cpp ServerSocket.hpp SignalHandler.cpp ClientSocket.hpp Dispatcher.cpp IProtocol.hpp ListenEventHandler.hpp Manager.cpp ProtoEngine.hpp ServiceEngine.cpp SignalHandler.hpp Configure.cpp Dispatcher.hpp ITask.hpp Log.hpp Manager.hpp ProtoEventHandler.cpp ServiceEngine.hpp
DEFS = -DBOOST_LOG_DYN_LINK -DDEBUG
CPPFLAGS =
CXXFLAGS =
AM_CPPFLAGS =
AM_CXXFLAGS =
AM_LDFLAGS =
server_LINK = $(CXX) -o $@ 
server$(EXEEXT): $(server_OBJECTS) $(server_DEPENDENCIES) $(EXTRA_server_DEPENDENCIES) 
	@rm -f server$(EXEEXT)
	$(AM_V_CXXLD)$(server_LINK) $(server_OBJECTS) $(server_LDADD) $(LIBS) $(AM_CXXFLAGS) $(CXXFLAGS) $(server_LDFLAGS) $(LDFLAGS) 
server_CPPFLAGS = -std=c++11 -gdwarf-2 -Werror -O0
server_LDFLAGS = -L/usr/lib/x86_64-linux-gnu -I/usr/include -levent -lboost_date_time

