#include "PlottingHelpers.h"

const QColor color[AXIS] = {Qt::red, Qt::green, Qt::blue};

void resetPlot(QCustomPlot *plot, OneDimensionPlotData &xAxisData, ThreeDimensionsPlotData &plotData, std::pair<double, double> yAxisRange)
{
    plot->xAxis->setRange(0, FREQUENCY);
    plot->yAxis->setRange(yAxisRange.first, yAxisRange.second);

    for (auto axis : THREE_AXIS)
    {
        plotData[axis] = QVector<double>(FREQUENCY, 0.0);
        plot->addGraph();
        plot->graph(axis)->setPen(QPen(color[axis]));
        plot->graph(axis)->setData(xAxisData, plotData[axis]);
    }

    plot->replot();
}

void updatePlot3Lines(QCustomPlot *plot, OneDimensionPlotData &xAxisData, ThreeDimensionsPlotData &plotData, const float inputData[AXIS])
{
    for (auto axis : THREE_AXIS)
    {
        plotData[axis][0] = (double)inputData[axis];
        std::rotate(plotData[axis].begin(), plotData[axis].begin() + 1, plotData[axis].end());
        plot->graph(axis)->setData(xAxisData, plotData[axis]);
    }
    plot->replot();
}
