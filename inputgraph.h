#ifndef INPUTGRAPH_H
#define INPUTGRAPH_H

#include "graph.h"

class InputGraph : public Graph
{
    Q_OBJECT
public:
    InputGraph(QwtPlot *plot, QWidget *parent);

public slots:
    void update(double sp, double input);

private:
    unsigned long long spIndex, posIndex;
};

#endif // INPUTGRAPH_H
