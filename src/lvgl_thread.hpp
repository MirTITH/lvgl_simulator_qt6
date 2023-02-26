#pragma once

#include <mutex>
#include "lcd.hpp"

class LvglThread
{
public:
    std::mutex _mux;

    void LvglThreadEntry(bool &isProgramRunning);
};

extern LvglThread lvgl_thread;
