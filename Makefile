# Top level makefile, the real shit is at src/Makefile

TARGET = all

default: $(TARGET)

.DEFAULT:
	cd src && $(MAKE) $@
