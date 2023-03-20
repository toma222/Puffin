
COMPILER = g++
TARGET = x64
SYSTEM = windows
RELEASE_MODE = BUILD_TYPE=debug
BIN_PATH = dist/$(TARGET)/main
IMGUI_DIR = include\windows\imgui

IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
IMGUI_SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp $(IMGUI_DIR)/backends/imgui_impl_sdlrenderer.cpp
IMGUIOBJ = obj/imgui.o obj/imgui_widgets.o obj/imgui_tables.o obj/imgui_draw.o obj/imgui_demo.o obj/imgui_impl_sdlrenderer.o obj/imgui_impl_sdl.o

INCLUDE_PATH = -Iinclude/$(SYSTEM) -Iinclude/$(SYSTEM)/SDL2 -Iinclude/$(SYSTEM)/imgui -Iinclude/$(SYSTEM)/imgui/backends -Ipuffin/src -Iice/game
LIBRARY_FLAGS = -Llib/$(TARGET) -lSDL2main -lSDL2 -lSDL2_image -llua-5.4.4

ENGINEOBJ = obj/PRenderer.o obj/PSurface.o obj/PTexture.o obj/PWindow.o obj/Application.o obj/Graphics.o obj/Window.o obj/Logging.o obj/Instrumentor.o obj/Entity.o obj/Scene.o obj/SceneLoading.o
EDITOR_OBJ = obj/EditorApplication.o obj/EditorLayer.o
GAMEOBJ = obj/GameLayer.o

obj/%.o : include/windows/imgui/%.cpp
	@echo ------ COMPILING IMGUI FILE $< -------
	$(COMPILER) -Wall -O2 -c -o $@ $< $(INCLUDE_PATH)

obj/%.o : include/windows/imgui/backends/%.cpp
	@echo ------ COMPILING IMGUI BACKENDS FILE $< -------
	$(COMPILER) -Wall -O2 -c -o $@ $<  $(INCLUDE_PATH)

obj/%.o : puffin/src/Core/%.cpp puffin/src/Core/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : puffin/src/Debug/%.cpp puffin/src/Debug/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : puffin/src/Rendering/%.cpp puffin/src/Rendering/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : puffin/src/Scene/%.cpp puffin/src/Scene/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : ice/%.cpp ice/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : ice/editor/%.cpp ice/editor/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< -Iice/game $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : ice/game/Layer/%.cpp ice/game/Layer/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< -Iice/game $(INCLUDE_PATH) $(LIBRARY_FLAGS)

obj/%.o : ice/game/Scene/%.cpp ice/game/Scene/%.h
	@echo ------ COMPILING  FILE $< -------
	$(COMPILER) -Wall -O2 -c -D$(RELEASE_MODE) -o $@ $< -Iice/game $(INCLUDE_PATH) $(LIBRARY_FLAGS)


make: $(ENGINEOBJ) $(GAMEOBJ) $(EDITOR_OBJ) $(IMGUIOBJ)
	@echo ------ COMPILING OBJECTS -------
	$(COMPILER) -Wall -D$(RELEASE_MODE) -o $(BIN_PATH) ice/game.cpp $(ENGINEOBJ) $(IMGUIOBJ) $(GAMEOBJ) $(INCLUDE_PATH) $(LIBRARY_FLAGS)
	make run

run:
	./$(BIN_PATH)

clean:
	del $(addprefix obj\,$(notdir $(ENGINEOBJ)))
	del $(addprefix obj\,$(notdir $(EDITOR_OBJ)))
	del $(addprefix obj\,$(notdir $(GAMEOBJ)))

deep-clean:
	del $(addprefix obj\,$(notdir $(ENGINEOBJ)))
	del $(addprefix obj\,$(notdir $(EDITOR_OBJ)))
	del $(addprefix obj\,$(notdir $(GAMEOBJ)))
	del $(addprefix obj\,$(notdir $(IMGUIOBJ)))
	

