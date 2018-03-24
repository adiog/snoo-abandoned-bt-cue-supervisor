#ifndef LIVEPLOT_H
#define LIVEPLOT_H

#include "protocol.h"
#include <qcustomplot.h>
#include <QTextEdit>
#include <QTimer>
#include <QVector>


class LivePlot
{
public:
    using OneDimensionPlotData = QVector<double>;
    using ThreeDimensionsPlotData = std::array<OneDimensionPlotData, AXIS>;

    LivePlot(
        QObject *parent,
        QCustomPlot *livePlot);

    void reset();

    void update(const float plotValue[AXIS]);

private:
    OneDimensionPlotData xAxisData;
    ThreeDimensionsPlotData plotData;

    QObject *parent;

    QCustomPlot *plotWidget;
};

#endif
