#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <memory>
#include <vector>
#include "segyio\segy.h"
#include "mainwindow.h"
#include "seg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}