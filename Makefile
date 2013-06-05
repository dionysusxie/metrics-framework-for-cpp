# Top level makefile, the real shit is at src/Makefile

TARGET = test

default: $(TARGET)

.DEFAULT:
	cd src && $(MAKE) $@
