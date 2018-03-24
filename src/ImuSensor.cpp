#include "ImuSensor.h"
#include "PlottingHelpers.h"

ImuSensor::ImuSensor(
    QObject *parent,
    QCustomPlot *accelerometerPlot,
    QCustomPlot *gyroscopePlot,
    QCustomPlot *magnetometerPlot)
        : parent(parent)
        , accelerometerPlot(accelerometerPlot)
        , gyroscopePlot(gyroscopePlot)
        , magnetometerPlot(magnetometerPlot)
{
    xAxisData = QVector<double>(FREQUENCY, 0.0);
    std::iota(xAxisData.begin(), xAxisData.end(), 0);

    reset();
}


void ImuSensor::updateAccelerometer(const float accelerometerValue[AXIS])
{
    updatePlot3Lines(accelerometerPlot, xAxisData, accelerometerData, accelerometerValue);
}

void ImuSensor::updateGyroscope(const float gyroscopeValue[AXIS])
{
    updatePlot3Lines(gyroscopePlot, xAxisData, gyroscopeData, gyroscopeValue);
}

void ImuSensor::updateMagnetometer(const float magnetometerValue[AXIS])
{
    updatePlot3Lines(magnetometerPlot, xAxisData, magnetometerData, magnetometerValue);
}

void ImuSensor::reset()
{
    resetPlot(accelerometerPlot, xAxisData, accelerometerData, {-20.0, 20.0});
    resetPlot(gyroscopePlot, xAxisData, gyroscopeData, {-10.0, 10.0});
    resetPlot(magnetometerPlot, xAxisData, magnetometerData, {-150.0, 150.0});
}

