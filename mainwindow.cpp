#include "linearsim.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sinePlot = new Sine(ui->qwtPlot, ui->qwtPlot);
    sinePlot->startTimer(20);

    sinePlot2 = new Sine(ui->qwtPlot_2, ui->qwtPlot_2);
    sinePlot2->startTimer(10);

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

    ui->linearSim->setSampleTime(0.02);
    ui->angularSim->setSampleTime(0.02);

    ui->modelComboBox->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);

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
    switch(model) {
    case 0:
        ui->pSpinBox->setValue(ui->linearSim->getP());
        ui->iSpinBox->setValue(ui->linearSim->getI());
        ui->dSpinBox->setValue(ui->linearSim->getD());
        break;
    case 1:
        ui->pSpinBox->setValue(ui->angularSim->getP());
        ui->iSpinBox->setValue(ui->angularSim->getI());
        ui->dSpinBox->setValue(ui->angularSim->getD());
        break;
    }
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



