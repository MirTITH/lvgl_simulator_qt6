#pragma once

#include <QImage>
#include <QQuickPaintedItem>
#include <QtQml/qqmlregistration.h>
#include <vector>

class LCD : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    void paint(QPainter *painter) override;

    LCD(QQuickItem *parent = 0);

    ~LCD();

    Q_INVOKABLE void init(int screenWidth, int screenHeight);

    int getScreenWidth() const
    {
        return screenWidth;
    }

    void setScreenWidth(int newScreenWidth);

    int getScreenHeight() const
    {
        return screenHeight;
    }

    void setScreenHeight(int newScreenHeight);

signals:
    void screenWidthChanged();

    void screenHeightChanged();

private:
    QImage *screenMem = nullptr;
    int screenWidth;
    int screenHeight;

    Q_PROPERTY(int screenWidth READ getScreenWidth NOTIFY screenWidthChanged);
    Q_PROPERTY(int screenHeight READ getScreenHeight NOTIFY screenHeightChanged);
};