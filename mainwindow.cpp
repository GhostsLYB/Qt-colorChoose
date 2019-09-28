#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(200,200);
    this->setWindowTitle("ColorChoose");
    color = ui->btnColor->palette().color(QPalette::Background);
    alterColor();
    connect(ui->btnColor,&QPushButton::clicked,this,&MainWindow::on_colorChangegd);
    connect(this,&MainWindow::rgbChanged,this,&MainWindow::on_rgbChanged);
    connect(this,&MainWindow::hexChanged,this,&MainWindow::on_hexChanged);
    QFile f(":/style.qss");
    if(f.open(QFile::ReadOnly))
        qApp->setStyleSheet(f.readAll());
    f.close();
}

void MainWindow::on_colorChangegd()
{
    QPalette palette = ui->btnColor->palette();
    QColor newColor;
    newColor = QColorDialog::getColor(color,this,"颜色选择");
    if(newColor.isValid())
    {
        int r = newColor.red();
        int g = newColor.green();
        int b = newColor.blue();
        color = QColor(r,g,b);
        alterColor();
    }
}

void MainWindow::on_rgbChanged(QString str)
{
    QString s = str;
    int one = s.indexOf(',');
    int r = s.mid(4,one-4).toInt();
    s = s.mid(one+1);
    one = s.indexOf(',');
    int g = s.mid(0,one).toInt();
    s = s.mid(one+1);
    one = s.indexOf(')');
    int b = s.mid(0,one).toInt();
    QColor newColor = QColor(r,g,b);
    if(newColor.isValid())
        color = newColor;
    alterColor();
}

void MainWindow::on_hexChanged(QString str)
{
    if(str.isEmpty())
        return;
    if(str.count() != 7)
        return;
    if(str.at(0) != '#')
        return;
    bool isHex = false;
    for(int i = 1; i < str.count(); i++)
    {
        QChar ch = str.at(1); //判断字符ch是否16进制字符，是返回1，否返回0
        if ( ch >='0' && ch <='9' ) {isHex = true;break;}
        if ( ch >='A' && ch <='F' ) {isHex = true;break;}
        if ( ch >='a' && ch <='f' ) {isHex = true;break;}
        else {isHex = false;break;}
    }
    if(!isHex)
        return;
    QString sr = str.mid(1,2);
    if(sr.isEmpty())
        return;
    QString sg = str.mid(3,2);
    if(sg.isEmpty())
        return;
    QString sb = str.mid(5,2);
    if(sb.isEmpty())
        return;
    QColor newColor = QColor(str);
    if(newColor.isValid())
        color = newColor;
    alterColor();
}

void MainWindow::alterColor()
{
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    ui->btnColor->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").
                                arg(r).arg(g).arg(b));
    ui->lineEdit->setText(QString("rgb(%1,%2,%3)").arg(r).arg(g).arg(b));
    QString sr,sg,sb;
    if(r<16)
        sr = QString::asprintf("0%X",r);
    else
        sr = QString::asprintf("%X",r);
    if(g<16)
        sg = QString::asprintf("0%X",g);
    else
        sg = QString::asprintf("%X",g);
    if(b<16)
        sb = QString::asprintf("0%X",b);
    else
        sb = QString::asprintf("%X",b);
    ui->lineEdit_2->setText("#"+sr+sg+sb);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Enter)
    {
        //qDebug()<<"pressed enter";
        if(ui->lineEdit->hasFocus())
        {
            emit rgbChanged(ui->lineEdit->text());
            //qDebug()<<"lineEdit1 has focus";
        }
        if(ui->lineEdit_2->hasFocus())
        {
            emit hexChanged(ui->lineEdit_2->text());
            //qDebug()<<"lineEdit2has focus";
        }
    }
    QMainWindow::keyPressEvent(e);
}

MainWindow::~MainWindow()
{
    delete ui;
}

