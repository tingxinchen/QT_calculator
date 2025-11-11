#include "dialog.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    display = new QLineEdit;
    display->setAlignment(Qt::AlignRight);
    display->setText("0");

    // === 建立按鈕 ===
    QPushButton *btn0 = new QPushButton("0");
    QPushButton *btn1 = new QPushButton("1");
    QPushButton *btn2 = new QPushButton("2");
    QPushButton *btn3 = new QPushButton("3");
    QPushButton *btn4 = new QPushButton("4");
    QPushButton *btn5 = new QPushButton("5");
    QPushButton *btn6 = new QPushButton("6");
    QPushButton *btn7 = new QPushButton("7");
    QPushButton *btn8 = new QPushButton("8");
    QPushButton *btn9 = new QPushButton("9");

    QPushButton *btnAdd = new QPushButton("+");
    QPushButton *btnSub = new QPushButton("-");
    QPushButton *btnMul = new QPushButton("*");
    QPushButton *btnDiv = new QPushButton("/");
    QPushButton *btnDot = new QPushButton(".");
    QPushButton *btnEq  = new QPushButton("=");

    QPushButton *backButton = new QPushButton("<-");

    // === 按鈕佈局 ===
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(btn7, 0, 0);
    gridLayout->addWidget(btn8, 0, 1);
    gridLayout->addWidget(btn9, 0, 2);
    gridLayout->addWidget(btnDiv, 0, 3);

    gridLayout->addWidget(btn4, 1, 0);
    gridLayout->addWidget(btn5, 1, 1);
    gridLayout->addWidget(btn6, 1, 2);
    gridLayout->addWidget(btnMul, 1, 3);

    gridLayout->addWidget(btn1, 2, 0);
    gridLayout->addWidget(btn2, 2, 1);
    gridLayout->addWidget(btn3, 2, 2);
    gridLayout->addWidget(btnSub, 2, 3);

    gridLayout->addWidget(btn0, 3, 0);
    gridLayout->addWidget(btnDot, 3, 1);
    gridLayout->addWidget(btnEq, 3, 2);
    gridLayout->addWidget(btnAdd, 3, 3);

    // === 手動設定每個按鈕的行為 ===
    auto appendText = [=](const QString &t){
        if (display->text() == "0" && t != ".")
            display->setText(t);
        else
            display->setText(display->text() + t);
    };

    connect(btn0, &QPushButton::clicked, this, [=](){ appendText("0"); });
    connect(btn1, &QPushButton::clicked, this, [=](){ appendText("1"); });
    connect(btn2, &QPushButton::clicked, this, [=](){ appendText("2"); });
    connect(btn3, &QPushButton::clicked, this, [=](){ appendText("3"); });
    connect(btn4, &QPushButton::clicked, this, [=](){ appendText("4"); });
    connect(btn5, &QPushButton::clicked, this, [=](){ appendText("5"); });
    connect(btn6, &QPushButton::clicked, this, [=](){ appendText("6"); });
    connect(btn7, &QPushButton::clicked, this, [=](){ appendText("7"); });
    connect(btn8, &QPushButton::clicked, this, [=](){ appendText("8"); });
    connect(btn9, &QPushButton::clicked, this, [=](){ appendText("9"); });

    connect(btnAdd, &QPushButton::clicked, this, [=](){ appendText("+"); });
    connect(btnSub, &QPushButton::clicked, this, [=](){ appendText("-"); });
    connect(btnMul, &QPushButton::clicked, this, [=](){ appendText("*"); });
    connect(btnDiv, &QPushButton::clicked, this, [=](){ appendText("/"); });
    connect(btnDot, &QPushButton::clicked, this, [=](){ appendText("."); });

    connect(btnEq, &QPushButton::clicked, this, &Dialog::calculate);
    connect(backButton, &QPushButton::clicked, this, &Dialog::backspace);

    // === 主版面 ===
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(display);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(backButton);
}

Dialog::~Dialog() {}

void Dialog::clearDisplay()
{
    display->setText("0");
}

void Dialog::calculate()
{
    QString expr = display->text();
    double result = simpleCalculate(expr);
    display->setText(QString::number(result, 'g', 12));
}

void Dialog::backspace()
{
    QString text = display->text();
    if (text.length() > 1) {
        text.chop(1);
        display->setText(text);
    } else {
        display->setText("0");
    }
}

double Dialog::simpleCalculate(const QString &expr)
{
    double result = 0;
    double num = 0;
    QChar op = '+';
    int i = 0;
    QString temp = expr + "+";

    while (i < temp.length()) {
        QChar c = temp[i];
        if (c.isDigit() || c == '.') {
            QString numStr;
            while (i < temp.length() && (temp[i].isDigit() || temp[i] == '.')) {
                numStr += temp[i];
                i++;
            }
            num = numStr.toDouble();
            if (op == '+') result += num;
            else if (op == '-') result -= num;
            else if (op == '*') result *= num;
            else if (op == '/') result /= num;
            continue;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            op = c;
        }
        i++;
    }
    return result;
}
