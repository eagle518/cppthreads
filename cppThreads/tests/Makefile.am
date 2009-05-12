AUTOMAKE_OPTIONS = foreign
LDADD = -L$(srcdir)/../libs -lgtest -lcppthreads -lpthread -lrt 
AM_CPPFLAGS = -ggdb3 -O0 -fPIC -D_REENTRANT -I$(srcdir)/../include
AM_CFLAGS = -ggdb3 -fPIC -D_REENTRANT -I$(srcdir)/../include
bin_PROGRAMS = runner
runner_SOURCES = \
runner.cpp\
SemaphoreTest.cpp\
MutexTest.cpp\
LinkedBlockingQueueTest.cpp

# include sources in include
#AM_CPPFLAGS = -I$(srcdir)/../include -D_REENTRANT
# Output programs "i.e executables"
# Source files of main
#main_SOURCES = Main.cpp Semaphore.cpp
