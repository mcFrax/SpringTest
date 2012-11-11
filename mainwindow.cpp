#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spring_solving.h"
#include <sstream>
#include <vector>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include <QColor>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), scene(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (scene) delete scene;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    stringstream st(ui->lineEdit->text().toStdString());

    int desired_len;
    st >> desired_len;
    int next_min, next_opt, next_mgl;
    vector <spring> springs;
    while (st >> next_min >> next_opt >> next_mgl){
        springs.push_back(spring(next_opt, next_min, next_mgl));
    }

    if (springs.empty()) return;

    vector<length_t> wynik = solve(springs, desired_len);

    length_t from_beg = 0;

    //200 100 50 105 20 50 25 60 50 65 30 50 35

    static const double opt_sp_width = 7;
    static const double box_height = 80;
    static const double opt_rod_width = 3;
    static const int opt_rod_steps = 3;

    scene->addRect(0, -opt_rod_steps*opt_rod_width-5, desired_len, 5, QPen(), QBrush(Qt::green));

    for (unsigned i = 0; i < wynik.size(); ++i){
        scene->addRect(from_beg, 0, springs[i].min_len(), box_height, QPen(), QBrush(Qt::yellow));
        double sp_width = (wynik[i] != 0) ? (springs[i].opt_len() * opt_sp_width / wynik[i]) : box_height;
        scene->addRect(from_beg, (box_height-sp_width)/2.0, wynik[i], sp_width, QPen(), QBrush(Qt::red));

        scene->addRect(from_beg, -(i%opt_rod_steps*opt_rod_width) - opt_rod_width,
                       springs[i].opt_len(), opt_rod_width, QPen(), QBrush(Qt::green));
        from_beg += wynik[i];
    }
    scene->addRect(from_beg, 0, 1, box_height);
}
