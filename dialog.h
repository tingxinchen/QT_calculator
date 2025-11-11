#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QLineEdit;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void clearDisplay();   // 清空顯示器
    void calculate();      // 計算
    void backspace();      // 退一位

private:
    QLineEdit *display;
    QString currentInput;

    double simpleCalculate(const QString &expr); // 用來計算簡單四則運算
};

#endif // DIALOG_H
