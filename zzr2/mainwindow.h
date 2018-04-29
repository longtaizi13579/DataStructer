#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "mylabel.h"
#include <stdio.h>
#include<stdlib.h>
#define MY_HEAP_NUMBER 4
namespace Ui {
class MainWindow;
}

typedef struct hstring{
    int heap_number;
    char* str;
    hstring* next;//这样吗
}Hstring,*HstringList;//堆的存储方式

typedef struct node {
    HstringList heapptr;// 堆的头指针
    int word_number;//每行的字数
    node* next;//连接下一行
}Node, *Linelist;//每行的存储结构


class QTextEdit;
class MainWindow :  public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();

private:
    Ui::MainWindow *ui;
    MyLabel * myLabel;
    QAction *openAction;
    QAction *saveAction;
    Linelist corehead;//头结点指针
    HstringList current_heap;//当前节点指针
    char* filename;/* 用于存放文件名 */
    QTextEdit *textEdit;
};

#endif // MAINWINDOW_H
