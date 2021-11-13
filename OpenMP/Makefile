TARGET = mympexe

CC = gcc
CFLAGS = -O3 -fPIC

SRCDIR = src
OBJDIR = obj

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@ -fopenmp 
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -fopenmp 
	@echo "Compiled "$<" successfully!"

run: 
	$ ./$(TARGET) NACA0015.mtx

.PHONY: clean
clean:
	$ rm -f $(TARGET) $(OBJECTS) 
	@echo "Project Cleaned"

	
