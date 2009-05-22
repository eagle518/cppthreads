AUTOMAKE_OPTIONS = foreign
lib_LTLIBRARIES = libcppthreads.la
libcppthreads_la_LIBADD = -lpthread -lrt
#AM_CPPFLAGS=-I$(srcdir)/../include
libcppthreads_la_CPPFLAGS = -ggdb3 -fPIC -D_REENTRANT -I$(srcdir)/../include
libcppthreads_la_CFLAGS = -ggdb3 -fPIC -D_REENTRANT -I$(srcdir)/../include
libcppthreads_la_SOURCES = \
LinkedBlockingQueue.cpp\
Mutex.cpp\
Semaphore.cpp\
SynchronousQueue.cpp\
Thread.cpp\
SuperObject.cpp

include_HEADERS = \
$(top_srcdir)/include/LinkedBlockingQueue.h\
$(top_srcdir)/include/Mutex.h\
$(top_srcdir)/include/Semaphore.h\
$(top_srcdir)/include/SynchronousQueue.h\
$(top_srcdir)/include/Thread.h\
$(top_srcdir)/include/Runnable.h\
$(top_srcdir)/include/SuperObject.h\
$(top_srcdir)/include/InterruptedException.h\
$(top_srcdir)/include/InvalidMutex.h\
$(top_srcdir)/include/InvalidSemaphore.h\
$(top_srcdir)/include/OutOfSpaceException.h\
$(top_srcdir)/include/ThreadingException.h

# include sources in include
#AM_CPPFLAGS = -I$(srcdir)/../include -D_REENTRANT
# Output programs "i.e executables"
#bin_PROGRAMS = main
# Source files of main
#main_SOURCES = Main.cpp Semaphore.cpp
