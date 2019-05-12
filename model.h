#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include "pid.h"

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

public slots:
    void setP(double p);
    void setI(double i);
    void setD(double d);

signals:
    void modelUpdated(double sp, double pos);

protected:
    double timeStep = 0.02;
    PID *pid;
};

#endif // MODEL_H
