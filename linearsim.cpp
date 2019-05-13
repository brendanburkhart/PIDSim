#include "linearsim.h"
#include "math.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

LinearSim::LinearSim(QWidget *parent): Model(parent)
{
    pid = new PID(0.0, 0.0, 0.0, -100.0, 100.0, -200.0, 200.0, false, timeStep);
    pid->setDerivativeOnInput(true);
}

void LinearSim::updateModel()
{
    std::tuple<double, double, double, double> output = pid->calculateOutput(position, setpoint);

    emit outputUpdated(std::get<0>(output), std::get<1>(output), std::get<2>(output), std::get<3>(output));

    //double sign = (0.0 < velocity) - (velocity < 0.0);
    //double air_resistance = sign * velocity * velocity;
    velocity -= gravity * timeStep;
    velocity += std::get<0>(output) * timeStep;
    position += velocity * timeStep;

    emit modelUpdated(setpoint, position);

    repaint();
}

std::pair<double, double> LinearSim::inputRange()
{
    int side = qMin(width(), height());
    double h = height() * 200.0 / side;
    return std::pair<double, double>(-0.5 * h, 0.5 * h);
}


std::pair<double, double> LinearSim::outputRange()
{
    return std::pair<double, double>(-200, 200);
}

void LinearSim::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QColor barColor(230, 60, 0);
    QColor spColor(0, 50, 220);

    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width() * 0.5, height() * 0.5);

    int side = qMin(width(), height());
    p.scale(side / 200.0, side / 200.0);

    p.setPen(Qt::NoPen);

    int w = int(width() * 200.0 / side);
    // int h = int(height() * 200.0 / side);

    p.setBrush(barColor);
    p.drawRect(-50, -int(position + 10), 100, 20);

    p.setBrush(Qt::NoBrush);
    p.setPen(QPen(spColor, 1));
    p.drawLine(-int(w/3), -int(setpoint), int(w/3), -int(setpoint));
}

void LinearSim::reset()
{
    setpoint = 75;
    position= 0.0;
    velocity = 0.0;
    pid->initialize(position, 0.0);
}

void LinearSim::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        int side = qMin(width(), height());
        int h = int(height() * 200.0 / side);
        setpoint = double(e->y() * 200.0 / side) * -1 + 0.5 * h;
    }
}
