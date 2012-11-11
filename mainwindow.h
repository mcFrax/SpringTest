#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include "spring.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_newObjectButton_clicked();

    void redrawSprings();

    void springControllerDeleted(spring& spring);

    void on_widthEdit_editingFinished();

    void on_widthSlider_valueChanged(int);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QList<spring> springs;
    double overall_length;
};

#endif // MAINWINDOW_H
