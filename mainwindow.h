#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QPushButton>
#include <QKeyEvent>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
signals:
    void rgbChanged(QString);
    void hexChanged(QString);
private:
    void on_colorChangegd();
    void on_rgbChanged(QString);
    void on_hexChanged(QString);
    void alterColor();
    QColor color;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
