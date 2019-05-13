#ifndef LINEARSIM_H
#define LINEARSIM_H

#include "model.h"
#include "pid.h"

#include <QWidget>

class LinearSim : public Model
{
    Q_OBJECT
public:
    LinearSim(QWidget *parent);
    void updateModel() override;
    std::pair<double, double> inputRange() override;
    std::pair<double, double> outputRange() override;

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

public slots:
    void reset() override;

private:
    double position = 0;
    double velocity = 0.0;
    double gravity = 20;

    double setpoint = 75;
};

#endif // LINEARSIM_H
