# Compiler (GCC by default)
CC=gcc

ifeq ($(OS),Windows_NT)
	CC		= g++
endif

CC_FLAGS		= -g -std=c++98 -Wall -Wl,-O1 -pipe -O2 -flto=2 \
			 -fno-fat-lto-objects -fuse-linker-plugin -fPIC
SA_CC_FLAGS 		= -Wall -c -g

# Directories needed for build
SRC_DIR			= src
LIBS_DIR		= libs
OUT_DIR			= out

# Libraries
TINYDIR_SRC		= $(LIBS_DIR)/tinydir

EXT_INCLUDES		= -I./src \
			  -I./libs/jsoncpp/include \
			  -I./$(TINYDIR_SRC)

POSTLIBS		= -lncursesw $(EXT_INCLUDES) -lstdc++

# Source codes
SOURCES			= $(SRC_DIR)/*.cpp $(SRC_DIR)/utils/*.cpp \
			  $(SRC_DIR)/windows/*.cpp $(SRC_DIR)/controls/*.cpp \
			  $(LIBS_DIR)/jsoncpp/src/lib_json/*.cpp
OUT_FILE=$(OUT_DIR)/linux/knowledges

# Static libraries linking
SA_CC_FLAGS 		= -g -std=c++98 -Wall -static
SA_LIBS			= $(EXT_INCLUDES) -L./$(OUT_DIR)
SA_JCPP_FILE		= $(OUT_DIR)/jsoncpp.o
SA_JCPP_ARCH_FILE	= $(OUT_DIR)/jsoncpp.a
SA_POSTLIBS		= -lncursesw $(EXT_INCLUDES) -ltinfo -lstdc++

ifeq ($(OS),Windows_NT)
	SA_CC_FLAGS 	=  -g -std=c++98 -Wall -s
	SA_POSTLIBS 	= -lncursesw -lstdc++ $(EXT_INCLUDES) -I/mingw64/include/ncursesw \
			  -static -DNCURSES_STATIC -DNCURSES_WIDECHAR=1
	OUT_FILE=$(OUT_DIR)/windows-mingw64/knowledges
endif

# Clean files function
DEL_FILE      	= rm -f

# Targets
build: $(SOURCE)
	$(CC) $(CC_FLAGS) $(LIBS) $(SOURCES) -o $(OUT_FILE) $(POSTLIBS)

standalone:
	$(CC) $(SA_CC_FLAGS) $(LIBS) $(SOURCES) -o $(OUT_FILE) $(SA_POSTLIBS)

sa_cygwin:
	g++ -g -std=c++98 -Wall -s $(LIBS) $(SOURCES) -o $(OUT_FILE).exe \
	-lncursesw $(EXT_INCLUDES) -I/mingw64/include/ncurses -static -DNCURSES_STATIC \
	-D__CYGWIN_MINGW64__

clean:
	$(DEL_FILE) out/*
