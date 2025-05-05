#include "window.h"

Window::Window() {
    dirCount_ = 0;
    fileCount_ = 0;
    directory_ = "";

    QString button_style = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 11px;
            margin: 5px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
        QPushButton:pressed {
            background-color: #d0d0d0;
            color: #333333;
        }
    )";

    QString text_style = R"(
        font-size: 14px;
        color: #FFFFFF;
    )";

    auto* open_button = new QPushButton("Выбрать директорию", this);
    open_button->setFixedSize(kButtonWidth, kButtonHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::DirectoryOpen);

    auto* tree_button =
        new QPushButton("Построить дерево папок и файлов", this);
    tree_button->setFixedSize(kButtonWidth, kButtonHeigth);
    tree_button->setStyleSheet(button_style);
    connect(tree_button, &QPushButton::clicked, this, &Window::TreeExecute);

    auto* recurse_start_button =
        new QPushButton("Начать рекурсивный подсчет", this);
    recurse_start_button->setFixedSize(kButtonWidth, kButtonHeigth);
    recurse_start_button->setStyleSheet(button_style);
    connect(recurse_start_button, &QPushButton::clicked, this,
            &Window::RecursionExecute);

    label_directory_ = new QLabel(this);
    label_directory_->setText("Директория: ");
    label_directory_->setStyleSheet(text_style);

    label_recursion_ = new QLabel(this);
    label_recursion_->setText("Кол-во подпапок: ");
    label_recursion_->setStyleSheet(text_style);

    label_file_ = new QLabel(this);
    label_file_->setText("Кол-во файлов: ");
    label_file_->setStyleSheet(text_style);

    tree_ = new QTreeWidget(this);
    tree_->setStyleSheet(text_style);
    tree_->setHeaderLabel("Дерево подпапок");

    auto* top_layout = new QHBoxLayout();
    top_layout->addWidget(open_button);
    top_layout->addWidget(tree_button);
    top_layout->addWidget(recurse_start_button);
    top_layout->addWidget(label_recursion_);
    top_layout->addWidget(label_file_);

    auto* main_layout = new QVBoxLayout();
    main_layout->addLayout(top_layout);
    main_layout->addWidget(label_directory_);
    main_layout->addWidget(tree_);
    setLayout(main_layout);
}

void Window::DirectoryOpen() {
    QString new_directory = QFileDialog::getExistingDirectory(
        this, "Выберите директорию", "",
        QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);
    if (!new_directory.isEmpty()) {
        directory_ = new_directory;
        label_directory_->setText("Директория: " + directory_);
        dirCount_ = 0;
        fileCount_ = 0;
        setNumbers();
    }
}

void Window::RecursionExecute() {
    if (!directory_.isEmpty()) {
        dirCount_ = 0;
        fileCount_ = 0;
        setNumbers();
        RecursionFolder(directory_);
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите директорию!");
    }
}

void Window::RecursionFolder(const QString& path) {
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |
                                           QDir::NoDotAndDotDot | QDir::Hidden);


    foreach (QFileInfo file_info, list) {
        if (file_info.isDir()) {
            dirCount_++;
            RecursionFolder(file_info.absoluteFilePath());
        } else if (file_info.isFile()) {
            fileCount_++;
        }
    }
    setNumbers();
}

void Window::setNumbers() {
    label_recursion_->setText("Кол-во подпапок: " + QString::number(dirCount_));
    label_file_->setText("Кол-во файлов: " + QString::number(fileCount_));
}

void Window::TreeExecute() {
    if (!directory_.isEmpty()) {
        tree_->clear();
        setTree(directory_, nullptr);
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите директорию!");
    }
}

void Window::setTree(const QString& path, QTreeWidgetItem* parentItem) {
    QDir dir(path);
    QFileInfoList entries = dir.entryInfoList(
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files | QDir::Hidden);


    for (const QFileInfo& entry : entries) {
        if (entry.isDir()) {
            auto* subfolder_item = new QTreeWidgetItem(
                (parentItem != nullptr) ? parentItem
                                        : tree_->invisibleRootItem());
            subfolder_item->setText(0, entry.fileName());
            setTree(entry.filePath(), subfolder_item);
        } else if (entry.isFile()) {
            auto* file_item = new QTreeWidgetItem(
                (parentItem != nullptr) ? parentItem
                                        : tree_->invisibleRootItem());
            file_item->setText(0, entry.fileName());
        }
    }
}
