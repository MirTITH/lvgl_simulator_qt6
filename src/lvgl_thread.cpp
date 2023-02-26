#include "lvgl_thread.hpp"
#include "lv_port_disp.h"
#include <thread>
#include "screen_console.hpp"
#include "lv_port_indev.h"

using namespace std;

void LvglThread::LvglThreadEntry(bool &isProgramRunning)
{
    lv_init();
    lv_port_disp_init(0);
    lv_port_indev_init();

    StartScreenConsoleThread(isProgramRunning);

    auto until_time = std::chrono::steady_clock::now();
    while (isProgramRunning) {
        {
            lock_guard<mutex> lock(_mux);
            lv_task_handler();
        }
        until_time += 4ms;
        this_thread::sleep_until(until_time);
    }
}

LvglThread lvgl_thread;
