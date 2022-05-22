#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString a;
    QString b; //定义两个变量a为前操作数，b为后操作数
    QString texT;//获取编辑框的内容
    bool Add=false;
    bool Sub=false;
    bool Mul=false;
    bool Div=false;
    void matchFh(); //识别输入文本的符号与分割

private:
    Ui::MainWindow *ui;

private slots:
    void numOnClick();//数字按键点击事件
    void fuHao();//符号点击事件
    void equalNum();//等于号点击事件

};
#endif // MAINWINDOW_H
