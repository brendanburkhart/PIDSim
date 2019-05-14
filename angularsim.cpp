#include "angularsim.h"
#include "math.h"
#include "utils.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

AngularSim::AngularSim(QWidget *parent): Model(parent)
{
    pid = new PID(0.0, 0.0, 0.0, 0.0, 2 * M_PI, -10, 10, true, timeStep);
    pid->setDerivativeOnInput(true);
}

void AngularSim::updateModel()
{
    std::tuple<double, double, double, double> output = pid->calculateOutput(angle, setpoint);

    emit outputUpdated(std::get<0>(output), std::get<1>(output), std::get<2>(output), std::get<3>(output));
    velocity += std::get<0>(output) * timeStep;
    angle += velocity * timeStep;
    angle = utils::modulus(angle, 2.0 * M_PI);

    emit modelUpdated(setpoint, angle);

    repaint();
}

std::pair<double, double> AngularSim::inputRange()
{
    return std::pair<double, double>(0.0, 2.0 * M_PI);
}

std::pair<double, double> AngularSim::outputRange()
{
    return std::pair<double, double>(-10, 10);
}

void AngularSim::reset()
{
    angle = 0.5 * M_PI;
    velocity = 0.0;
    setpoint = 1.5 * M_PI;
    pid->initialize(angle, 0.0);
}

void AngularSim::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QColor circleColor(250, 250, 250);
    QColor spColor(0, 50, 220);
    QColor angleColor(230, 60, 0);

    p.setRenderHint(QPainter::Antialiasing);
    p.translate(width() * 0.5, height() * 0.5);

    int side = qMin(width(), height());
    p.scale(side / 200.0, side / 200.0);

    p.setPen(Qt::NoPen);

    p.setBrush(circleColor);
    p.drawEllipse(-40, -40, 80, 80);

    p.setBrush(Qt::NoBrush);

    p.setPen(QPen(angleColor, 1));
    p.drawLine(0, 0, int(60.0 * std::cos(angle)), -int(60.0 * std::sin(angle)));

    p.setPen(QPen(spColor, 1));
    p.drawLine(0, 0, int(80.0 * std::cos(setpoint)), -int(80.0 * std::sin(setpoint)));
}

void AngularSim::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        int side = qMin(width(), height());
        int h = int(height() * 200.0 / side);
        int w = int(width() * 200.0 / side);
        int x = int((e->x() * 200.0 / side) - 0.5 * w);
        int y = int((e->y() * 200.0 / side) * -1 + 0.5 * h);
        setpoint = utils::modulus(std::atan2(y, x), 2.0 * M_PI);
    }
}
