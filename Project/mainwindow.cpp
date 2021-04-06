#include "mainwindow.h"
#include "segyio\segy.h"
#include <QFileDialog>
#include "./ui_mainwindow.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <memory>
#include <vector>
#include <QtWidgets>
#include "seismicdata.h"
#include "seismogramm.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.sgy").toStdString().c_str();
    if(!str.isEmpty()){
        SeismicData *seg = new SeismicData(str);
        Seismogramm *seis = seg->getSeismogramm(866,368);
        qDebug()<< "this max:"<<seis->getMaxValue();
    }
}

void MainWindow::on_pushButton_clicked()
{

}
