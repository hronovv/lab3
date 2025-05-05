#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <sstream>
#include "QButtonGroup"
#include "QComboBox"
#include "QInputDialog"
#include "QLabel"
#include "QMessageBox"
#include "QRadioButton"
#include "QString"
#include "bits/stdc++.h"
#include "hanoi.h"
#include "hanoitext.h"
#include "tower.h"
constexpr int kButtonWidth = 300;
constexpr int kFieldWidth = 300;
constexpr int kButtonHeigth = 60;
constexpr int kFieldHeigth = 600;
constexpr int kTowerWidgetWidth = 1000;
constexpr int kTowerWidgetHeigth = 600;
constexpr int kVerticalLayoutSpacing = 5;
constexpr int kHorisontalLayoutSpacing = 50;
constexpr int kFive = 5;
constexpr int kTimerMs = 800;
constexpr int kDiskHeigth = 20;

class Window : public QWidget {
    Q_OBJECT

   public:
    Window();
    void HanoiOpen();
    void Start();
    void moveDisk();

   private:
    QTimer* timer_;
    QTextEdit* field_;
    QVector<QPair<int, int>> moves_;
    TowersWidget* towersWidget_;
    QButtonGroup* buttonGroup_;
    int currentMove_;
    int disk_number_;
    int i_, k_;
};

#endif	//WINDOW_H
