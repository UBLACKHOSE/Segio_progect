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
#include "segio_trace_info.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int errmsg(int errcode, const char* msg) {
    if (!msg) return errcode;

    fflush(stdout);
    fputs(msg, stderr);
    fputc('\n', stderr);
    fflush(stderr);
    return errcode;
}

void read_trace_inline(segy_file* fp, int tr_num, long trace0, int trace_bsize, int* in_line, int* x_line) {

    char traceh[SEGY_TRACE_HEADER_SIZE];
    int err = segy_traceheader(fp, tr_num, traceh, trace0, trace_bsize);

    err = segy_get_field(traceh, SEGY_TR_INLINE, &in_line[tr_num]);
    err = segy_get_field(traceh, SEGY_TR_CROSSLINE, &x_line[tr_num]);


//	cout << in_line[tr_num] << ' ' << x_line[tr_num]<< endl;
}

void tracer(segy_file* fp, int samnr, int tr_block_num, int tr_count, int block_size, long trace0, int trace_bsize, int* in_line, int* x_line) {


    for (int loc_tr_num = 0; loc_tr_num < tr_count; loc_tr_num++) {
        int tr_num = tr_block_num * block_size + loc_tr_num;
        read_trace_inline(fp, tr_num,trace0,trace_bsize, in_line,x_line);
    }


}

void in_and_x_line(int* in_line, int* x_line, int trace_size, std::vector<int> &trace) {

    trace.push_back(0);
    int prev_xline = x_line[0], prev_inline = in_line[0];
    for (int loc_tr_num = 0; loc_tr_num < trace_size; loc_tr_num++) {
        if (in_line[loc_tr_num]!= prev_inline || x_line[loc_tr_num]!= prev_xline) {
            prev_inline = in_line[loc_tr_num];
            prev_xline = x_line[loc_tr_num];
            trace.push_back(loc_tr_num);
            std::cout << loc_tr_num << ' ' << in_line[loc_tr_num] << ' ' << x_line[loc_tr_num] << std::endl;
        }
    }
}

QMap<QString,int> test;

void MainWindow::on_action_triggered()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.sgy").toStdString().c_str();

//    QByteArray ba = str.toLocal8Bit();
//    const char *PathToFile = ba.data();


    SeismicData *seg = new SeismicData(str);

    //Segio_trace_info *seg_info = new Segio_trace_info(*seg);

//    seg->segy_get_otg(*seg_info);
//    test = seg->get_trace_by_id(1);

//    std::cout<<seg->segy_get_size()<<std::endl;



//    char header[SEGY_TEXT_HEADER_SIZE + 1] = { 0 };
//    char binheader[SEGY_BINARY_HEADER_SIZE];
//    //Открываем segy файл
//    segy_file* fp = segy_open(PathToFile, "r");
//    //Открываем segy файл
//    if (!fp) fprintf(stderr, "segyio-cath: %s: No such file or directory\n", PathToFile);


//    //проверка на НЕПОНЯЛ
//    int err = segy_binheader(fp, binheader);
//    if (err) exit(errmsg(errno, "Unable to read binheader"));
//    //НЕПОНЯЛ
//    int samnr = segy_samples(binheader);
//    //возврощает формат,хотя в данном случае 1.
//    int format = segy_format(binheader);
//    switch (format) {
//    case SEGY_IBM_FLOAT_4_BYTE:
//    case SEGY_SIGNED_INTEGER_4_BYTE:
//    case SEGY_SIGNED_SHORT_2_BYTE:
//    case SEGY_FIXED_POINT_WITH_GAIN_4_BYTE:
//    case SEGY_IEEE_FLOAT_4_BYTE:
//    case SEGY_SIGNED_CHAR_1_BYTE:
//        break;

//    case 0:
//        format = SEGY_IBM_FLOAT_4_BYTE;
//        break;

//    case SEGY_NOT_IN_USE_1:
//    case SEGY_NOT_IN_USE_2:
//    default:
//        errmsg(1, "sample format field is garbage. "
//            "falling back to 4-byte float. "
//            "override with --format");
//        format = SEGY_IBM_FLOAT_4_BYTE;
//    }
//    //segy_trsize вычисляет размер трассировки в байтах, определяемый форматом трассировки.
//    int trace_bsize = segy_trsize(format, samnr);

