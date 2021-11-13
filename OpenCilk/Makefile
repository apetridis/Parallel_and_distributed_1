TARGET = mycilkexe

CILKCC = /usr/local/OpenCilk-9.0.1-Linux/bin/clang
CFLAGS = -O3

SRCDIR = src
OBJDIR = obj

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CILKCC) $(OBJECTS) $(CFLAGS) -o $@ -fcilkplus
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CILKCC) $(CFLAGS) -c $< -o $@ -fcilkplus
	@echo "Compiled "$<" successfully!"

run: 
	$ ./$(TARGET) NACA0015.mtx

.PHONY: clean
clean:
	$ rm -f $(TARGET) $(OBJECTS) 
	@echo "Project Cleaned"

	
