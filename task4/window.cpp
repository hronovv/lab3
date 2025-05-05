#include "window.h"

Window::Window() {
    disk_number_ = 0;
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Window::moveDisk);
    QString button_style = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 12px;
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

    QString text_edit_style = R"(
        font-size: 14px;
        background-color: #f9f9f9;
        color: #000000;
        border: 2px solid #000000; /* Черная рамка */
        border-radius: 5px; /* Немного закругленные углы */
    )";

    QString text_style = R"(
        font-size: 14px;
        color: #FFFFFF;
    )";

    auto* open_button = new QPushButton("Ввести количество дисков: ", this);
    open_button->setFixedSize(kButtonWidth, kButtonHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::HanoiOpen);

    auto* start_button = new QPushButton("Старт", this);
    start_button->setFixedSize(kButtonWidth, kButtonHeigth);
    start_button->setStyleSheet(button_style);
    connect(start_button, &QPushButton::clicked, this, &Window::Start);

    field_ = new QTextEdit(this);
    field_->setFixedSize(kFieldWidth, kFieldHeigth);
    field_->setStyleSheet(text_edit_style);
    field_->setReadOnly(true);

    towersWidget_ = new TowersWidget(this);
    towersWidget_->setFixedSize(kTowerWidgetWidth, kTowerWidgetHeigth);

    auto* rb1 = new QRadioButton("1 -> 2", this);
    auto* rb2 = new QRadioButton("1 -> 3", this);
    auto* rb3 = new QRadioButton("2 -> 1", this);
    auto* rb4 = new QRadioButton("2 -> 3", this);
    auto* rb5 = new QRadioButton("3 -> 1", this);
    auto* rb6 = new QRadioButton("3 -> 2", this);

    buttonGroup_ = new QButtonGroup(this);
    buttonGroup_->addButton(rb1, 0);
    buttonGroup_->addButton(rb2, 1);
    buttonGroup_->addButton(rb3, 2);
    buttonGroup_->addButton(rb4, 3);
    buttonGroup_->addButton(rb5, 4);
    buttonGroup_->addButton(rb6, kFive);

    auto* radio_layout = new QHBoxLayout();
    radio_layout->addWidget(rb1);
    radio_layout->addWidget(rb2);
    radio_layout->addWidget(rb3);
    radio_layout->addWidget(rb4);
    radio_layout->addWidget(rb5);
    radio_layout->addWidget(rb6);

    auto* vertical_layout = new QVBoxLayout();
    vertical_layout->setSpacing(kVerticalLayoutSpacing);
    vertical_layout->addWidget(open_button);
    vertical_layout->addWidget(start_button);
    vertical_layout->addLayout(radio_layout);
    vertical_layout->addWidget(field_);

    auto* horizontal_layout = new QHBoxLayout();
    horizontal_layout->setSpacing(kHorisontalLayoutSpacing);
    horizontal_layout->addLayout(vertical_layout);
    horizontal_layout->addWidget(towersWidget_);
    horizontal_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    setLayout(horizontal_layout);
}

void Window::HanoiOpen() {
    bool ok = false;
    QString number = QInputDialog::getText(
        nullptr, "", "Введите целое неотрицательное число(кол-во дисков):",
        QLineEdit::Normal, "", &ok);
    if (ok && !number.isEmpty()) {
        bool n_ok;
        disk_number_ = number.toInt(&n_ok);


        if (n_ok && disk_number_ > 0) {
            field_->clear();
        } else {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Введите целое неотрицательное число с учетом диапазона");
        }
    } else {
        QMessageBox::warning(nullptr, "Ошибка",
                             "Введите целое неотрицательное число");
    }
}

void Window::Start() {


    if (disk_number_ == 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Введите кол-во дисков");
        return;
    }

    if (buttonGroup_->checkedButton() == nullptr) {
        QMessageBox::warning(
            nullptr, "Ошибка",
            "Выберите, с какой башни на какую переместить диски");
        return;
    }

    // Определяем исходную и целевую башню
    if (buttonGroup_->button(0)->isChecked()) {	 // 1 -> 2
        i_ = 1;
        k_ = 2;
    } else if (buttonGroup_->button(1)->isChecked()) {	// 1 -> 3
        i_ = 1;
        k_ = 3;
    } else if (buttonGroup_->button(2)->isChecked()) {	// 2 -> 1
        i_ = 2;
        k_ = 1;
    } else if (buttonGroup_->button(3)->isChecked()) {	// 2 -> 3
        i_ = 2;
        k_ = 3;
    } else if (buttonGroup_->button(4)->isChecked()) {	// 3 -> 1
        i_ = 3;
        k_ = 1;
    } else if (buttonGroup_->button(kFive)->isChecked()) {	// 3 -> 2
        i_ = 3;
        k_ = 2;
    }

    field_->clear();
    HanoiText(disk_number_, i_, k_, field_);
    currentMove_ = 0;
    moves_.clear();
    Hanoi(disk_number_, i_, k_, moves_);

    towersWidget_->clearDisks();


    for (int d = 1; d <= disk_number_; ++d) {
        towersWidget_->addDisk(i_ - 1, (disk_number_ - d + 1) * kDiskHeigth);
    }


    timer_->start(kTimerMs);
}

void Window::moveDisk() {
    if (currentMove_ < moves_.size()) {
        auto move = moves_[currentMove_];
        towersWidget_->moveDisk(move.first - 1, move.second - 1);
        currentMove_++;
    } else {
        timer_->stop();
    }
}
