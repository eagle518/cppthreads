AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS = -ggdb3 -O0 -fPIC -D_REENTRANT -I$(srcdir)/../include
AM_CFLAGS = -ggdb3 -fPIC -D_REENTRANT -I$(srcdir)/../include
check_PROGRAMS = runner
noinst_PROGRAMS = runner
runner_SOURCES = \
runner.cpp\
SemaphoreTest.cpp\
MutexTest.cpp\
LinkedBlockingQueueTest.cpp
runner_DEPENDENCIES = ../src
runner_LDADD = $(top_srcdir)/src/libcppthreads.la -lgtest -lpthread -lrt 
runner_LDFLAGS = -all-static 

TESTS = $(check_PROGRAMS)

# include sources in include
#AM_CPPFLAGS = -I$(srcdir)/../include -D_REENTRANT
# Output programs "i.e executables"
# Source files of main
#main_SOURCES = Main.cpp Semaphore.cpp
