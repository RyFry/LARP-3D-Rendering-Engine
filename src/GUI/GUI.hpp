#pragma once

#include <unordered_map>
#include <string>
#include <memory>         // unique_ptr

#include "GUIPrerequisites.hpp"
#include "Page.hpp"

namespace GUI
{
    /**
     * Manages the GUI system by storing and creating Pages
     */
    class GUI
    {
    private:
        bool _is_active;
        Page* _current_page;
        std::unordered_map<std::string, UniquePage> _pages;

        static UniqueGUI _singleton;

        GUI();
    public:
        static GUI* get_singleton();

        void set_active(bool is_active);
        bool is_active() const;
        Page* get_current_page() const;
        Page* add_page(std::string name);
    };
}
