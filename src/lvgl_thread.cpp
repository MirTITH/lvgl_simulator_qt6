#include "lvgl_thread.hpp"
#include "lv_port_disp.h"
#include <thread>
#include "lv_port_indev.h"

using namespace std;

void LvglThread::LvglThreadEntry(bool &isProgramRunning)
{
    lv_init();
    lv_port_disp_init(0);
    lv_port_indev_init();

    static lv_style_t page_stype;
    lv_style_init(&page_stype);
    lv_style_set_width(&page_stype, lv_pct(80));
    lv_style_set_height(&page_stype, lv_pct(95));
    lv_style_set_align(&page_stype, LV_ALIGN_BOTTOM_RIGHT);
    lv_style_set_border_width(&page_stype,1);
    lv_style_set_border_color(&page_stype,LV_COLOR_MAKE(128,128,128));

    auto parent_page = lv_obj_create(lv_scr_act());

    lv_obj_remove_style_all(parent_page);

    lv_obj_add_style(parent_page, &page_stype, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_create(parent_page);



    auto until_time = std::chrono::steady_clock::now();
    while (isProgramRunning) {
        {
            lock_guard<mutex> lock(_mux);
            lv_task_handler();
        }
        until_time += 5ms;
        this_thread::sleep_until(until_time);
    }
}

LvglThread lvgl_thread;
