#include "AimingWidget.h"
#include <cmath>

#define AIM_X_CENTER 100
#define AIM_Y_CENTER 100
#define AIM_RADIUS 90


AimingWidget::AimingWidget(
        QObject *parent,
        QLabel *canvas,
        QLineEdit *xAngleStatus,
        QLineEdit *yAngleStatus)
        : parent(parent)
        , canvas(canvas)
        , xAngleStatus(xAngleStatus)
        , yAngleStatus(yAngleStatus)
{
    pixmap = new QPixmap(AIM_X_CENTER*2, AIM_Y_CENTER*2);
    painter = new QPainter(pixmap);
}

/*
QPoint AimingWidget::fromPolar(double angle, double radius)
{
    double xPosition = ((double)AIM_X_CENTER) + (((double)AIM_RADIUS) * cos(M_PI * double(angle) / 180.0));
    double yPosition = ((double)AIM_Y_CENTER) + (((double)AIM_RADIUS) * sin(M_PI * double(angle) / 180.0));

    return QPoint(xPosition, yPosition);
}


void AimingWidget::drawRay(float angle, int start, int stop)
{
    painter->drawLine(fromPolar(angle, start), fromPolar(angle, stop));
}
*/


void AimingWidget::updateCanvas(float xAngle, float yAngle, bool pressed)
{
    pixmap->fill();

    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawEllipse(AIM_X_CENTER - AIM_RADIUS, AIM_Y_CENTER - AIM_RADIUS, 2 * AIM_RADIUS, 2 * AIM_RADIUS);

    painter->setPen(Qt::black);
    if (pressed) {
        painter->setBrush(Qt::red);
    } else {
        painter->setBrush(Qt::gray);
    }
    painter->drawEllipse(AIM_X_CENTER + xAngle, AIM_Y_CENTER + yAngle, 10, 10);

    canvas->setPixmap(*pixmap);
}

void AimingWidget::updateControls(float xAngle, float yAngle)
{
    xAngleStatus->setText(QString::number(xAngle));
    yAngleStatus->setText(QString::number(yAngle));
}


void AimingWidget::update(float xAngle, float yAngle, bool pressed)
{
    updateCanvas(xAngle, yAngle, pressed);
    updateControls(xAngle, yAngle);
}
