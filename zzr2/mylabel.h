#ifndef MYLABEL_H
#define MYLABEL_H
#include <QFocusEvent>
#include <QLabel>
#include <QKeyEvent>
#include <QInputMethodEvent>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget * parent);
protected:
    void focusInEvent(QFocusEvent * ev);//获取焦点
    void focusOutEvent(QFocusEvent *ev);//失去焦点
    void keyPressEvent(QKeyEvent * ev);
    void inputMethodEvent(QInputMethodEvent * ev);
};

#endif // MYLABEL_H
