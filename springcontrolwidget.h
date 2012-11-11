#ifndef SPRINGCONTROLWIDGET_H
#define SPRINGCONTROLWIDGET_H

#include <QWidget>
#include "spring.h"

namespace Ui {
class SpringControlWidget;
}

class SpringControlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SpringControlWidget(QWidget *parent, spring& spring);
    ~SpringControlWidget();
    
private slots:
    void on_spinBox_editingFinished();

    void on_spinBox_2_editingFinished();

    void on_spinBox_3_editingFinished();

signals:
    void springChanged(spring& spring);
    void springControllerDeleted(spring& spring);

private:
    Ui::SpringControlWidget *ui;
    spring& connected_spring;
};

#endif // SPRINGCONTROLWIDGET_H
