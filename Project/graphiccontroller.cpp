#include "graphiccontroller.h"
#include <iostream> // TODO: need to DELETE

typedef Data::SeismComponent SeismComponent;
typedef Data::SeismEvent SeismEvent;
typedef Data::SeismTrace SeismTrace;

namespace EventOperation {
GraphicController::GraphicController(QWidget *parent)
    : QFrame(parent){}



void GraphicController::draw(Seismogramm* sm) {

    addTraceSeries(sm);
    //updateSeries();
}



void GraphicController::addTraceSeries(Seismogramm* sm)
{
    const float intervalAxisX = sm->getSampleInterval();// MICROSECONDS_IN_SECOND;
    int idx = -1;
    int index = 1;
    for (unsigned j = 0; j < sm->getTracesSize(); ++j, ++idx)
    {
        _norm = sm->getMaxValue(); /* NORMED*/;
        QLineSeries *series = new QLineSeries;
        series->setUseOpenGL(true); // NOTE: COMMENT FOR RELEASE
        auto trace = sm->getTraces(j);


        float tmp = intervalAxisX * sm->getBufferSize();



        for (int k = 0; k < sm->getBufferSize(); k++) {
            // index - сдвиг на номер компоненты
            series->append( trace[k + sm->getBufferSize() * j] * _gain / _norm + index,static_cast<qreal>(tmp));
            tmp -= intervalAxisX;
        }


        _chart->addSeries(series);
        series->setColor(_view->getAxisColor(j));
        series->attachAxis(_axisX);
        series->attachAxis(_axisY);
        _allSeries.push_back(series);
    }
}

}


