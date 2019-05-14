#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include <QWidget>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_abstract_legend.h>

class GraphController : public QWidget
{
    Q_OBJECT
public:
    GraphController(QwtPlot *plot, QWidget *parent, QString title);
    ~GraphController();

    unsigned long long addSeries(QString name, QPen pen);
    void addValue(unsigned long long series, double value);
    void refresh();
    void modelEnabled(double yMin, double yMax);

protected:
    QwtAbstractLegend *legend;

public slots:
    void clear();

private:
    QwtPlot *plot;
    std::vector<std::tuple<QVector<double>, QVector<double>, QwtPlotCurve*>> series;
    static const int maxSize = 100;
};

#endif // GRAPHCONTROLLER_H
