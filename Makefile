# Compiler (GCC by default)
CC=gcc

ifeq ($(OSTYPE), "msys")
	CC		= mingw-w64-x86_64-gcc
endif

CC_FLAGS		= -g -std=c++98 -Wall -Wl,-O1 -pipe -O2 -flto=2 \
			 -fno-fat-lto-objects -fuse-linker-plugin -fPIC
SA_CC_FLAGS 		= -Wall -c -g

# Directories needed for build
SRC_DIR			= src
LIBS_DIR		= libs
OUT_DIR			= out

# Libraries
EXT_INCLUDES		= -I./src
EXT_INCLUDES 	       += -I./libs/jsoncpp/include
POSTLIBS		= -lncursesw $(EXT_INCLUDES) -lstdc++

# Source codes
SOURCES=$(SRC_DIR)/*.cpp $(SRC_DIR)/utils/*.cpp $(SRC_DIR)/windows/*.cpp $(SRC_DIR)/controls/*.cpp $(LIBS_DIR)/jsoncpp/src/lib_json/*.cpp
OUT_FILE=$(OUT_DIR)/knowledges
SA_OUT_FILE=$(OUT_DIR)/knowledges.o

ifeq ($(OSTYPE), "msys")
	LIBS	= -static -static-libgcc -static-libstdc++ -lncursesw $(EXT_INCLUDES)
	OUT_FILE= $(OUT_DIR)/knowledges.exe
endif

# Clean files function
DEL_FILE      	= rm -f

# Targets
build: $(SOURCE)
	$(CC) $(CC_FLAGS) $(LIBS) $(SOURCES) -o $(OUT_FILE) $(POSTLIBS)

standalone:
	$(CC) $(SA_CC_FLAGS) $(LIBS) $(SOURCES) -o $(SA_OUT_FILE)
	$(CC) -o $(OUT_FILE) $(SA_OUT_FILE)

clean:
	$(DEL_FILE) out/*


