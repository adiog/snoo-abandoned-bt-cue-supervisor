#ifndef IMUSENSOR_H
#define IMUSENSOR_H

#include "protocol.h"
#include <QTimer>
#include <QVector>
#include <qcustomplot.h>
#include <QTextEdit>


using OneDimensionPlotData = QVector<double>;
using ThreeDimensionsPlotData = std::array<OneDimensionPlotData, AXIS>;

class ImuSensor
{
public:
    ImuSensor(
            QObject * parent,
            QCustomPlot *plotAccelerometer,
            QCustomPlot *plotGyroscope,
            QCustomPlot *plotMagnetometer
            );

    void reset();

    void updateAccelerometer(const float accelerometerValue[AXIS]);
    void updateGyroscope(const float gyroscopeValue[AXIS]);
    void updateMagnetometer(const float magnetometerValue[AXIS]);

private:
    OneDimensionPlotData xAxisData;
    ThreeDimensionsPlotData accelerometerData;
    ThreeDimensionsPlotData gyroscopeData;
    ThreeDimensionsPlotData magnetometerData;

    QObject * parent;

    QCustomPlot *accelerometerPlot;
    QCustomPlot *gyroscopePlot;
    QCustomPlot *magnetometerPlot;
};

#endif
