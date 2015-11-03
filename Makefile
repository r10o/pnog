# Generic Makefile
# See LICENSE file for copyright and license details.
# See README for more information on the program

include config.mk

# CFLAG options
# Compiler debugging enabled
ifeq ($(DEBUG), yes)
	CFLAGS += -Wextra
	CFLAGS += -g
endif

# Pedantic warnings
ifeq ($(PEDANTIC), yes)
	CFLAGS += -Werror
	CFLAGS += -pedantic
	CFLAGS += -pedantic-errors
endif

# Enable optimization
ifeq ($(OPTIMIZE), yes)
	CFLAGS += -O3
endif

# Sets if lib or bin
ifeq ($(TYPE), lib)
	DIR ?= $(LIB_DIR)
else
	DIR ?= $(BIN_DIR)
endif

all: options $(TARGET)

options:
	@echo "$(TARGET) build options:"
	@echo "CFLAGS	= $(CFLAGS)"
	@echo "LIBS	= $(LIBS)"
	@echo "CC	= $(CC)"

%.o: %.c
	@echo -e "\n>> compiling object files <<\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@echo -e "\n>> linking object files into a shared library <<\n"
	$(CC) $(LIBS) $(OBJ) -o $(DIR)/$(OUTPUT)
	@echo -e "\n>> done compiling <<"

clean:
	@echo -e ">> cleaning <<\n"
	@rm -rvf $(DIR)/* $(OBJ) $(DIR)/*
	@echo -e "\n>> done cleaning <<"

cleanobj:
	@echo -e ">> cleaning <<\n"
	@rm -rvf $(OBJ)
	@echo -e "\n>> done cleaning <<"


dist:
	@echo -e ">> making dist tarball <<\n"
	@mkdir -vp $(TARGET)-$(VERSION)
	@cp -avr LICENSE Makefile config.mk $(SRC_DIR) $(TARGET)-$(VERSION)
	tar -cvf $(TARGET)-$(VERSION).tar $(TARGET)-$(VERSION)
	gzip -v $(TARGET)-$(VERSION).tar
	@rm -rvf $(TARGET)-$(VERSION)
	@echo -e "\n>> $(TARGET)-$(VERSION).tar.gz created <<"

install: all
	@echo -e "\n>> installing $(TARGET)-$(VERSION) <<\n"
	@mkdir -p $(DESTDIR)$(PREFIX)/$(DIR)
	@mkdir -p $(DESTDIR)$(PREFIX)/$(INC_DIR)
	@cp -vf $(DIR)/$(OUTPUT) $(DESTDIR)$(PREFIX)/$(DIR)
ifeq ($(TYPE), lib)
	@cp -vf $(SRC_DIR)/*.h $(DESTDIR)$(PREFIX)/$(INC_DIR)
	@/usr/bin/bash -c "pushd $(DESTDIR)$(PREFIX)/$(DIR) > /dev/null;\
	ln -svf $(OUTPUT) $(LIB_LN);\
	ln -svf $(OUTPUT) $(LIB_LN_V);\
	popd > /dev/null;"
endif
	@echo -e "\n>> done installing <<"

uninstall:
	@echo -e ">> uninstalling $(TARGET)-$(VERSION) <<\n"
	@rm -vf $(DESTDIR)$(PREFIX)/$(INC_DIR)/$(TARGET).h
	@rm -vf $(DESTDIR)$(PREFIX)/$(DIR)/$(OUTPUT) 
ifeq ($(TYPE), lib)
	@rm -vf $(DESTDIR)$(PREFIX)/$(DIR)/$(LIB_LN)
	@rm -vf $(DESTDIR)$(PREFIX)/$(DIR)/$(LIB_LN_V)
endif
	@echo -e "\n>> done uninstalling <<"

.PHONY: all options clean dist install uninstall
