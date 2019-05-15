#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QFont font = app.font();
    font.setPointSize(12);
    app.setFont(font);

    MainWindow window;
    window.showMaximized();

    return app.exec();
}
