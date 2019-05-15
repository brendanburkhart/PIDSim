#ifndef OUTPUTGRAPH_H
#define OUTPUTGRAPH_H

#include "graphcontroller.h"

class OutputGraph : public GraphController
{
    Q_OBJECT
public:
    OutputGraph(QwtPlot *plot, QWidget *parent);

public slots:
    void update(double output, double p, double i, double d, double f);

private:
    unsigned long long outputIndex, pIndex, iIndex, dIndex, fIndex;
};

#endif // OUTPUTGRAPH_H
