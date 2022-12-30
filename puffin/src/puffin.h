#pragma once

#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"
#include "puffin/core/Window.h"
#include "puffin/core/Application.h"
#include "puffin/core/Layer.h"
#include "puffin/core/LayerStack.h"

// ---------- PLATFORM THINGS ---------- //
#include "platform/GLFWContext.h"
#include "platform/GLFWWindow.h"
#include "platform/GLFWUtils.h"

// ---------- ENTRY POINT ---------- //
#include "puffin/core/EntryPoint.h"

// ---------- GRAPHICS ---------- //
#include "puffin/graphics/Context.h"
#include "puffin/graphics/Graphics.h"
#include "puffin/graphics/Shader.h"
#include "puffin/graphics/Vertices.h"
#include "puffin/graphics/PerspectiveCamera.h"

// ---------- EVENTS ---------- //
#include "puffin/events/Event.h"
#include "puffin/events/KeyboardEvents.h"
#include "puffin/events/MouseEvent.h"