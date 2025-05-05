#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <sstream>
#include "QComboBox"
#include "QInputDialog"
#include "QMessageBox"
#include "QString"
#include "binaryconvertion.h"
constexpr double kMaxNumber = 2147483647;
constexpr short kAfterPointNumbers = 10;
constexpr short kWidth = 800;
constexpr short kHeigth = 100;

class Window : public QWidget {
    Q_OBJECT

   public:
    Window();
    void BinaryOpen();
};

#endif	//WINDOW_H
