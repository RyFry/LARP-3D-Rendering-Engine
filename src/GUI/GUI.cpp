#include "GUI.hpp"

GUI::GUI()
    : _is_active(false)
{
}

void GUI::set_active(bool is_active)
{
    this->_is_active = is_active;
}

bool GUI::is_active() const
{
    return this->_is_active;
}
