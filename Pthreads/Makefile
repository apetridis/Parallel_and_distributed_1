TARGET = mythreadsexe

CC = gcc
CFLAGS = -O3

SRCDIR = src
OBJDIR = obj

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@ -pthread
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -pthread
	@echo "Compiled "$<" successfully!"

run: 
	$ ./$(TARGET) belgium_osm.mtx

.PHONY: clean
clean:
	$ rm -f $(TARGET) $(OBJECTS) 
	@echo "Project Cleaned"

	
