#pragma once

//#include "wavepick.h"
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

namespace EventOperation {
class GraphicView : public QChartView {
  Q_OBJECT
public:
  GraphicView(QChart *, QWidget *parent = nullptr);




//  void setWaveRadius(const qreal wr) { WAVE_RADIUS = wr; }
//  void setRangeX(const qreal rangeX) { _rangeX = rangeX; }
//  void setRangeY(const qreal rangeY) { _rangeY = rangeY; }
//  void setCountOfComponents(int count) { _countOfComponents = count; }

//  bool isEdit() const { return _editMode; }



//  void resetItemSize() { _sizeWaveItem = DEFAULT_WAVEITEM_SIZE; }

protected:
//  bool viewportEvent(QEvent *) override;
//  void mousePressEvent(QMouseEvent *) override;
//  void mouseMoveEvent(QMouseEvent *) override;
//  void mouseReleaseEvent(QMouseEvent *) override;
//  void keyPressEvent(QKeyEvent *) override;
//  void keyReleaseEvent(QKeyEvent *) override;
//  void mouseDoubleClickEvent(QMouseEvent *) override;
//  void paintEvent(QPaintEvent *) override;
//  void scrollContentsBy(int dx, int dy) override;
//  void resizeEvent(QResizeEvent *) override;
//  void wheelEvent(QWheelEvent *) override;
//  void scaleContentsBy(qreal factor);

private:
//  qreal WAVE_RADIUS;
//  qreal _rangeX;
//  qreal _rangeY;
//  int _countOfComponents = 0;
//  bool _zoomIsTouching = false;
//  bool _editMode = false;
//  bool _addWaveMode = false;
//  bool _isAddPWaveTriggerPressed = false;
//  bool _isAddSWaveTriggerPressed = false;

//  QPointF calculatePickPosition(QPointF);

  QGraphicsTextItem *_status;
//  QRubberBand *rubberBand = nullptr;
//  QPoint _firstPoint;
//  QSizeF _sizeWaveItem = QSizeF(12, 1);

//signals:


private:
  QGraphicsRectItem *rect;

//  const QString EDIT_MODE_STRING = "Edit Mode";
  const QString OVERVIEW_MODE_STRING = "Overview Mode";
//  const QString ADD_WAVE_STRING = "Add Wave";
//  const int MICROSECONDS_IN_SECOND = 1000000;
//  const int MICROSECONDS_IN_MILISECOND = 1000;
//  const QSizeF DEFAULT_WAVEITEM_SIZE = QSizeF(12, 1);


};
} // namespace EventOperation
