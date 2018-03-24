#include "LivePlot.h"
#include "PlottingHelpers.h"

LivePlot::LivePlot(
    QObject *parent,
    QCustomPlot *plotWidget)
        : parent(parent)
        , plotWidget(plotWidget)
{
    xAxisData = QVector<double>(FREQUENCY, 0.0);
    std::iota(xAxisData.begin(), xAxisData.end(), 0);

    reset();
}


void LivePlot::update(const float value[AXIS])
{
    updatePlot3Lines(plotWidget, xAxisData, plotData, value);
}

void LivePlot::reset()
{
    resetPlot(plotWidget, xAxisData, plotData, {-180.0, 180.0});
}

