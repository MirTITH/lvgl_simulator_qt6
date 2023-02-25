#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "lcd.hpp"

int main(int argc, char *argv[])
{
    qmlRegisterType<LCD>("LCD", 1, 0, "LCD");

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

    return app.exec();
}
