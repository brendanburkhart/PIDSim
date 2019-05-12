#ifndef SINE_H
#define SINE_H

#include <QWidget>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class Sine : public QWidget
{
    Q_OBJECT
public:
    Sine(QwtPlot *plot, QWidget *parent, Qt::WindowFlags wFlags = nullptr);
    ~Sine();
    void timerEvent(QTimerEvent *);
private:
    QwtPlot *plot;
    QwtPlotCurve *curve;

    int x = 0;

    static const int dataSize = 100;
    double xData[dataSize];
    double yData[dataSize];
};

#endif // SINE_H
