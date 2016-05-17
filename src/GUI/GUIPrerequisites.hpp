#pragma once

#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GUI
{
    class ButtonElement;
    class CheckboxElement;
    class DropdownElement;
    class GUI;
    class GUIElement;
    class Page;
    class TextDisplayElement;
    class TextInsertElement;

    typedef std::unique_ptr<GUI>  UniqueGUI;
    typedef std::unique_ptr<Page> UniquePage;
}
