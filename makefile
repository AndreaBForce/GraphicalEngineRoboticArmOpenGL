###############
# COMMANDS
###############

CC = gcc
CXX = g++

# Engine flags
EFLAGS = -fPIC -Wall -std=c++11 -fexceptions -Iinclude -Idependencies/glm/include
EINCLUDE = -lglut -lGL -lfreeimage -lGLU
EDFLAGS = $(EFLAGS) -g
ERFLAGS = $(EFLAGS) -O2
LDFLAGS = -shared

# Client flags
CLFLAGS = -Wall -std=c++11 -Iinclude -I$(ENGINE_NAME) -Idependencies/glm/include
CLRFLAGS = $(CLFLAGS) -O2
CLDFLAGS = $(CLFLAGS) -g

CHK_CREATE_DIR = @[ -d $@ ] || mkdir -p $@
RM = rm -f
TAR = tar -czvf
AR = ar rcs

###################
# VARIABLES
###################

#*******************
# Client variables
#*******************

MAIN = main
CLIENT_NAME = client
CLIENT_CPP_FILE = $(CLIENT_NAME)/$(MAIN).cpp

# Debug client variables
D_CLIENT_O_DIR = $(CLIENT_NAME)/obj/Debug
D_CLIENT_EXE_DIR = $(CLIENT_NAME)/bin/Debug
D_CLIENT_O_FILE = $(patsubst $(CLIENT_NAME)/%.cpp,$(D_CLIENT_O_DIR)/%.o,$(CLIENT_CPP_FILE))
D_CLIENT_EXECUTABLE = $(D_CLIENT_EXE_DIR)/$(CLIENT_NAME)

# Release client variables
R_CLIENT_O_DIR = $(CLIENT_NAME)/obj/Release
R_CLIENT_EXE_DIR = $(CLIENT_NAME)/bin/Release
R_CLIENT_O_FILE = $(patsubst $(CLIENT_NAME)/%.cpp,$(R_CLIENT_O_DIR)/%.o,$(CLIENT_CPP_FILE))
R_CLIENT_EXECUTABLE = $(R_CLIENT_EXE_DIR)/$(CLIENT_NAME)

#*******************
# Engine variables
#*******************

