#include "sine.h"
#include "math.h"

#include <algorithm>

Sine::Sine(QwtPlot *plot, QWidget *parent, Qt::WindowFlags wFlags):
    plot(plot)
{
    setParent(parent, wFlags);
    for(int i = 0; i < dataSize; i++) {
        xData[i] = i;
        yData[i] = sin(M_PI * i/50.0);
    }

    curve = new QwtPlotCurve();
    curve->setSamples(xData, yData, dataSize);
    curve->attach(plot);

    QPen blue(Qt::blue);
    blue.setWidth(4);
    curve->setPen(blue);

    plot->setAxisScale(plot->xBottom, 0, dataSize);

    plot->replot();
    plot->show();
}

Sine::~Sine()
{
}

void Sine::timerEvent(QTimerEvent *) {
    double y = sin(M_PI * x/50.0);
    x = (x + 1) % dataSize;

    std::rotate(yData, yData+1, yData + dataSize);
    yData[dataSize - 1] = y;

    curve->setSamples(xData, yData, dataSize);
    plot->replot();
}
