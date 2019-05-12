#ifndef ANGULARSIM_H
#define ANGULARSIM_H

#include "model.h"
#include "pid.h"
#include "math.h"

#include <QWidget>

class AngularSim : public Model
{
    Q_OBJECT
public:
    AngularSim(QWidget *parent);
    void updateModel() override;

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

private:
    double angle = 0.5 * M_PI;
    double velocity = 0.0;
    double friction = 20;

    double setpoint = 1.5 * M_PI;
};
#endif // ANGULARSIM_H
