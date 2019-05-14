#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputgraph.h"
#include "outputgraph.h"

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

private:
    Ui::MainWindow *ui;
    InputGraph *inputGraph;
    OutputGraph *outputGraph;

    static const int ANGULAR = 0;
    static const int LINEAR = 1;
};

#endif // MAINWINDOW_H
