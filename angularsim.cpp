#include "angularsim.h"
#include "math.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

AngularSim::AngularSim(QWidget *parent): Model(parent)
{
    pid = new PID(0.0, 0.0, 0.0, 0.0, 2 * M_PI, true, timeStep);
    pid->setDerivativeOnInput(true);
}

void AngularSim::updateModel()
{
    double output = pid->calculateOutput(angle, setpoint);

    //double sign = (0.0 < velocity) - (velocity < 0.0);
    //double air_resistance = sign * velocity * velocity;
    velocity += output * timeStep;
    angle += velocity * timeStep;
    angle = std::fmod(angle, 2 * M_PI);

    emit modelUpdated(setpoint, angle);

    repaint();
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
        setpoint = std::fmod(std::atan2(y, x) + 2 * M_PI, 2 * M_PI);
    }
}
