#include <QApplication>
#include <QPushButton>
#include "window.h"
constexpr int kSizeWindow = 1600;


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    auto* window = new Window();
    window->setWindowTitle("Ханойские башни");
    window->resize(kSizeWindow, kSizeWindow);
    window->show();
    return a.exec();
}
