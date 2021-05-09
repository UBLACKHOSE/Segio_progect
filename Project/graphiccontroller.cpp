#include "graphiccontroller.h"
#include "chart.h"


#include <iostream> // TODO: need to DELETE
typedef Data::SeismComponent SeismComponent;
typedef Data::SeismEvent SeismEvent;
typedef Data::SeismTrace SeismTrace;

namespace EventOperation {
GraphicController::GraphicController(QWidget *parent)
    : QFrame(parent){}


double GraphicController::findPointAroundZero(int numberOfComponent,QPointF &from, QPointF &to) {

  double k = (to.y() - from.y()) / (to.x() - from.x());
  double b = (to.x() * from.y() - to.y() * from.x()) / (to.x() - from.x());
  return (static_cast<double>(numberOfComponent) * k + b);
}


Chart* GraphicController::draw(Seismogramm* sm,int flag = 0,float g = 0.4) {

    _gain = g;

    const double MAX_OFFSET = 0.00001;
    QPen pen(QRgb(0x000000));
    QLineSeries *series;
    Chart *chartings = new Chart();


    int index;
    for(int i=0;i<3;i++){

        series = getTrace(sm,i,pen);


        if(flag!=0){

        index = i + sm->getMaxValue() - _gain;
        double seriesXZeroCord = 0 *_gain / sm->getMaxValue()+index;
        QLineSeries *medianSeries = new QLineSeries();
        medianSeries->setUseOpenGL(true);
        medianSeries->append(seriesXZeroCord, sm->getBufferSize());
        medianSeries->append(seriesXZeroCord, 0);
        QLineSeries *newSeries = new QLineSeries;
        newSeries->setUseOpenGL(true);
        QPointF lp = series->at(0);

        if (flag==1) {
          // проходим по точкам серии
          for (auto &point : series->points()) {
            double y = point.y();
            /* we have a median series like x = 1, x = 2, x = 3 func
    * if point[t] was left from median and point[t+1] from right
    * then we don't use wiggle, becouse we want to keep one side --
    * positive or negative.
    * this if block decide we should paint or not
    * */
            if (lp.x() <= seriesXZeroCord && point.x() >= seriesXZeroCord) {
              y = (((lp.y() - point.y())/2) + point.y());


              qDebug()<<lp.y();
              qDebug()<<point.y();
              qDebug()<<y;


              newSeries->append(QPointF(seriesXZeroCord, y));
              lp = point;
              continue;
            }

            if (lp.x() >= seriesXZeroCord && point.x() <= seriesXZeroCord) {


              y = (((lp.y() - point.y())/2) + point.y());

              newSeries->append(seriesXZeroCord, y);
              lp = point;
              continue;
            }

            if (point.x() >= seriesXZeroCord) {
                newSeries->append(point);
                lp = point;
              continue;
            }else {
                lp = point;
            }

          }
        } else if(flag==2) {
          for (auto &point : series->points()) {
            double y = 0;
            if (lp.x() >= seriesXZeroCord && point.x() <= seriesXZeroCord) {
              y = (((lp.y() - point.y())/2) + point.y());

              newSeries->append(QPointF(seriesXZeroCord, y));
              lp = point;
              continue;
            }
            if (lp.x() <= seriesXZeroCord && point.x() >= seriesXZeroCord) {
              y = (((lp.y() - point.y())/2) + point.y());

              newSeries->append(seriesXZeroCord, y);
              lp = point;
              continue;
            }
            if (point.x() <= seriesXZeroCord) {
              newSeries->append(point);
              lp = point;
              continue;
            }
            else{
               lp = point;
            }
          }
        }

        QAreaSeries *upperArea = new QAreaSeries();
        QColor upperAreaColor = QColor(QRgb(0x000000));
        upperAreaColor.setAlpha(100);
        upperArea->setPen(QColor(QRgb(0xffffff)));
        upperArea->setBrush(QBrush(upperAreaColor));
        medianSeries->setVisible(false);
        upperArea->setLowerSeries(medianSeries);
        upperArea->setUpperSeries(newSeries);

        upperArea->setUseOpenGL(true);
        chartings->addSeries(upperArea);
        }
        chartings->addSeries(series);
    }


    chartings->setAnimationOptions(QChart::SeriesAnimations);
    chartings->legend()->hide();
    chartings->createDefaultAxes();

    return chartings;


}

QLineSeries* GraphicController::getTrace(Seismogramm* sm,int j,QPen pen){
    QLineSeries *series = new QLineSeries;
    const float intervalAxisX = sm->getSampleInterval();
    auto trace = sm->getTraces(j);
    float tmp = sm->getBufferSize();
    _norm = sm->getMaxValue();
    int index = j + _norm - _gain;
    for (int k = 0; k < sm->getBufferSize(); k++) {
        series->append( trace[k + sm->getBufferSize() * j] * _gain / _norm + index,tmp);
        series->setPen(pen);
        series->setUseOpenGL(true);
        tmp--;
    }
    return series;
}




void GraphicController::addTraceSeries(Seismogramm* sm,int index)
{
    const float intervalAxisX = sm->getSampleInterval();// MICROSECONDS_IN_SECOND;
    int idx = -1;
    for (int j = 0; j < sm->getTracesSize(); ++j, ++idx)
    {

        _norm = sm->getMaxValue(); /* NORMED*/;
        QLineSeries *series = new QLineSeries;
        //series->setUseOpenGL(true); // NOTE: COMMENT FOR RELEASE
        auto trace = sm->getTraces(j);


        float tmp = intervalAxisX * sm->getBufferSize();



//        for (int k = 0; k < sm->getBufferSize(); k++) {
//            // index - сдвиг на номер компоненты
//            series->append( trace[k + sm->getBufferSize() * j] * _gain / _norm + index,static_cast<qreal>(tmp));
//            tmp -= intervalAxisX;
//        }

        for (int i = 0; i < 500; i++) {
            QPointF p((qreal) i, 1);
            p.ry() += QRandomGenerator::global()->bounded(20);
            *series << p;
            //qDebug()<<p;
        }
        index+=_norm - _gain;

        //_chart->addSeries(series);
        //series->setColor(_view->getAxisColor(j));
        //series->attachAxis(_axisX);
        //series->attachAxis(_axisY);
        _allSeries.push_back(series);
    }
}


void GraphicController::setGainCoefficient(const float gainCoefficient) {
  _gain = gainCoefficient;
}





}


