#include "GUI.hpp"

GUI::GUI()
    : m_is_active(false)
{
}

void GUI::set_active(bool is_active)
{
    m_is_active = is_active;
}

bool GUI::is_active() const
{
    return m_is_active;
}