ENGINE_NAME = engine
ENGINE_LIB_NAME = lib$(ENGINE_NAME).so
ENGINE_CPP_FILES = $(wildcard $(ENGINE_NAME)/*.cpp)

# Debug engine variables
D_ENGINE_O_DIR = $(ENGINE_NAME)/obj/Debug
D_ENGINE_LIB_DIR = $(ENGINE_NAME)/bin/Debug
D_ENGINE_LIB_PATH = $(D_ENGINE_LIB_DIR)/$(ENGINE_LIB_NAME)
D_ENGINE_O_FILES = $(patsubst $(ENGINE_NAME)/%.cpp,$(D_ENGINE_O_DIR)/%.o,$(ENGINE_CPP_FILES))

# Release engine variables
R_ENGINE_O_DIR = $(ENGINE_NAME)/obj/Release
R_ENGINE_LIB_DIR = $(ENGINE_NAME)/bin/Release
R_ENGINE_LIB_PATH = $(R_ENGINE_LIB_DIR)/$(ENGINE_LIB_NAME)
R_ENGINE_O_FILES = $(patsubst $(ENGINE_NAME)/%.cpp,$(R_ENGINE_O_DIR)/%.o,$(ENGINE_CPP_FILES))

.PHONY : all_release
all_release: clean_release run_release

.PHONY : all_debug
all_debug: clean_debug run_debug

.PHONY : build_realease
build_release: client_build_release

.PHONY : build_debug
build_debug: client_build_debug


###################################
# CLIENT BUILD
###################################

#********************************
# Client build DEBUG lifecycle
#********************************

client_build_debug: $(D_CLIENT_O_FILE) $(D_CLIENT_EXE_DIR) engine_build_debug
	$(CXX) -L$(D_ENGINE_LIB_DIR) -o $(D_CLIENT_EXECUTABLE) $< -l$(ENGINE_NAME)
	@echo "BUILDING CLIENT DEBUG DONE"
	
$(D_CLIENT_O_DIR)/%.o: $(CLIENT_NAME)/%.cpp $(D_CLIENT_O_DIR)
	@echo "BUILDING CLIENT DEBUG"
	$(CXX) $(CLDFLAGS) -c $< -o $@
	
#********************************
# Client build RELEASE lifecycle
#********************************

client_build_release: $(R_CLIENT_O_FILE) $(R_CLIENT_EXE_DIR) engine_build_release
	$(CXX) -L$(R_ENGINE_LIB_DIR) -o $(R_CLIENT_EXECUTABLE) $< -s -lengine
	@echo "BUILDING CLIENT REALEASE DONE"
	
$(R_CLIENT_O_DIR)/%.o: $(CLIENT_NAME)/%.cpp $(R_CLIENT_O_DIR)
	@echo "BUILDING CLIENT RELEASE"
	$(CXX) $(CLRFLAGS) -c $< -o $@

###################################
# ENGINE BUILD
###################################

#*******************************
# Engine build DEBUG lifecycle
#*******************************
ed_msg:
	@echo "BUILDING ENGINE DEBUG"

engine_build_debug: ed_msg $(D_ENGINE_O_FILES) $(D_ENGINE_LIB_DIR)
	$(CXX) $(LDFLAGS) $(D_ENGINE_O_FILES) -o $(D_ENGINE_LIB_PATH) $(EINCLUDE)
	@echo "BUILDING ENGINE DEBUG DONE"
	
$(D_ENGINE_O_DIR)/%.o: $(ENGINE_NAME)/%.cpp $(D_ENGINE_O_DIR)
	$(CXX) $(EDFLAGS) -c $< -o $@
	
#********************************
# Engine build RELEASE lifecycle
#********************************
er_msg:
	@echo "BUILDING ENGINE RELEASE"

engine_build_release: er_msg $(R_ENGINE_O_FILES) $(R_ENGINE_LIB_DIR)
	$(CXX) $(LDFLAGS) $(R_ENGINE_O_FILES) -o $(R_ENGINE_LIB_PATH) -s $(EINCLUDE)
	@echo "BUILDING ENGINE RELEASE DONE"
	
$(R_ENGINE_O_DIR)/%.o: $(ENGINE_NAME)/%.cpp $(R_ENGINE_O_DIR)
	$(CXX) $(ERFLAGS) -c $< -o $@
	
###################################
# CLIENT RUN
###################################

#**********************
# Client run RELEASE
#**********************

run_release: client_build_release
	@echo "RUN CLIENT RELEASE"
	gnome-terminal -t client -- /usr/bin/cb_console_runner LD_LIBRARY_PATH=:.:$(R_ENGINE_LIB_DIR) $(R_CLIENT_EXECUTABLE)

#**********************
# Client run DEBUG
#**********************

run_debug: client_build_debug
	@echo "RUN CLIENT DEBUG"
	gnome-terminal -t client -- /usr/bin/cb_console_runner LD_LIBRARY_PATH=:.:$(D_ENGINE_LIB_DIR) $(D_CLIENT_EXECUTABLE)

#################################
# CLEAN
#################################

# Clean all lifecycle
.PHONY : clean_all
clean_all: clean_debug clean_release
	
# Clean debug lifecycle
.PHONY : clean_debug
clean_debug:
	@echo "CLEANING DEBUG"
	$(RM) $(D_ENGINE_O_FILES) $(D_ENGINE_LIB_PATH) $(D_CLIENT_O_FILE) $(D_CLIENT_EXECUTABLE)
	@echo "CLEANING DONE!"

# Clean release lifecycle
.PHONY : clean_release
clean_release:
	@echo "CLEANING RELEASE"
	$(RM) $(R_ENGINE_O_FILES) $(R_ENGINE_LIB_PATH) $(R_CLIENT_O_FILE) $(R_CLIENT_EXECUTABLE)
	@echo "CLEANING DONE!"
	
#################################
# Directories creation
#################################

$(D_CLIENT_O_DIR) $(D_CLIENT_EXE_DIR) $(R_CLIENT_O_DIR) $(R_CLIENT_EXE_DIR) $(D_ENGINE_O_DIR) $(D_ENGINE_LIB_DIR) $(R_ENGINE_O_DIR) $(R_ENGINE_LIB_DIR):
	$(CHK_CREATE_DIR)
	
.DEFAULT :
	@echo "Default"

