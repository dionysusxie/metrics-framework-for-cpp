TARGET = test

OBJECT_FILES = Updater.o MetricsContext.o MetricsRecord.o BasicItem.o MetricTag.o \
	AbstractMetric.o MetricsSystem.o MetricsSource.o MetricsSink.o \
	test.o

LIB_DIR = /usr/local/lib

CXXFLAGS = -Wall -c -g -fpic

LDFLAGS = -L$(LIB_DIR) 
LDFLAGS += -lboost_thread -lboost_filesystem -lboost_system
LDFLAGS += -Wl,-E

CC = g++

.PHONY: clean

$(TARGET): $(OBJECT_FILES)
	$(CC) -o $(TARGET) $(OBJECT_FILES) $(LDFLAGS)
	@echo "Build successfully!"

%.o : %.c
	$(CC) $(CXXFLAGS) $*.c -o $*.o
	$(CC) $(CXXFLAGS) -MM $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.o : %.cpp
	$(CC) $(CXXFLAGS) $*.cpp -o $*.o
	$(CC) $(CXXFLAGS) -MM $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

-include $(OBJECT_FILES:.o=.d)

clean:
	rm -rf $(TARGET) *.o *.d
