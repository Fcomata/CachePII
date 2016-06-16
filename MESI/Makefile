_OBJS = Bloque.o Cache.o
CC = g++
DEBUG = -g
ODIR = obj
SDIR = src
CFLAGS = -c $(DEBUG)
LFLAGS = -std=gnu++0x $(DEBUG)
TARGET = mi_cache
INC = -I 'include'

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o : $(SDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -o $@ $< $

$(TARGET): $(OBJS) main.cpp
	$(CC) $(LFLAGS) $(INC) main.cpp $(OBJS)  -o $(TARGET)
.PHONY: clean
 clean:
	rm -f $(ODIR)/*.o $(TARGET)
