#include "GUI.hpp"

namespace GUI
{
    UniqueGUI GUI::_singleton(nullptr);

    GUI::GUI()
        : _is_active(false),
        _current_page(nullptr)
    {
    }

    GUI* GUI::get_singleton()
    {
        if (_singleton == nullptr)
        {
            _singleton.reset(new GUI());
        }
        return _singleton.get();
    }

    void GUI::set_active(bool is_active)
    {
        this->_is_active = is_active;
    }

    bool GUI::is_active() const
    {
        return this->_is_active;
    }

    Page* GUI::get_current_page() const
    {
        return this->_current_page;
    }

    Page* GUI::add_page(std::string name)
    {
        if (this->_pages.find(name) == this->_pages.end())
        {
            this->_pages.emplace(name, UniquePage(new Page()));
        }
        return this->_pages.at(name).get();
    }
}
