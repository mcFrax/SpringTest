#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spring_solving.h"
#include <sstream>
#include <vector>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QString>
#include <iostream>
#include <QInputDialog>
#include "springcontrolwidget.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), scene(0), overall_length(500)
{
    ui->setupUi(this);
    ui->widthSlider->setValue(overall_length);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newObjectButton_clicked()
{
    addSpringController();
    redrawSprings();
}

void MainWindow::redrawSprings()
{
    cerr << "redrawSprings()" << endl;
    if (scene) delete scene;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    int desired_len = overall_length;

    cerr << springs.size() << endl;
    for (auto i = springs.begin(); i != springs.end(); ++i)
        cerr << i->opt_len() << ' ' << i->min_len() << ' ' << i->min_len_good_looking() << ' ' << endl;

    if (springs.empty()) return;

    vector<length_t> wynik = solve(springs, desired_len);

    length_t from_beg = 0;

    static const double opt_sp_width = 7;
    static const double box_height = 80;
    static const double opt_rod_width = 3;
    static const int opt_rod_steps = 3;

    scene->addRect(0, -opt_rod_steps*opt_rod_width-5, desired_len, 5, QPen(), QBrush(Qt::green));

    for (unsigned i = 0; i < wynik.size(); ++i){
        scene->addRect(from_beg, 0, springs[i].min_len(), box_height, QPen(), QBrush(Qt::yellow));
        scene->addRect(from_beg+springs[i].min_len(), 0, springs[i].min_len_good_looking()-springs[i].min_len(),
                       box_height, QPen(), QBrush(Qt::cyan));
        double sp_width = (wynik[i] != 0) ? (springs[i].opt_len() * opt_sp_width / wynik[i]) : box_height;
        scene->addRect(from_beg, (box_height-sp_width)/2.0, wynik[i], sp_width, QPen(), QBrush(Qt::red));

        scene->addRect(from_beg, -(i%opt_rod_steps*opt_rod_width) - opt_rod_width,
                       springs[i].opt_len(), opt_rod_width, QPen(), QBrush(Qt::green));
        from_beg += wynik[i];
    }
    scene->addRect(from_beg, 0, 1, box_height);
}

void MainWindow::springControllerDeleted(spring &spring)
{
    //inefficient
    cerr << "springControllerDeleted(spring &spring)\n";
    for (auto i = springs.begin(); i != springs.end(); ++i){
        if (&(*i) == &spring){
            springs.erase(i);
            break;
        }
    }

    redrawSprings();
}

void MainWindow::on_widthEdit_editingFinished()
{
    if (sender() == ui->widthEdit){
        ui->widthSlider->setValue(ui->widthEdit->text().toInt());
    } else /*if (sender() == ui->widthSlider)*/{
        ui->widthEdit->setText(QString::number(ui->widthSlider->value()));
    }

    overall_length = ui->widthSlider->value();

    redrawSprings();
}

void MainWindow::on_widthSlider_valueChanged(int)
{
    on_widthEdit_editingFinished();
}

void MainWindow::on_textInputButton_clicked()
{
    stringstream str;
    for (auto i = springs.begin(); i != springs.end(); ++i)
        str << i->min_len() << ' ' << i->opt_len() << ' ' << i->min_len_good_looking() << ' ';
    QString input = QInputDialog::getText(this, tr("Input"), tr("input"),
                                          QLineEdit::Normal, QString::fromStdString(str.str()));
    if (input.isNull()) return;

    while (ui->verticalLayout_3->count() > 1)
        ui->verticalLayout_3->removeItem(ui->verticalLayout_3->itemAt(0));

    stringstream str2(input.toStdString());
    double min_len, opt_len, mgl;
    while (str2 >> min_len >> opt_len >> mgl){
        addSpringController(spring(opt_len, min_len, mgl));
    }

    redrawSprings();
}

void MainWindow::addSpringController(const spring &s)
{
    springs.push_back(s);
    SpringControlWidget *spc = new SpringControlWidget(this, springs.back());
    ui->verticalLayout_3->insertWidget(ui->verticalLayout_3->count()-1, spc);

    connect(spc, SIGNAL(springChanged(spring&)), this, SLOT(redrawSprings()));
    connect(spc, SIGNAL(springControllerDeleted(spring&)), this, SLOT(springControllerDeleted(spring&)));
}
