#include "springcontrolwidget.h"
#include "ui_springcontrolwidget.h"

SpringControlWidget::SpringControlWidget(QWidget *parent, spring& spring) :
    QWidget(parent),
    ui(new Ui::SpringControlWidget),
    connected_spring(spring)
{
    ui->setupUi(this);
    ui->spinBox->setValue(connected_spring.min_len());
    ui->spinBox_2->setValue(connected_spring.opt_len());
    ui->spinBox_3->setValue(connected_spring.min_len_good_looking());
}

SpringControlWidget::~SpringControlWidget()
{
    emit springControllerDeleted(connected_spring);
    delete ui;
}

void SpringControlWidget::on_spinBox_editingFinished()
{
    connected_spring.set_min_len(ui->spinBox->value());
    emit springChanged(connected_spring);
}

void SpringControlWidget::on_spinBox_2_editingFinished()
{
    connected_spring.set_opt_len(ui->spinBox_2->value());
    emit springChanged(connected_spring);
}

void SpringControlWidget::on_spinBox_3_editingFinished()
{
    connected_spring.set_min_len_good_looking(ui->spinBox_3->value());
    emit springChanged(connected_spring);
}
