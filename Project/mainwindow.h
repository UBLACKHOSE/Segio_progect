#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtCharts>
#include <QMainWindow>
#include "seismicdata.h"
#include "seismogramm.h"
#include "graphiccontroller.h"
#include "graphview.h"
#include "chart.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();


    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_groupBox_clicked();

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);


    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    SeismicData *seg;
    QString Path;
    GraphView* view = nullptr;
    GraphView* view_coordinate = nullptr;
    int in_line,x_line;
    int flag = 0;
    float _gain = 0.4;
};
#endif // MAINWINDOW_H
