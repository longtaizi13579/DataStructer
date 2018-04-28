#ifndef MYLABEL_H
#define MYLABEL_H

#include <QMainWindow>

namespace Ui {
class MyLabel;
}

class MyLabel : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyLabel(QWidget *parent = 0);
    ~MyLabel();

protected:
    void focusInEvent(QFocusEvent * ev);//获取焦点
    void focusOutEvent(QFocusEvent *ev);//失去焦点
    void keyPressEvent(QKeyEvent * ev);
    void inputMethodEvent(QInputMethodEvent * ev);

private:
    Ui::MyLabel *ui;
};

#endif // MYLABEL_H
