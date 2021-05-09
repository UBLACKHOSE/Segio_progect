#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE


//![1]
class GraphView : public QChartView
{
//![1]
public:
    GraphView(QChart *chart, QWidget *parent = 0);

//![2]
protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
//![2]

private:
    bool m_isTouching;
};

#endif // GRAPHVIEW_H