//    // байтовое смещение первого заголовка трассировки.
//    long trace0 = segy_trace0(binheader);


//    int numtrh;
//    //количество трасс
//    err = segy_traces(fp, &numtrh, trace0, trace_bsize);
//    if (err)
//        exit(errmsg(errno, "Unable to determine number of traces in file"));

//    int block_size = 1000;

//    auto trbuf = new float[block_size * trace_bsize];
//    int* source_x = new int[block_size];
//    int* source_y = new int[block_size];
//    int* CDP_x = new int[block_size];
//    int* CDP_y = new int[block_size];
//    int* yline = new int[block_size];
//    int* xline = new int[block_size];
//    int* group_x = new int[block_size];
//    int* group_y = new int[block_size];
//    int* shot_point = new int[block_size];
//    int* offset = new int[block_size];
//    int* trace_id = new int[block_size];


//    std::cout << numtrh / block_size << std::endl;
//    std::cout << numtrh % block_size << std::endl;


//    float threshold = 0.01f;
//    size_t window_size = 15;

//    int size = segy_textheader_size();

//    err =  segy_read_textheader(fp, header);
//    std::cout << err << std::endl;
//    std::cout << header << std::endl;
//    err = segy_read_ext_textheader(fp, 0, header);
//    std::cout << err << std::endl;
//    std::cout << header << std::endl;
//    int traceno=100;
//    err = segy_traceheader(fp, traceno,header,trace0,trace_bsize);
//    std::cout << err << std::endl;
//    std::cout << header << std::endl;

//    //err = segy_sorting(fp,il,xl,tr_offset,int* sorting,trace0,int trace_bsize);

//    int* in_line = new int [numtrh];
//    int* x_line = new int[numtrh];
//    std::vector<int> traces_count;

//    for (int tr_block_num = 0; tr_block_num < numtrh / block_size; tr_block_num++) {
//        //std::cout << "block number " << tr_block_num << std::endl;
//        tracer(fp,samnr, tr_block_num, block_size, block_size, trace0,trace_bsize, in_line, x_line);
//    }
//    tracer(fp, samnr, numtrh / block_size, numtrh % block_size, block_size, trace0, trace_bsize, in_line, x_line);


//    in_and_x_line(in_line, x_line, numtrh, traces_count);
//    int n = 0;

//    QStringList tituls;
//    tituls << "Index set"<<"Start"<<"STOP"<<"Count trace(N)"<<"Inline(i)"<<"Xline(j)"<<"Linear index(I)";
//    ui->tableWidget->setColumnCount(7);
//    ui->tableWidget->setRowCount(traces_count.size()-1);
//    ui->tableWidget->setHorizontalHeaderLabels(tituls);
//    QTableWidgetItem *ptwi = 0;
//    for(int j=0;j< traces_count.size()-1;j++){
//            ptwi = new QTableWidgetItem(QString("%1").arg(j+1));
//            ui->tableWidget->setItem(j,0,ptwi);
//            ptwi = new QTableWidgetItem(QString("%1").arg(traces_count[j]));
//            ui->tableWidget->setItem(j,1,ptwi);
//            ptwi = new QTableWidgetItem(QString("%1").arg(traces_count[j+1]));
//            ui->tableWidget->setItem(j,2,ptwi);
//            ptwi = new QTableWidgetItem(QString("%1").arg(traces_count[j+1]- traces_count[j]));
//            ui->tableWidget->setItem(j,3,ptwi);
//            ptwi = new QTableWidgetItem(QString("%1").arg(in_line[traces_count[j]]));
//            ui->tableWidget->setItem(j,4,ptwi);
//            ptwi = new QTableWidgetItem(QString("%1").arg(x_line[traces_count[j]]));
//            ui->tableWidget->setItem(j,5,ptwi);
//            ptwi = new QTableWidgetItem(QString("%1").arg(in_line[traces_count[j]] *(traces_count[j + 1] - traces_count[j]) +x_line[traces_count[j]]));
//            ui->tableWidget->setItem(j,6,ptwi);
//        }
//    ui->File_path->setText(PathToFile);
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << test["source_x"]<< Qt::endl;;
    qDebug() << test["source_y"]<< Qt::endl;;
}
