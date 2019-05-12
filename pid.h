#ifndef PID_H
#define PID_H


class PID
{
public:
    PID(double p, double i, double d, double inputMin, double inputMax, bool continuous, double timeStep);

    void initialize(double input, double output);
    double calculateOutput(double intput, double setpoint);

    void setP(double p);
    void setI(double p);
    void setD(double p);

    double getP();
    double getI();
    double getD();

    void setTimeStep(double t);

    void setContinuous(bool continuous);
    void setDerivativeOnInput(bool on);
private:
    double calculateContinuousError(double error);
    double p = 0.0, i = 0.0, d = 0.0;
    const double inputMin, inputMax;
    const double outputMin, outputMax;

    bool continuous, derivativeOnInput;

    double iTerm;
    double timeStep;
    double prevInput;
    double prevError;
};

#endif // PID_H
