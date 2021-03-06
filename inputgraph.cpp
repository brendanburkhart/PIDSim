#include "inputgraph.h"

InputGraph::InputGraph(QwtPlot *plot, QWidget *parent):
    GraphController(plot, parent, "Input and Setpoint")
{
    spIndex = addSeries("Setpoint", QPen(Qt::green, 4));
    posIndex = addSeries("Position", QPen(Qt::blue, 4));
}

void InputGraph::update(double sp, double input)
{
    addValue(spIndex, sp);
    addValue(posIndex, input);
    refresh();
}
