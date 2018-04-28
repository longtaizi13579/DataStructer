
#include "mylabel.h"

MyLabel::MyLabel(QWidget * parent)
    : QLabel(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_InputMethodEnabled, true);
}
