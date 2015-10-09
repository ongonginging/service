bin_PROGRAMS = client 
client_SOURCES = main.cpp
DEFS = -DBOOST_LOG_DYN_LINK -DDEBUG
CPPFLAGS =
CXXFLAGS =
AM_CPPFLAGS =
AM_CXXFLAGS =
AM_LDFLAGS =
client_LINK = $(CXX) -o $@ 
client$(EXEEXT): $(client_OBJECTS) $(client_DEPENDENCIES) $(EXTRA_client_DEPENDENCIES) 
	@rm -f client$(EXEEXT)
	$(AM_V_CXXLD)$(client_LINK) $(client_OBJECTS) $(client_LDADD) $(LIBS) $(AM_CXXFLAGS) $(CXXFLAGS) $(client_LDFLAGS) $(LDFLAGS) 
client_CPPFLAGS = -std=c++11 -gdwarf-2 -Werror -O0
client_LDFLAGS = -L/usr/lib/x86_64-linux-gnu -I/usr/include -levent -lboost_date_time

