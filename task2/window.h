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
#include "QLabel"
#include "QMessageBox"
#include "QString"
#include "akkerman.h"
constexpr short kWidth = 800;
constexpr short kHeigth = 100;

class Window : public QWidget {
    Q_OBJECT

   public:
    Window();
    void AkkermanOpen();
};

#endif	//WINDOW_H
