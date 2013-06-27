TARGET = sample
TARGET_FOR_UNIT_TEST = unit-test

NON_MAIN_OBJECT_FILES = MetricsContext.o MetricsRecord.o BasicItem.o MetricTag.o conf.o \
	MetricSnapshot.o MetricsSystem.o MetricsSource.o MetricsSink.o gmf_common.o \
	Number.o MutableMetric.o

OBJECT_FILES = $(NON_MAIN_OBJECT_FILES) sample.o

OBJECT_FILES_FOR_UNIT_TEST = UnitTest.o Number_unittest.o

LIB_DIR = /usr/local/lib

CXXFLAGS = -Wall -c -g

LDFLAGS = -L$(LIB_DIR)
LDFLAGS += -lboost_thread -lboost_filesystem -lboost_system -lallyes-log
LDFLAGS += -Wl,-E

GTEST_LIBS = -lgtest

CC = g++

.PHONY: clean test

all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) -o $(TARGET) $(OBJECT_FILES) $(LDFLAGS)
	@echo "Build successfully!"

test: $(TARGET_FOR_UNIT_TEST)
	@echo "\nRun unit test now ..."
	./$(TARGET_FOR_UNIT_TEST)

$(TARGET_FOR_UNIT_TEST): $(NON_MAIN_OBJECT_FILES) $(OBJECT_FILES_FOR_UNIT_TEST)
	@echo "This test works right on gtest-1.6.0."
	$(CC) -o $@ $^ $(LDFLAGS) $(GTEST_LIBS)
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
	rm -rf $(TARGET_FOR_UNIT_TEST)
