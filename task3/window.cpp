#include "window.h"

Window::Window() {
    QString button_style = R"(
        QPushButton {
            background-color: #ffffff;
            border: 2px solid #000000;
            color: #000000;
            padding: 10px 20px;
            font-size: 20px;
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

    auto* open_button = new QPushButton("Получить число наоборот: ", this);
    open_button->setFixedSize(kWidth, kHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::ReverseOpen);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(open_button);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void Window::ReverseOpen() {
    bool ok = false;
    QString number = QInputDialog::getText(
        nullptr, "Обратное число", "Введите целое число:", QLineEdit::Normal,
        "", &ok);
    if (ok && !number.isEmpty()) {
        bool n_ok;
        ll default_number = number.toLongLong(&n_ok);


        if (n_ok) {
            ll result = reverseNumber(default_number, 0);
            QMessageBox::information(
                this, "Результат",
                "Обратное число к вашему: " + QString::number(result));
        } else {
            QMessageBox::warning(nullptr, "Ошибка",
                                 "Введите целое число с учетом диапазона");
        }
    } else {
        QMessageBox::warning(nullptr, "Ошибка", "Введите целое число");
    }
}
