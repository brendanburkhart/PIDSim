#include "mainwindow.h"

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QRect display = QGuiApplication::primaryScreen()->availableGeometry();
    MainWindow window;

    int width = int(display.width() * 0.6);
    int height = int(display.height() * 0.8);
    window.setGeometry(int(display.x() * 0.5 - width * 0.5), int(display.y() * 0.5 - height * 0.5), width, height);
    window.showMaximized();

    return app.exec();
}
