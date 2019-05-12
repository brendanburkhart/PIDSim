#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sine.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void timerEvent(QTimerEvent *);
public slots:
    void setP(double p);
    void setI(double i);
    void setD(double d);

    void switchModel(int model);

signals:
    void modelEnabled();

private:
    Ui::MainWindow *ui;
    Sine *sinePlot;
    Sine *sinePlot2;
};

#endif // MAINWINDOW_H
