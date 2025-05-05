#ifndef TOWER_H
#define TOWER_H

#include <QPainter>
#include <QPair>
#include <QVector>
#include <QWidget>
constexpr int kTowersWidth = 400;
constexpr int kTowersHeigth = 700;
constexpr int kHeigthDisk = 20;
constexpr int kLeftMargin = 150;
constexpr int kGap = 250;
constexpr int kTowerWidth = 10;
constexpr int kTowerHeigth = 400;


class TowersWidget : public QWidget {
   public:
    TowersWidget(QWidget* parent = nullptr);

    void addDisk(int tower, int width);			// Addind disk to the tower
    void moveDisk(int fromTower, int toTower);	// Moving disk
    void clearDisks();	// clearing all disk when finished

   protected:
    void paintEvent(QPaintEvent* event) override;

   private:
    QVector<QVector<int>> towers_;	// contains disks at every tower
};

#endif	// TOWER_H
