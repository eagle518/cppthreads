AUTOMAKE_OPTIONS = foreign
lib_LTLIBRARIES = libcppthreads.la
LDADD = -lpthread -lrt
#AM_CPPFLAGS=-I$(srcdir)/../include
libcppthreads_la_CPPFLAGS = -fPIC -D_REENTRANT -I$(srcdir)/../include
libcppthreads_la_CFLAGS = -fPIC -D_REENTRANT -I$(srcdir)/../include
libcppthreads_la_SOURCES = \
ArrayBlockingQueue.cpp\
LinkedBlockingQueue.cpp\
Mutex.cpp\
Semaphore.cpp\
SynchronousQueue.cpp

# include sources in include
#AM_CPPFLAGS = -I$(srcdir)/../include -D_REENTRANT
# Output programs "i.e executables"
#bin_PROGRAMS = main
# Source files of main
#main_SOURCES = Main.cpp Semaphore.cpp
