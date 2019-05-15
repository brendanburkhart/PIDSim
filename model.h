#ifndef MODEL_H
#define MODEL_H

#include "pid.h"

#include <QWidget>

class Model : public QWidget
{
    Q_OBJECT
public:
    explicit Model(QWidget *parent);
    ~Model() override;

    void setSampleTime(double t);

    virtual void updateModel() = 0;

    double getP();
    double getI();
    double getD();

    double getFeedforward();

    virtual std::pair<double, double> inputRange() = 0;
    virtual std::pair<double, double> outputRange() = 0;

    void enableFriction(bool enabled);

public slots:
    void setP(double p);
    void setI(double i);
    void setD(double d);

    void setFeedforward(double f);

    virtual void reset() = 0;

signals:
    void modelUpdated(double sp, double input);
    void outputUpdated(double output, double p, double i, double d, double f);

protected:
    double timeStep = 0.02;
    bool frictionEnabled = false;
    PID *pid;
};

#endif // MODEL_H
