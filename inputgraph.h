#ifndef INPUTGRAPH_H
#define INPUTGRAPH_H

#include "graphcontroller.h"

class InputGraph : public GraphController
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
