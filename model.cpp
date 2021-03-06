#include "model.h"

Model::Model(QWidget *parent) : QWidget(parent)
{
}

Model::~Model()
{
    delete pid;
}

void Model::setSampleTime(double t)
{
    timeStep = t;
    pid->setTimeStep(t);
}

void Model::setP(double p)
{
    pid->setP(p);
}

void Model::setI(double i)
{
    pid->setI(i);
}

void Model::setD(double d)
{
    pid->setD(d);
}

void Model::setFeedforward(double f)
{
    pid->setFeedforward(f);
}

double Model::getP()
{
    return pid->getP();
}

double Model::getI()
{
    return pid->getI();
}

double Model::getD()
{
    return pid->getD();
}

double Model::getFeedforward()
{
    return pid->getFeedforward();
}

void Model::enableFriction(bool enabled)
{
    frictionEnabled = enabled;
}
