#include <QtGui>
#include <QtWidgets>
#include "mainwindow.h"
#include"ui_mainwindow.h"
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QGridLayout>
#define OK 1
#define MY_HEAP_NUMBER 4
int g_Linenumber = 0;
int g_TotalWord = 0;
int CreateFirstLine(Linelist &L)         //创建文件首行头结点
{
    L = (Node*)malloc(sizeof(Node));
    L->heapptr = (Hstring*)malloc(sizeof(Hstring));
    if (!L) return ERROR;
    L->heapptr->str = NULL;
    L->heapptr->next = NULL;
    L->heapptr->heap_number = 1;
    L->next = NULL;
    L->word_number = 0;
    g_Linenumber++;
    return OK;
}
Linelist LineInsert_L(Linelist &L, int i)    //插入一行到第i个节点处
{
    Linelist ptr = L;
    Linelist s=NULL;//要插入的行
    int j = 0;
    while (ptr && j<i - 2) { ptr = ptr->next; j++; }
    if (!ptr|| j > i - 2)
    {
        printf("ERROR");
        return NULL;
    }
    s = (Node*)malloc(sizeof(Node));
    s->heapptr = (Hstring*)malloc(sizeof(Hstring));
    if (!s)exit(-1);
    s->heapptr->str = (char*)malloc(102 * sizeof(char));//为第一个分配堆
    memset(s->heapptr->str, '\0', 102* sizeof(char));//数组全部初始化为/0
    s->heapptr->next = NULL;
    s->heapptr->heap_number = 1;
    s->next = ptr->next;
    s->word_number = 0;
    s->next = NULL;
    ptr->next = s;
    return s;
}
HstringList New_Add_A_Word(Linelist line, int count_word, char str,int heap_number)
//在当前堆的末尾加入一个字符
{
    //将current_heap移动到当前的堆位置
    HstringList current_heap = line->heapptr;
    for (int i = 1; i < heap_number; i++)
    {
        current_heap = current_heap->next;
    }
    if (count_word % 100 != 0 || count_word == 0)
        current_heap->str[count_word - 100 * (heap_number-1)] = str;
    else if (count_word % 100 == 0)//重新分配堆
    {
        HstringList a;
        a = (Hstring*)malloc(sizeof(Hstring));//不知道这样移动对不对
        current_heap->next = a;
        current_heap = a;
        current_heap->str = (char*)malloc(102 * sizeof(char));
        memset(current_heap->str, '\0', 102 * sizeof(char));
        current_heap->heap_number = heap_number + 1;
        current_heap->str[0] = str;
        current_heap->next = NULL;
    }
    else
        printf("error");
    line->word_number++;
    g_TotalWord += 1;//每插入一个字符，总字数统计就+1
    return current_heap;
}
int PrintLine(Linelist L)//打印整个文件
{
    Linelist l = L;
    HstringList heapptr = l->heapptr;
    printf("\n当前文件如下：\n");
    while (l != NULL)//行
    {
        heapptr = l->heapptr;
        while(heapptr!=NULL)//块
        {
            printf("%s", heapptr->str);
            heapptr = heapptr->next;
        }
        //printf("有%d个字", l->word_number-1);//-1为了去掉换行符
        l = l->next;
    }
    printf("\n");
    return OK;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myLabel=new MyLabel(this);
    //myLabel->setText(tr("testLabel"));
    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(myLabel);
    ui->centralWidget->setLayout(layout);

    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    //textEdit = new QTextEdit(this);
    //setCentralWidget(textEdit);

    CreateFirstLine(corehead);
    Linelist line = corehead;
    current_heap = line->heapptr;
    current_heap->str = (char*)malloc(102 * sizeof(char));//为第一个分配堆
    memset(current_heap->str, '\0', 102 * sizeof(char));//数组全部初始化为/0
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MyLabel::focusInEvent(QFocusEvent * ev)
{

}
void MyLabel::focusOutEvent(QFocusEvent * ev)
{

}
void MyLabel::keyPressEvent(QKeyEvent * ev)
{
    QString str = text();//获取原字符串

    if (ev->key() == Qt::Key_Backspace){
        //如果按键是Backspace
        str.chop(1);//删除原字符串最后一个字符
        setText(str);//显示新字符串
    } else {
        //不是Backspace
        str += ev->text();//在原字符串后添加新输入的字符
        if(ev->text()==13)
          str.append("\n");
        setText(str);//显示新字符串
    }
}
void MyLabel::inputMethodEvent(QInputMethodEvent * ev)
{
    QString str = text();//获取原字符串

    str += ev->commitString();//原字符串后接上输入的中文字符串
    setText(str);//显示新字符串
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
    QByteArray ba = path.toLatin1();
    FILE *out= NULL;
    filename=ba.data();
    HstringList heapptr = corehead->heapptr;
    out=fopen(filename, "w");
    Linelist l = corehead;
    //qDebug() << path;
    if(!path.isEmpty()) {
        while (l != NULL)
            {
                heapptr = l->heapptr;
                while(heapptr!=NULL)//块
                {
                    int count = 0;
                    while (heapptr->str != NULL && count <= 99 && heapptr->str[count] != '\0')
                    {
                        if (heapptr->str[count] == '\n')
                            fprintf(out, "\n");
                        else
                            fputc(heapptr->str[count], out);
                        ++count;
                    }
                    heapptr = heapptr->next;
                }
                //printf("有%d个字", l->word_number-1);//-1为了去掉换行符
                l = l->next;
            }
            fprintf(out, "\n");
        fclose(out);
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::openFile()
{

    QString str = myLabel->text();//获取原字符串
    //释放原来堆(没做)
    filename=NULL;
    g_Linenumber = 0;
    g_TotalWord = 0;
    CreateFirstLine(corehead);
    Linelist line = corehead;
    current_heap = line->heapptr;
    current_heap->str = (char*)malloc(102 * sizeof(char));//为第一个分配堆
    memset(current_heap->str, '\0', 102 * sizeof(char));//数组全部初始化为/0

    QString path = QFileDialog::getOpenFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
    //textEdit->clear();
    QByteArray ba = path.toLatin1();
    filename=ba.data();
    //读入
    if(!path.isEmpty()) {
            FILE *fp = NULL;
            int count_word=0;//记录字数总数
            Linelist line = corehead;
            char write;
            fp = fopen(filename, "r"); /* 只供读void fileopen(char filename[])取 */
            if (NULL == fp) /* 如果失败了 */
            {
                QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
                return;
            }
            while ((write= getc(fp)) != EOF)
            {
                if (write == '\n')
                {
                    current_heap=New_Add_A_Word(line, count_word, write,current_heap->heap_number);
                    //line->word_number = Count_Line_WordNum(line);
                    printf("\n");
                    count_word = 0;//下一行字数清零
                    line = LineInsert_L(corehead, g_Linenumber + 1);//新建一行链表
                    current_heap = line->heapptr;
                    ++g_Linenumber;
                }
                else
                {
                    current_heap = New_Add_A_Word(line, count_word, write,current_heap->heap_number);
                    count_word++;
                }
            }
            fclose(fp);
        //打印
            Linelist l = corehead;
            HstringList heapptr = l->heapptr;
            char receive[4];
            int number_count=0;
            memset(receive,'\0',4*sizeof(char));
             //printf("\n当前文件如下：\n");
            while (l != NULL)//行
                {
                    heapptr = l->heapptr;
                    while(heapptr!=NULL)//块
                    {
                        int count = 0;
                        while (heapptr->str != NULL && count <= 99 && heapptr->str[count] != '\0')
                        {
                            if (heapptr->str[count] =='\n')
                                str.append("\n");
                            else if(heapptr->str[count]<0&&number_count<2)
                           {
                                receive[number_count]=heapptr->str[count];
                                number_count++;
                            }
                            else
                            {
                                receive[number_count]=heapptr->str[count];
                                number_count=0;
                                str.append(receive);
                                memset(receive,'\0',4*sizeof(char));
                             }
                            ++count;
                        }
                        heapptr = heapptr->next;
                    }
                    //printf("有%d个字", l->word_number-1);//-1为了去掉换行符
                    l = l->next;
                }
               str.append("\n");
               myLabel->setText(str);
        }
     else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}
