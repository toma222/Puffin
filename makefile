
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
PUFFIN_COMPILE_FLAGS = -c -fPIC

# PUFFIN 3D PARTY LIB FILES
PUFFIN_FILES = puffin\vendor\glad\gl.cpp

# PUFFIN CORE FILES
PUFFIN_FILES += $(PUFFIN_SRC)/puffin/core/Application.cpp $(PUFFIN_SRC)/puffin/core/Window.cpp $(PUFFIN_SRC)/puffin/cores/Logging.cpp

# PUFFIN GLDF PLATFORM FILES
PUFFIN_FILES += $(PUFFIN_SRC)\platform\GLFWWindow.cpp $(PUFFIN_SRC)\platform\GLFWContext.cpp

# PUFFIN RENDER FILES
PUFFIN_FILES += $(PUFFIN_SRC)\puffin\graphics\Graphics.cpp $(PUFFIN_SRC)\puffin\graphics\Context.cpp

INCLUDE += -I$(PUFFIN_SRC)
PUFFIN_INCLUDE = -Ipuffin/vendor -I$(PUFFIN_SRC)

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
LIBS = -Ldist

all: build

# ----------------------------------------- #
#             GAME BUILD RULES              #
# ----------------------------------------- #

$(ODIR)/%.o : $(GAMEDIR)/%.cpp puffin\src\puffin\core\EntryPoint.h
	$(CXX) -c $(INCLUDE) -o $@ $<

# ----------------------------------------- #
#            PUFFIN BUILD RULES             #
# ----------------------------------------- #
$(POBJOUT)/gl.o: puffin\vendor\glad\gl.cpp
	@echo ------- COMPILING GLAD $< -------
	$(CXX) $(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<
	@echo DONE

# Core directory
$(POBJOUT)/%.o: $(PUFFIN_SRC)/puffin/core/%.cpp $(PUFFIN_SRC)/puffin/core/%.h
	@echo ------- COMPILING PUFFIN CORE $< -------
	$(CXX) $(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<
	@echo DONE

# Graphics directory
$(POBJOUT)/%.o: $(PUFFIN_SRC)/puffin/graphics/%.cpp $(PUFFIN_SRC)/puffin/graphics/%.h
	@echo ------- COMPILING PUFFIN GRAPHICS $< -------
	$(CXX) $(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<
	@echo DONE

# Platform Directory
$(POBJOUT)/%.o: $(PUFFIN_SRC)/platform/%.cpp $(PUFFIN_SRC)/platform/%.h
	@echo ------- COMPILING PUFFIN PLATFORM $< -------
	$(CXX) $(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<
	@echo DONE

$(POBJOUT)/%.o: $(PUFFIN_SRC)/puffin/renderer/%.cpp $(PUFFIN_SRC)/puffin/renderer/%.cpp
	@echo ------- COMPILING PUFFIN PLATFORM $< -------
	$(CXX) $(PUFFIN_INCLUDE) $(PUFFIN_COMPILE_FLAGS) -DBUILD_DLL -o $@ $<
	@echo DONE


buildlib: $(PUFFINOBJ)
	@echo -------------------------------------------
	@echo           BUILDING PUFFIN LIBRARY          
	@echo -------------------------------------------
	$(CXX) -shared -o $(EXEPATH)/puffin.so $(PUFFINOBJ) -Llib -l:libglfw3dll.a -lglu32 -lopengl32

build : $(OBJ)
	make buildlib

	@echo -------------------------------------------
	@echo     COMPILING GAME WITH PUFFIN LIBRARY          
	@echo -------------------------------------------
	$(CXX) $(LIBS) -l:puffin.so -o $(EXEPATH)/app $(ODIR)/game.o

	@echo -------------------------------------------
	@echo             RUNNING THE GAME
	@echo -------------------------------------------
	./$(EXEPATH)/app.exe
	

run:
	./$(EXEPATH)/app.exe

clean:
	@echo begining clean
	@echo cleaning puffin library object files
	del $(PUFFINCLEANFILES)