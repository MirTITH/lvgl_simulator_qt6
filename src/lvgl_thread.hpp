#pragma once

#include <thread>
#include <mutex>
#include "lvgl/lvgl.h"
#include "lv_port_disp.h"

class LvglThread
{
public:
    std::mutex _mux;

    LvglThread(){
        auto lvgl_thread = std::thread();
    }


private:

    void LvglThreadEntry(){
        lv_init();
        lv_port_disp_init();
    }
};
