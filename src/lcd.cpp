#include "lcd.hpp"
#include <QPainter>
#include <QDebug>

std::vector<LCD *> lcds;

void LCD::paint(QPainter *painter)
{
    if (painter == nullptr) {
        return;
    }

    if (screenMem == nullptr) {
        return;
    }

    //    for (int y = 0; y < screenMem->height(); ++y) {
    //        for (int x = 0; x < screenMem->width(); ++x) {
    //            screenMem->setPixel(x, y, qRgb(rand() % 255, rand() % 255, rand() % 255));
    //        }
    //    }

    QImage tempImage = screenMem->scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->drawImage(0, 0, tempImage);
    //        painter->drawImage(0, 0, *screenMem);
}

LCD::LCD(QQuickItem *parent)
{
    lcds.push_back(this);
    qDebug() << "new LCD:" << lcds;
}

LCD::~LCD()
{
    if (screenMem != nullptr) {
        delete screenMem;
    }

    // 从lcds中删除
    lcds.erase(std::remove(std::begin(lcds), std::end(lcds), this), std::end(lcds));
    qDebug() << "delete LCD:" << lcds;
}

void LCD::init(int screenWidth, int screenHeight)
{
    this->screenWidth  = screenWidth;
    this->screenHeight = screenHeight;
    screenMem          = new QImage(screenWidth, screenHeight, QImage::Format_RGB32);

    for (int y = 0; y < screenMem->height(); ++y) {
        for (int x = 0; x < screenMem->width(); ++x) {
            screenMem->setPixel(x, y, qRgb(rand() % 255, rand() % 255, rand() % 255));
        }
    }
}

void LCD::lcdMouseDown(bool isDown)
{
    isLcdMouseDown = isDown;
    //    qDebug() << "lcd Mouse Down:" << isDown;
    //    qDebug() << getConvertedMouseX() << getConvertedMouseY();
}

void LCD::setScreenWidth(int newScreenWidth)
{
    if (screenWidth == newScreenWidth) return;
    screenWidth = newScreenWidth;
    emit screenWidthChanged();
}

void LCD::setScreenHeight(int newScreenHeight)
{
    if (screenHeight == newScreenHeight) return;
    screenHeight = newScreenHeight;
    emit screenHeightChanged();
}

double LCD::getLcdMouseX() const
{
    return lcdMouseX;
}

void LCD::setLcdMouseX(double newLcdMouseX)
{
    if (qFuzzyCompare(lcdMouseX, newLcdMouseX))
        return;
    lcdMouseX = newLcdMouseX;
    emit lcdMouseXChanged();
}

double LCD::getLcdMouseY() const
{
    return lcdMouseY;
}

void LCD::setLcdMouseY(double newLcdMouseY)
{
    if (qFuzzyCompare(lcdMouseY, newLcdMouseY))
        return;
    lcdMouseY = newLcdMouseY;
    emit lcdMouseYChanged();
}
