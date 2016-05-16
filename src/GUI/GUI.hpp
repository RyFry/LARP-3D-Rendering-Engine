#pragma once

class GUI
{
private:
    bool _is_active;

public:
    GUI();

    void set_active(bool is_active);
    bool is_active() const;
};
