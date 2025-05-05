#include <QApplication>
#include <QPushButton>
#include "window.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    auto* window = new Window();
    window->setWindowTitle("Рекурсивные директории");
    window->resize(kSizeWindow, kSizeWindow);
    window->show();
    return a.exec();
}
