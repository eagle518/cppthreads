AUTOMAKE_OPTIONS = foreign
LDADD = -L$(libdir) -lpthread -lgtest -lcppthreads
AM_CPPFLAGS = -fPIC -D_REENTRANT -I$(srcdir)/../include
AM_CFLAGS = -fPIC -D_REENTRANT -I$(srcdir)/../include
bin_PROGRAMS = runner
runner_SOURCES = \
runner.cpp\
SemaphoreTest.cpp

# include sources in include
#AM_CPPFLAGS = -I$(srcdir)/../include -D_REENTRANT
# Output programs "i.e executables"
# Source files of main
#main_SOURCES = Main.cpp Semaphore.cpp
