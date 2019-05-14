#include "graphcontroller.h"
#include <algorithm>

GraphController::GraphController(QwtPlot *plot, QWidget *parent, QString title):
    plot(plot)
{
    setParent(parent);
    plot->setTitle(title);
    plot->setAxisScale(QwtPlot::xBottom, 0, maxSize);

    legend = plot->legend();

    plot->show();
}

GraphController::~GraphController()
{
}

unsigned long long GraphController::addSeries(QString name, QPen pen)
{
    QwtPlotCurve *curve = new QwtPlotCurve();

    QVector<double> data;
    QVector<double> axis;
    curve->setSamples(axis, data);
    curve->attach(plot);

    curve->setPen(pen);

    curve->setTitle(name);

    series.push_back(std::tuple<QVector<double>, QVector<double>, QwtPlotCurve*>(axis, data, curve));

    return series.size() - 1;
}

void GraphController::addValue(unsigned long long seriesIndex, double value) {
    auto &curve = series.at(seriesIndex);
    auto &xData = std::get<0>(curve);
    int size = xData.size();

    if(size == 0) {
        xData.push_back(0.0);
        std::get<1>(curve).push_back(value);
    } else {
        double x = xData.at(size - 1);

        if(size >= maxSize) {
            std::rotate(std::get<1>(curve).begin(), std::get<1>(curve).begin() + 1, std::get<1>(curve).end());
            std::get<1>(curve).replace(size - 1, value);
        } else {
            xData.push_back(x + 1);
            std::get<1>(curve).push_back(value);
        }
    }
}

void GraphController::clear() {
    for (auto &curve : series) {
        std::get<0>(curve).clear();
        std::get<1>(curve).clear();
        std::get<2>(curve)->setSamples(std::get<0>(curve), std::get<1>(curve));
    }
    plot->replot();
}

void GraphController::refresh() {
    for (auto &curve : series) {
        std::get<2>(curve)->setSamples(std::get<0>(curve), std::get<1>(curve));
    }
    plot->replot();
}

void GraphController::modelEnabled(double yMin, double yMax) {
    plot->setAxisScale(QwtPlot::yLeft, yMin, yMax);
    clear();
}
