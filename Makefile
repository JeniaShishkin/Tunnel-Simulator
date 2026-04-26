# Makefile for Tunnel Simulation Project
# Compiler and flags
CXX := x86_64-w64-mingw32-g++
CXXFLAGS := -std=c++20 -Wall -Wextra -g
LDFLAGS := -static-libstdc++ -static-libgcc -lws2_32

# Project structure
SRCDIR := .
BINDIR := bin
OBJDIR := obj

# Executable name
TARGET := $(BINDIR)/prog.exe

# Source files from root directory
ROOT_SOURCES := main.cpp Drone.cpp Session.cpp

# Source files from Cmd directory
CMD_SOURCES := Cmd/Backward.cpp Cmd/DropMine.cpp Cmd/Execute.cpp Cmd/Forward.cpp \
               Cmd/Map.cpp Cmd/PointOfView.cpp Cmd/TurnLeft.cpp Cmd/TurnRight.cpp

# Source files from Navigation directory
NAV_SOURCES := Navigation/Compass.cpp Navigation/Position.cpp Navigation/WorldGrid.cpp

# Source files from Networking directory
NET_SOURCES := Networking/DroneNetworkHandler.cpp Networking/NetworkHandler.cpp

# Source files from Sensors directory
SENSOR_SOURCES := Sensors/CircularSensor.cpp Sensors/DistanceSensor.cpp \
                  Sensors/Sensor.cpp Sensors/WideSensor.cpp

# Source files from Tiles directory
TILE_SOURCES := Tiles/EmptyTile.cpp Tiles/Tile.cpp

# Combine all sources
SOURCES := $(ROOT_SOURCES) $(CMD_SOURCES) $(NAV_SOURCES) $(NET_SOURCES) \
           $(SENSOR_SOURCES) $(TILE_SOURCES)

# Create object file names from source files
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Create directories if they don't exist
$(BINDIR) $(OBJDIR):
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)/Cmd
	mkdir -p $(OBJDIR)/Navigation
	mkdir -p $(OBJDIR)/Networking
	mkdir -p $(OBJDIR)/Sensors
	mkdir -p $(OBJDIR)/Tiles

# Link all objects into the executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET)
	@echo "✓ Build successful: $(TARGET)"

# Compile each source file into an object file
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "✓ Compiled: $<"

# Clean object files and executable
clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	@echo "✓ Clean complete"

# Clean only object files (keeps executable)
clean-obj:
	rm -rf $(OBJDIR)
	@echo "✓ Object files cleaned"

# Rebuild: clean and build
rebuild: clean all

# Display help
help:
	@echo "Available targets:"
	@echo "  all       - Build the executable (default)"
	@echo "  rebuild   - Clean and build from scratch"
	@echo "  clean     - Remove all build artifacts"
	@echo "  clean-obj - Remove object files only"
	@echo "  help      - Display this help message"

# List all source files and their object files
list:
	@echo "Source files:"
	@$(foreach src,$(SOURCES),echo "  $(src)";)
	@echo ""
	@echo "Object files:"
	@$(foreach obj,$(OBJECTS),echo "  $(obj)";)

# Phony targets (not actual files)
.PHONY: all clean clean-obj rebuild help list
