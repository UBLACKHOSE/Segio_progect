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

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox_2->hide();
    ui->label_2->hide();
    ui->pushButton->hide();
    ui->groupBox->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    Path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.sgy").toStdString().c_str();
    if(!Path.isEmpty()){
        if(view!=nullptr&&view_coordinate!=nullptr){
            view->hide();
            view_coordinate->hide();
        }
        ui->groupBox->show();
        seg = new SeismicData(Path);
        QStringList list = seg->getInlineList();
        ui->comboBox->addItems(list);
        QStringList list2 = seg->getXlineList(list[0].toInt());
        Seismogramm *seis = seg->getSeismogramm(list[0].toInt(),list2[0].toInt());
        view_coordinate = new GraphView(seg->getScatterSeries());

        in_line = list[0].toInt();
        x_line = list2[0].toInt();
        EventOperation:: GraphicController *chart = new EventOperation::GraphicController();
        Chart* ch = chart->draw(seis,flag,_gain);
        view = new GraphView(ch);
        view->setRenderHint(QPainter::Antialiasing);
        ui->verticalLayout->addWidget(view);
        ui->verticalLayout_2->addWidget(view_coordinate);
        //ui->comboBox->addItems("Hello");
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(!Path.isEmpty()){
    if(!ui->comboBox->currentText().isEmpty() || !ui->comboBox_2->currentText().isEmpty()){

        in_line = ui->comboBox->currentText().toInt();
        x_line =ui->comboBox_2->currentText().toInt();

        if(in_line >0||x_line>0){
            view->hide();
            seg = new SeismicData(Path);
            Seismogramm *seis = seg->getSeismogramm(in_line,x_line);
            EventOperation:: GraphicController *chart = new EventOperation::GraphicController();
            Chart* ch = chart->draw(seis,flag,_gain);
            view = new GraphView(ch);
            view->setRenderHint(QPainter::Antialiasing);
            ui->verticalLayout->addWidget(view);
        }
    }
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(!Path.isEmpty()){
        QStringList list = seg->getXlineList(arg1.toInt());
        ui->comboBox_2->show();
        ui->label_2->show();
        ui->comboBox_2->addItems(list);
    }
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
    ui->pushButton->show();
}

void MainWindow::on_groupBox_clicked()
{
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked){
        view->hide();
        flag =0;
        Seismogramm *seis = seg->getSeismogramm(in_line,x_line);
        EventOperation:: GraphicController *chart = new EventOperation::GraphicController();
        Chart* ch = chart->draw(seis,0,_gain);
        view = new GraphView(ch);
        view->setRenderHint(QPainter::Antialiasing);
        ui->verticalLayout->addWidget(view);
    }
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if(checked){
        view->hide();
        flag =1;
        Seismogramm *seis = seg->getSeismogramm(in_line,x_line);
        EventOperation:: GraphicController *chart = new EventOperation::GraphicController();
        Chart* ch = chart->draw(seis,1,_gain);
        view = new GraphView(ch);
        view->setRenderHint(QPainter::Antialiasing);
        ui->verticalLayout->addWidget(view);
    }
}

void MainWindow::on_radioButton_3_clicked(bool checked)
{
    if(checked){
        view->hide();
        flag =2;
        Seismogramm *seis = seg->getSeismogramm(in_line,x_line);
        EventOperation:: GraphicController *chart = new EventOperation::GraphicController();
        Chart* ch = chart->draw(seis,2,_gain);
        view = new GraphView(ch);
        view->setRenderHint(QPainter::Antialiasing);
        ui->verticalLayout->addWidget(view);
    }
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
        if(!Path.isEmpty()){
    view->hide();
    _gain =arg1;
    Seismogramm *seis = seg->getSeismogramm(in_line,x_line);
    EventOperation:: GraphicController *chart = new EventOperation::GraphicController();
    Chart* ch = chart->draw(seis,flag,_gain);
    view = new GraphView(ch);
    view->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(view);
    qDebug()<<_gain;
        }
        else{
                _gain =arg1;
        }
}
