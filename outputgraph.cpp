#include "outputgraph.h"

#include <qwt_scale_engine.h>

OutputGraph::OutputGraph(QwtPlot *plot, QWidget *parent):
    Graph(plot, parent, "Output Breakdown")
{
    outputIndex = addSeries("Output", QPen(Qt::black, 4));
    pIndex = addSeries("Proportional", QPen(Qt::red, 4));
    iIndex = addSeries("Integral", QPen(Qt::green, 4));
    dIndex = addSeries("Derivative", QPen(Qt::blue, 4));

    QwtScaleEngine *scaler = plot->axisScaleEngine(QwtPlot::yLeft);
    scaler->setReference(0.0);
    scaler->setAttribute(QwtScaleEngine::Symmetric, true);
}

void OutputGraph::update(double output, double p, double i, double d)
{
    addValue(pIndex, p);
    addValue(iIndex, i);
    addValue(dIndex, d);
    addValue(outputIndex, output);
    refresh();
}
