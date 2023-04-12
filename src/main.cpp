#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "lcd.hpp"
#include <thread>
#include "lvgl.h"
#include "lvgl_thread.hpp"
#include <mutex>

using namespace std;

bool isProgramRunning = true;

int main(int argc, char *argv[])
{
    qmlRegisterType<LCD>("LCD", 1, 0, "LCD");

    auto lvglT = std::thread([&]() {
        std::this_thread::sleep_for(500ms);
        while (lcds.size() < 1) {
            std::this_thread::sleep_for(500ms);
        }

        lvgl_thread.LvglThreadEntry(isProgramRunning);
    });

//    auto lvglTick = std::thread([]() {
//        auto until_time = chrono::steady_clock::now();
//        while (isProgramRunning) {
//            until_time += 1ms;
//            lv_tick_inc(1);
//            this_thread::sleep_until(until_time);
//        }
//    });

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    auto result = app.exec();

    isProgramRunning = false;

    lvglT.join();

    return result;
}
