#include "tower.h"

TowersWidget::TowersWidget(QWidget* parent) : QWidget(parent) {
    setFixedSize(kTowersWidth, kTowersWidth);
    towers_.resize(3);
}

void TowersWidget::addDisk(int tower, int width) {
    towers_[tower].append(width);
    update();
}

void TowersWidget::moveDisk(int fromTower, int toTower) {
    if (!towers_[fromTower].isEmpty()) {
        int disk = towers_[fromTower].takeLast();
        towers_[toTower].append(disk);
        update();
    }
}

void TowersWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QColor tower_color = Qt::yellow;
    int base_height = height();


    for (int i = 0; i < 3; ++i) {
        int x = kLeftMargin + (i * kGap) + (kTowerWidth * i);
        painter.setBrush(tower_color);
        painter.drawRect(x, base_height - kTowerHeigth, kTowerWidth,
                         kTowerHeigth);


        int current_disk_y = base_height + kHeigthDisk;
        for (int j = 0; j < towers_[i].size(); ++j) {
            int disk_width = towers_[i][j];
            int disk_height = kHeigthDisk;


            current_disk_y -= disk_height;
            int disk_x = x - (disk_width / 2) + (kTowerWidth / 2);

            painter.setBrush(Qt::blue);
            painter.drawRect(disk_x, current_disk_y - disk_height, disk_width,
                             disk_height);
        }
    }
}


void TowersWidget::clearDisks() {


    for (auto& tower : towers_) {
        tower.clear();
    }
    update();
}
