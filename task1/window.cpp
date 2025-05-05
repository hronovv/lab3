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

    auto* open_button = new QPushButton(
        "Перевести число из десятичной системы в двоичную систему: ", this);
    open_button->setFixedSize(kWidth, kHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::BinaryOpen);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(open_button);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void Window::BinaryOpen() {
    bool ok = false;
    double decimal_number = QInputDialog::getDouble(
        this, "Конвертация", "Введите ваше число:", 0.0, -1 * kMaxNumber,
        kMaxNumber, kAfterPointNumbers, &ok);


    if (ok) {
        QString binary_number = QString::fromStdString(Binary(decimal_number));
        QMessageBox::information(
            this, "Результат",
            "Ваше число " +
                QString::fromStdString(std::to_string(decimal_number)) +
                " в двоичной системе исчисления: " + binary_number);
    } else {
        QMessageBox::warning(this, "Ошибка",
                             "Вы не ввели число или число вне диапазона.");
    }
}
