#ifndef ANGULARSIM_H
#define ANGULARSIM_H

#include "model.h"
#include "math.h"
#include "pid.h"

#include <QWidget>

class AngularSim : public Model
{
    Q_OBJECT
public:
    AngularSim(QWidget *parent);
    void updateModel() override;
    std::pair<double, double> inputRange() override;
    std::pair<double, double> outputRange() override;

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

public slots:
    void reset() override;

private:
    double angle = 0.5 * M_PI;
    double velocity = 0.0;
    double dynamic_friction = 1.5;
    double static_friction = 5.0;

    double setpoint = 1.5 * M_PI;
};
#endif // ANGULARSIM_H
