#include "linearsim.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inputGraph = new InputGraph(ui->inputPlot, ui->inputPlot);
    outputGraph = new OutputGraph(ui->outputPlot, ui->outputPlot);

    QObject::connect(ui->pSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setP(double)));
    QObject::connect(ui->iSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setI(double)));
    QObject::connect(ui->dSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setD(double)));
    QObject::connect(ui->fSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setF(double)));

    QObject::connect(ui->modelComboBox, SIGNAL(currentIndexChanged(int)),
                ui->modelStackWidget, SLOT(setCurrentIndex(int)));
    QObject::connect(ui->modelComboBox, SIGNAL(currentIndexChanged(int)),
                this, SLOT(switchModel(int)));

    QObject::connect(ui->linearSim, SIGNAL(modelUpdated(double, double)),
                inputGraph, SLOT(update(double, double)));
    QObject::connect(ui->angularSim, SIGNAL(modelUpdated(double, double)),
                inputGraph, SLOT(update(double, double)));

    QObject::connect(ui->linearSim, SIGNAL(outputUpdated(double, double, double, double, double)),
                outputGraph, SLOT(update(double, double, double, double, double)));
    QObject::connect(ui->angularSim, SIGNAL(outputUpdated(double, double, double, double, double)),
                outputGraph, SLOT(update(double, double, double, double, double)));

    QObject::connect(ui->resetButton, SIGNAL(clicked()), ui->linearSim, SLOT(reset()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), ui->angularSim, SLOT(reset()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), inputGraph, SLOT(clear()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), outputGraph, SLOT(clear()));

    QObject::connect(ui->frictionCheckBox, SIGNAL(clicked(bool)), this, SLOT(enableFriction(bool)));

    ui->linearSim->setSampleTime(0.02);
    ui->angularSim->setSampleTime(0.02);

    ui->modelComboBox->setCurrentIndex(ANGULAR);
    ui->modelStackWidget->setCurrentIndex(ANGULAR);

    std::pair<double, double> range = ui->angularSim->inputRange();
    inputGraph->modelEnabled(range.first, range.second);

    startTimer(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    switch (ui->modelComboBox->currentIndex()) {
    case LINEAR:
        ui->linearSim->updateModel();
        break;
    case ANGULAR:
        ui->angularSim->updateModel();
        break;
    }
}

void MainWindow::switchModel(int model)
{
    std::pair<double, double> inputRange;

    switch(model) {
    case LINEAR:
        ui->pSpinBox->setValue(ui->linearSim->getP());
        ui->iSpinBox->setValue(ui->linearSim->getI());
        ui->dSpinBox->setValue(ui->linearSim->getD());
        ui->fSpinBox->setValue(ui->linearSim->getFeedforward());
        inputRange = ui->linearSim->inputRange();
        break;
    case ANGULAR:
        ui->pSpinBox->setValue(ui->angularSim->getP());
        ui->iSpinBox->setValue(ui->angularSim->getI());
        ui->dSpinBox->setValue(ui->angularSim->getD());
        ui->fSpinBox->setValue(ui->angularSim->getFeedforward());
        inputRange = ui->angularSim->inputRange();
        break;
    default:
        inputRange = std::pair<double, double>(-1.0, 1.0);
    }
    inputGraph->modelEnabled(inputRange.first, inputRange.second);
}

void MainWindow::setP(double p)
{
    switch (ui->modelComboBox->currentIndex()) {
    case LINEAR:
        ui->linearSim->setP(p);
        break;
    case ANGULAR:
        ui->angularSim->setP(p);
        break;
    }
}

void MainWindow::setI(double i)
{
    switch (ui->modelComboBox->currentIndex()) {
    case LINEAR:
        ui->linearSim->setI(i);
        break;
    case ANGULAR:
        ui->angularSim->setI(i);
        break;
    }
}

void MainWindow::setD(double d)
{
    switch (ui->modelComboBox->currentIndex()) {
    case LINEAR:
        ui->linearSim->setD(d);
        break;
    case ANGULAR:
        ui->angularSim->setD(d);
        break;
    }
}

void MainWindow::setF(double f)
{
    switch (ui->modelComboBox->currentIndex()) {
    case LINEAR:
        ui->linearSim->setFeedforward(f);
        break;
    case ANGULAR:
        ui->angularSim->setFeedforward(f);
        break;
    }
}

void MainWindow::enableFriction(bool enabled)
{
    switch (ui->modelComboBox->currentIndex()) {
    case LINEAR:
        ui->linearSim->enableFriction(enabled);
        break;
    case ANGULAR:
        ui->angularSim->enableFriction(enabled);
        break;
    }
}
