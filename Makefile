# Top level makefile, the real shit is at src/Makefile

TARGET = libgeneralmetricsframework.so

default: $(TARGET)

.DEFAULT:
	cd src && $(MAKE) $@
