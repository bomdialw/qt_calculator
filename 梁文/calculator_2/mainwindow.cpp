#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QToolButton>
#include <QTextCursor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setWindowTitle("简易计算器");
    ui->plainTextEdit->setReadOnly(true);//设置为只读
    ui->plainTextEdit->setPlainText(""); //初始框为空
    texT = ui->plainTextEdit->toPlainText();//把框内内容给到texT

    //捕获键盘
    ui->num0->setShortcut(QKeySequence(Qt::Key_0));
    ui->num1->setShortcut(QKeySequence(Qt::Key_1));
    ui->num2->setShortcut(QKeySequence(Qt::Key_2));
    ui->num3->setShortcut(QKeySequence(Qt::Key_3));
    ui->num4->setShortcut(QKeySequence(Qt::Key_4));
    ui->num5->setShortcut(QKeySequence(Qt::Key_5));
    ui->num6->setShortcut(QKeySequence(Qt::Key_6));
    ui->num7->setShortcut(QKeySequence(Qt::Key_7));
    ui->num8->setShortcut(QKeySequence(Qt::Key_8));
    ui->num9->setShortcut(QKeySequence(Qt::Key_9));
    ui->num10->setShortcut(QKeySequence(Qt::Key_Period));
    ui->add->setShortcut(QKeySequence(Qt::Key_Plus));
    ui->sub->setShortcut(QKeySequence(Qt::Key_Minus));
    ui->mul->setShortcut(QKeySequence(Qt::Key_Asterisk));
    ui->dev->setShortcut(QKeySequence(Qt::Key_Slash));
    ui->delete_2->setShortcut(QKeySequence(Qt::Key_Backspace));
    ui->equal->setShortcut(QKeySequence(Qt::Key_Equal));
    ui->equal->setShortcut(QKeySequence(Qt::Key_Enter));

    //数字的槽函数
    connect(ui->num0,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num1,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num2,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num3,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num4,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num5,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num6,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num7,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num8,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num9,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));
    connect(ui->num10,SIGNAL(clicked(bool)),this,SLOT(numOnClick()));

    //符号槽函数
    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(fuHao()));
    connect(ui->sub,SIGNAL(clicked(bool)),this,SLOT(fuHao()));
    connect(ui->mul,SIGNAL(clicked(bool)),this,SLOT(fuHao()));
    connect(ui->dev,SIGNAL(clicked(bool)),this,SLOT(fuHao()));
    connect(ui->AC,SIGNAL(clicked(bool)),this,SLOT(fuHao()));
    connect(ui->delete_2,SIGNAL(clicked(bool)),this,SLOT(fuHao()));

    //等于号槽函数
    connect(ui->equal,SIGNAL(clicked(bool)),this,SLOT(equalNum()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numOnClick()
{
    QToolButton *numName = (QToolButton*) sender();//sender()  返回的就是你信号来源对象的指针
    ui->plainTextEdit->textCursor().insertText(numName->text());//从光标处插入文本
    texT = ui->plainTextEdit->toPlainText();        //Returns the text of the text edit as plain text返回文本框中的文本到texT
    if(Add)
    {
        int i = texT.indexOf("+");  //索引运算符
        texT = texT.mid(i+1);  //从i+1位置开始返回文本中的内容
        b = texT;
    }
    else if(Sub)
    {
        int i = texT.indexOf("-");
        texT = texT.mid(i+1);
        b = texT;
    }
    else if(Mul)
    {
        int i = texT.indexOf("×");
        texT = texT.mid(i+1);
        b = texT;
    }
    else if(Div)
    {
        int i = texT.indexOf("÷");
        texT = texT.mid(i+1);
        b = texT;
    }
    else a=texT;
    qDebug()<<a<<b;
}

void MainWindow::fuHao()
{
    QToolButton *fh = (QToolButton*)sender();//返回指向发送信号的对象的指针
    QString f = fh->text();
    if(!(Add||Sub||Mul||Div))//只限定输入一个运算符
    {
        if(f == "+")
        {
            Add = true;
            ui->plainTextEdit->textCursor().insertText("+");//在文本的光标处插入一个"+"
        }
        if(f == "-")
        {
            Sub = true;
            ui->plainTextEdit->textCursor().insertText("-");
        }
        if(f == "×")
        {
            Mul = true;
            ui->plainTextEdit->textCursor().insertText("×");
        }
        if(f == "÷")
        {
            Div = true;
            ui->plainTextEdit->textCursor().insertText("÷");
        }
    }

    if(f == "←")
    {
        texT = ui->plainTextEdit->toPlainText();
        texT.chop(1);         //从文本中的末尾移除1个字符
        Add=Sub=Mul=Div=false;
        matchFh(); //识别输入文本的符号与分割
        ui->plainTextEdit->setPlainText(texT);//移除后剩余的文本放置在文本编辑框
        ui->plainTextEdit->moveCursor(QTextCursor::End);//移除操作结束，光标处于文本末端
    }

    if(f == "AC")
    {
        b='0';
        a='0';
        Add=Sub=Mul=Div=false;
        ui->plainTextEdit->setPlainText("");
    }
}

void MainWindow::matchFh()//识别输入文本的符号与分割
{
    if(texT.contains("+",Qt::CaseSensitive))//检测输入文本是否有“+”号
    {
        QStringList t = texT.split("+");//提供字符串列表的类，t为它的一个成员，
        //将字符串拆分为子字符串，无论在何处出现"+"，并返回这些字符串的列表。
        a = t[0]; //将分割的字符分别赋值给a和b
        b = t[1];
        Add = true;
    }
    else if(texT.contains("-",Qt::CaseSensitive)) //检测输入文本是否有“-”号
    {
        QStringList t = texT.split("-");
        a = t[0];
        b = t[1];
        Sub = true;
    }
    else if(texT.contains("×",Qt::CaseSensitive)) //检测输入文本是否有“×”号
    {
        QStringList t = texT.split("×");
        a = t[0];
        b = t[1];
        Mul = true;
    }
    else if(texT.contains("÷",Qt::CaseSensitive)) //检测输入文本是否有“÷”号
    {
        QStringList t = texT.split("÷");
        a = t[0];
        b = t[1];
        Div = true;
    }
    else a = texT;//如果把+-*/删除了，只剩下前运算数，就把文本内容给a
}

void MainWindow::equalNum()
{
    double x;
    double y;
    texT = ui->plainTextEdit->toPlainText();
    matchFh();
    x = a.toDouble();
    //返回Qstring转换为double的数据
    y = b.toDouble();
    qDebug()<<"x:"<<x<<"y:"<<y;
    if(Add)
    {
        ui->plainTextEdit->setPlainText(a=QString::number(x+y)); //将运算后的结果重新给到前运算数，将之前的运算符置为false
        Add = false;
    }
    if(Sub)
    {
        ui->plainTextEdit->setPlainText(a=QString::number(x-y));
        Sub = false;
    }
    if(Mul)
    {
        ui->plainTextEdit->setPlainText(a=QString::number(x*y));
        Mul = false;
    }
    if(Div)
    {
        ui->plainTextEdit->setPlainText(a=QString::number(x/y));
        Div = false;
    }
    ui->plainTextEdit->moveCursor(QTextCursor::End);//运算结束，光标处于文本末端
}

