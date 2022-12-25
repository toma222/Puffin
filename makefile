
IMGUI_DIR = include/imgui

ODIR = obj
EXEPATH = dist

SOURCES = game/src/game.cpp

OBJ = $(addprefix $(ODIR)/,$(addsuffix .o, $(basename $(notdir $(SOURCES)))))

INCLUDE = -Iinclude

# -------------------------------- #
#         PUFFIN SETTINGS          #
# -------------------------------- #

PUFFIN_SRC = puffin/src
PUFFIN_COMPILE_FLAGS = -g -c -fPIC

PUFFIN_FILES = $(PUFFIN_SRC)/puffin/core/Application.cpp $(PUFFIN_SRC)/puffin/core/Window.cpp $(PUFFIN_SRC)/puffin/core/GLFWWindow.cpp $(PUFFIN_SRC)/puffin/cores/Logging.cpp

INCLUDE += -I$(PUFFIN_SRC)
PUFFIN_INCLUDE = puffin/vendor

POBJOUT = $(ODIR)\puffin
PUFFINOBJ = $(addprefix $(POBJOUT)/,$(addsuffix .o, $(basename $(notdir $(PUFFIN_FILES)))))
PUFFINCLEANFILES += $(addprefix $(POBJOUT)\,$(addsuffix .o, $(basename $(notdir $(PUFFIN_FILES)))))

OBJ += $(PUFFINOBJ)

# -------------------------------- #
#          GAME SETTINGS           #
# -------------------------------- #

GAMEDIR = game/src

# -------------------------------- #

CXX = g++

LIB = dist
LIBS = -L$(LIB) -lglu32 -lopengl32

all: build

# ----------------------------------------- #
#             GAME BUILD RULES              #
# ----------------------------------------- #

$(ODIR)/%.o : $(GAMEDIR)/%.cpp
	$(CXX) -c $(INCLUDE) -o $@ $<

# ----------------------------------------- #
#            PUFFIN BUILD RULES             #
# ----------------------------------------- #
$(POBJOUT)/%.o: $(PUFFIN_SRC)/puffin/core/%.cpp $(PUFFIN_SRC)/puffin/core/%.h
	@echo Compiling puffin file $<
	$(CXX) -I$(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<

$(POBJOUT)/%.o: $(PUFFIN_SRC)/puffin/renderer/%.cpp $(PUFFIN_SRC)/renderer/core/%.h
	@echo Compiling puffin file $<
	$(CXX) -I$(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<


buildlib: $(PUFFINOBJ)
	@echo # --------- BUILDING PUFFIN LIBRARY --------- #
	@echo Compiling the puffin library
	$(CXX) -shared -o $(EXEPATH)/puffin.dll -Wl,--out-implib,$(EXEPATH)/puffin.a $(PUFFINOBJ)

build : $(OBJ)
	make buildlib

	@echo # --------- LINKING PUFFIN TO GAME --------- #
	@echo $(OBJ)
	$(CXX) $(LIBS) -l:puffin.dll -o $(EXEPATH)/app $(ODIR)/game.o

	@echo # --------- RUNNING --------- #
	./$(EXEPATH)/app.exe
	

run:
	./$(EXEPATH)/app.exe

clean:
	@echo begining clean
	@echo cleaning puffin library object files
	del $(PUFFINCLEANFILES)