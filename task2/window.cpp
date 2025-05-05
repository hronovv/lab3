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

    auto* open_button =
        new QPushButton("Посчитать значение функции Аккермана: ", this);
    open_button->setFixedSize(kWidth, kHeigth);
    open_button->setStyleSheet(button_style);
    connect(open_button, &QPushButton::clicked, this, &Window::AkkermanOpen);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(open_button);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void Window::AkkermanOpen() {
    int m, n;
    bool ok = false;
    QString numbers = QInputDialog::getText(
        nullptr, "Функция Аккермана",
        "Введите неотрицательные числа m и n, разделенные запятой:",
        QLineEdit::Normal, "", &ok);

    if (ok && !numbers.isEmpty()) {
        QStringList numbers_list = numbers.split(",");
        if (numbers_list.size() == 2) {
            bool m_ok, n_ok;
            m = numbers_list[0].trimmed().toInt(&m_ok);
            n = numbers_list[1].trimmed().toInt(&n_ok);


            if (m_ok && n_ok) {
                if (m < 0 || n < 0) {
                    QMessageBox::warning(
                        nullptr, "Ошибка",
                        "Числа m и n должны быть неотрицательными!");
                } else if ((n == 0 && m > 4 + 1) || (n == 1 && m > 4) ||
                           (n > 1 && m > 3)) {
                    QMessageBox::warning(
                        nullptr, "Ошибка",
                        "Сорян. Я либо буду очень долго считать, либо вообще "
                        "не "
                        "посчитаю(читай: "
                        "https://ru.wikipedia.org/wiki/Функция_Аккермана");
                } else {
                    ull result = Akerman(m, n);
                    QMessageBox::information(
                        this, "Результат",
                        "Значение функции Аккермана для ваших чисел: " +
                            QString::number(result));
                }
            } else {
                QMessageBox::warning(
                    nullptr, "Ошибка",
                    "Введите корректные числовые значения чисел m и n.");
            }
        } else {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Введите две координаты, разделённые запятой.");
        }
    }
}
