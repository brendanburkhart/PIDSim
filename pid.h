#ifndef PID_H
#define PID_H

#include <tuple>

class PID
{
public:
    PID(double p, double i, double d, double inputMin, double inputMax, double outputMin, double outputMax, bool continuous, double timeStep);
    virtual ~PID();

    void initialize(double input, double output);
    std::tuple<double, double, double, double, double> calculateOutput(double intput, double setpoint);

    void setP(double p);
    void setI(double p);
    void setD(double p);
    void setFeedforward(double f);

    double getP();
    double getI();
    double getD();
    double getFeedforward();

    void setTimeStep(double t);

    void setContinuous(bool continuous);
    void setDerivativeOnInput(bool on);

private:
    double calculateContinuousError(double error);
    double p = 0.0, i = 0.0, d = 0.0;
    const double inputMin, inputMax;
    const double outputMin, outputMax;

    double feedforward;

    bool continuous, derivativeOnInput;

    double iTerm;
    double timeStep;
    double prevInput;
    double prevError;
};

#endif // PID_H
