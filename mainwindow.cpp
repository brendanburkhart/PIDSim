#include "linearsim.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inputGraph = new InputGraph(ui->qwtPlot, ui->qwtPlot);
    outputGraph = new OutputGraph(ui->qwtPlot_2, ui->qwtPlot_2);

    QObject::connect(ui->pSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setP(double)));
    QObject::connect(ui->iSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setI(double)));
    QObject::connect(ui->dSpinBox, SIGNAL(valueChanged(double)),
                         this, SLOT(setD(double)));

    QObject::connect(ui->modelComboBox, SIGNAL(currentIndexChanged(int)),
                ui->stackedWidget, SLOT(setCurrentIndex(int)));
    QObject::connect(ui->modelComboBox, SIGNAL(currentIndexChanged(int)),
                this, SLOT(switchModel(int)));

    QObject::connect(ui->linearSim, SIGNAL(modelUpdated(double, double)),
                inputGraph, SLOT(update(double, double)));
    QObject::connect(ui->angularSim, SIGNAL(modelUpdated(double, double)),
                inputGraph, SLOT(update(double, double)));

    QObject::connect(ui->linearSim, SIGNAL(outputUpdated(double, double, double, double)),
                outputGraph, SLOT(update(double, double, double, double)));
    QObject::connect(ui->angularSim, SIGNAL(outputUpdated(double, double, double, double)),
                outputGraph, SLOT(update(double, double, double, double)));

    QObject::connect(ui->resetButton, SIGNAL(clicked()), ui->linearSim, SLOT(reset()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), ui->angularSim, SLOT(reset()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), inputGraph, SLOT(clear()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), outputGraph, SLOT(clear()));

    ui->linearSim->setSampleTime(0.02);
    ui->angularSim->setSampleTime(0.02);

    ui->modelComboBox->setCurrentIndex(1);
    ui->stackedWidget->setCurrentIndex(1);

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
    case 0:
        ui->linearSim->updateModel();
        break;
    case 1:
        ui->angularSim->updateModel();
        break;
    }
}

void MainWindow::switchModel(int model)
{
    std::pair<double, double> inputRange;

    switch(model) {
    case 0:
        ui->pSpinBox->setValue(ui->linearSim->getP());
        ui->iSpinBox->setValue(ui->linearSim->getI());
        ui->dSpinBox->setValue(ui->linearSim->getD());
        inputRange = ui->linearSim->inputRange();
        break;
    case 1:
        ui->pSpinBox->setValue(ui->angularSim->getP());
        ui->iSpinBox->setValue(ui->angularSim->getI());
        ui->dSpinBox->setValue(ui->angularSim->getD());
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
    case 0:
        ui->linearSim->setP(p);
        break;
    case 1:
        ui->angularSim->setP(p);
        break;
    }
}

void MainWindow::setI(double i)
{
    switch (ui->modelComboBox->currentIndex()) {
    case 0:
        ui->linearSim->setI(i);
        break;
    case 1:
        ui->angularSim->setI(i);
        break;
    }
}

void MainWindow::setD(double d)
{
    switch (ui->modelComboBox->currentIndex()) {
    case 0:
        ui->linearSim->setD(d);
        break;
    case 1:
        ui->angularSim->setD(d);
        break;
    }
}



