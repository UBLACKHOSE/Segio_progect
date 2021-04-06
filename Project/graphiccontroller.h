#pragma once

#include <QPainter>
#include <QPixmap>

#include "chartgesture.h"
#include "data/seismevent.h"
#include "event_view/graphic_view.h"
#include "seismogramm.h"

#include <QtCharts>

namespace Data {
class SeismEvent;
class SeismComponent;
class SeismTrace;
} // namespace Data

namespace EventOperation {
class WiggleWidget;
class HideComponentWidget;
class ClippingWidget;
class GainWidget;
class HideWavePointsWidget;
class ChangeBorderOnPolarWidget;
class GraphicController : public QFrame {
  Q_OBJECT
public:
  explicit GraphicController(QWidget *parent = nullptr);

  ChartGesture *getModel() const { return _chart; }
  void setChart(ChartGesture *chart) { _chart = chart; }
  void setView(GraphicView *view) { _view = view; }

  void draw(Seismogramm*);

  void updateEventName(const QString &);
  void setGainCoefficient(const float gainCoefficient);
  void setClippingValue(const float clippingValue);
  void setWiggle(const int status);

  void clear();

private:
  //  QWidget *_allView;
  GraphicView *_view;
  Data::SeismEvent const *_event;

  float _norm;
  float _rangeAxisX;
  float _rangeAxisY;
  float _clipping = 1.0f;
  float _gain = 1.0f;
  bool _isPositiveWiggleSet = false;
  bool _isNegativeWiggleSet = false;



  ChartGesture *_chart;


  QValueAxis *_axisX = new QValueAxis;
  QValueAxis *_axisY = new QValueAxis;
  QList<QAreaSeries *> _positiveWiggleSeries;
  QList<QAreaSeries *> _negativeWiggleSeries;
  QList<QLineSeries *> _allSeries;

  const qreal AMPLITUDE_SCALAR = 0.1;
  const float NORMED = 2.1f;
  const int GRAPH_WIDHT = 750;
  const int GRAPH_HEIGHT = 470;
  const int MICROSECONDS_IN_SECOND = 1000000;
  const int MICROSECONDS_IN_MILISECOND = 1000;

private:
  WiggleWidget *_wiggleWidget;
  ClippingWidget *_clippingWidget;
  GainWidget *_gainWidget;
  ChangeBorderOnPolarWidget *_changeBorderWidget;

  QPushButton *_addWaveButton;
  QAction *_addPWave;
  QAction *_addSWave;

  QPushButton *_screenButton;

signals:


private:
  void addTraceSeries(Seismogramm*);
  void addWiggle(bool t); // true is positive, false is negative
  void settingAreaSeries(QAreaSeries *series);
  void setAxesY(int);
  void setAxesX(int);
  void getRange(Qt::Orientation, Data::SeismEvent const *const);
  void removeAllSeries();

  void updateSeries();
  double findPointAroundZero(int, QPointF &, QPointF &);
  void deleteAllWiggle();

  void showToolsMenu();
  void hideToolsMenu();
};

} // namespace EventOperation
