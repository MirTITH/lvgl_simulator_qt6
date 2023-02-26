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
    bool isLcdMouseDown = false;

    void paint(QPainter *painter) override;

    void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
    {
        if (screenMem == nullptr) {
            return;
        }

        screenMem->setPixel(x, y, qRgb(r, g, b));
    };

    LCD(QQuickItem *parent = 0);

    ~LCD();

    Q_INVOKABLE void init(int screenWidth, int screenHeight);

    Q_INVOKABLE void lcdMouseDown(bool isDown);

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

    double getLcdMouseX() const;
    void setLcdMouseX(double newLcdMouseX);

    double getLcdMouseY() const;
    void setLcdMouseY(double newLcdMouseY);

    float getConvertedMouseX() const
    {
        float result = lcdMouseX / width() * screenWidth;
        if (result >= screenWidth) {
            result = screenWidth - 1;
        } else if (result < 0) {
            result = 0;
        }
        return result;
    };
    float getConvertedMouseY() const
    {
        float result = lcdMouseY / height() * screenHeight;
        if (result >= screenHeight) {
            result = screenHeight - 1;
        } else if (result < 0) {
            result = 0;
        }
        return result;
    };

signals:
    void screenWidthChanged();

    void screenHeightChanged();

    void lcdMouseXChanged();

    void lcdMouseYChanged();

private:
    QImage *screenMem = nullptr;
    int screenWidth;
    int screenHeight;

    double lcdMouseX;
    double lcdMouseY;

    Q_PROPERTY(int screenWidth READ getScreenWidth NOTIFY screenWidthChanged);
    Q_PROPERTY(int screenHeight READ getScreenHeight NOTIFY screenHeightChanged);
    Q_PROPERTY(double lcdMouseX READ getLcdMouseX WRITE setLcdMouseX NOTIFY lcdMouseXChanged)
    Q_PROPERTY(double lcdMouseY READ getLcdMouseY WRITE setLcdMouseY NOTIFY lcdMouseYChanged)
};

extern std::vector<LCD *> lcds;
