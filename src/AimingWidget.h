#ifndef AIMING_WIDGET_H
#define AIMING_WIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>


class AimingWidget
{
public:
    AimingWidget(
        QObject *parent,
        QLabel *canvas,
        QLineEdit *xAngleStatus,
        QLineEdit *yAngleStatus);

    void update(float xAngle, float yAngle, bool pressed);

private:
    void updateCanvas(float xAngle, float yAngle, bool pressed);
    void updateControls(float xAngle, float yAngle);

private:
    float xAngle;
    float yAngle;

    QObject *parent;
    QLabel *canvas;
    QLineEdit *xAngleStatus;
    QLineEdit *yAngleStatus;

    QPixmap *pixmap;
    QPainter *painter;
};

#endif
