#ifndef PLOTTINGHELPERS_H
#define PLOTTINGHELPERS_H

#include "protocol.h"
#include <qcustomplot.h>
#include <QVector>

using OneDimensionPlotData = QVector<double>;
using ThreeDimensionsPlotData = std::array<OneDimensionPlotData, AXIS>;


void resetPlot(QCustomPlot *plot, OneDimensionPlotData &xAxisData, ThreeDimensionsPlotData &plotData, std::pair<double, double> yAxisRange);
void updatePlot3Lines(QCustomPlot *plot, OneDimensionPlotData &xAxisData, ThreeDimensionsPlotData &plotData, const float inputData[AXIS]);

#endif
