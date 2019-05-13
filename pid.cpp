#include "pid.h"
#include <algorithm>

PID::PID(double p, double i, double d, double inputMin, double inputMax, double outputMin, double outputMax, bool continuous, double timeStep):
    p(p), i(i), d(d), inputMin(inputMin), inputMax(inputMax),
    outputMin(outputMin), outputMax(outputMax),
    continuous(continuous), derivativeOnInput(false), timeStep(timeStep)
{
    initialize(0.0, 0.0);
}

PID::~PID()
{
}

void PID::initialize(double input, double output)
{
    iTerm = output;
    prevInput = input;
    prevError = 0.0;
}

std::tuple<double, double, double, double> PID::calculateOutput(double input, double setpoint)
{
    double error = setpoint - input;
    if(continuous)
        error = calculateContinuousError(error);

    iTerm += i * error;

    double derivative;
    if(derivativeOnInput)
    {
        double deltaInput = calculateContinuousError(input - prevInput);
        derivative = -deltaInput;
    } else {
        derivative = (error - prevError);
    }

    prevInput = input;
    prevError = error;

    double output = p * error + iTerm + d * derivative;
    if (output > outputMax && iTerm > outputMax) {
        iTerm -= output - outputMax;
    } else if (output < outputMin && iTerm < outputMin) {
        iTerm += outputMin - output;
    }
    iTerm = std::min(iTerm, outputMax);
    iTerm = std::max(iTerm, outputMin);
    output = std::min(output, outputMax);
    output = std::max(output, outputMin);

    return std::tuple<double, double, double, double> (output, p * error, iTerm, d * derivative);
}

void PID::setP(double p)
{
    this->p = p;
}

void PID::setI(double i)
{
    this->i = i * timeStep;
}

void PID::setD(double d)
{
    this->d = d / timeStep;
}

double PID::getP()
{
    return p;
}

double PID::getI()
{
    return i / timeStep;
}

double PID::getD()
{
    return d * timeStep;
}

void PID::setTimeStep(double t)
{
    double ratio = t / timeStep;

    i *= ratio;
    d /= ratio;
    timeStep = t;
}

void PID::setContinuous(bool continuous)
{
    this->continuous = continuous;
}

void PID::setDerivativeOnInput(bool on)
{
    derivativeOnInput = on;
}

double PID::calculateContinuousError(double error)
{
    const double inputSize = inputMax - inputMin;
    const double sign = double(0.0 < error) - double(error < 0.0);
    if(std::abs(error) > (inputSize * 0.5))
    {
        return error - sign * inputSize;
    }
    return error;
}
