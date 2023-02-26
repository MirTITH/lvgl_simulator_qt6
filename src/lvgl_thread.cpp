#include "lvgl_thread.hpp"
#include "lv_port_disp.h"
#include <thread>

using namespace std;

void LvglThread::LvglThreadEntry(bool &isProgramRunning)
{
    lv_init();
    lv_port_disp_init(0);

    auto until_time = std::chrono::steady_clock::now();
    while (isProgramRunning) {
        until_time += 5ms;
        {
            lock_guard<mutex> lock(_mux);
            lv_task_handler();
        }
        this_thread::sleep_until(until_time);
    }
}
