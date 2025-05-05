#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QFileInfoList>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
constexpr int kSizeWindow = 1600;
constexpr int kButtonWidth = 250;
constexpr int kButtonHeigth = 55;

class Window : public QWidget {
    Q_OBJECT
   public:
    Window();

    void DirectoryOpen();

    void RecursionExecute();

    void RecursionFolder(const QString& path);

    void TreeExecute();

    void setNumbers();

    void setTree(const QString& folderPath, QTreeWidgetItem* parentItem);

   private:
    QLabel* label_directory_;
    QLabel* label_recursion_;
    QLabel* label_file_;
    QTreeWidget* tree_;
    QString directory_;
    int dirCount_, fileCount_;
};

#endif	// WINDOW_H
