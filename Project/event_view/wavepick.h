#pragma once

#include "data/seismwavepick.h"

#include <QBrush>
#include <QGuiApplication>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>

#include <iostream>
#include <variant>

QT_BEGIN_NAMESPACE
class QGraphicsSceneEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE;

namespace EventOperation {
class WavePick : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  WavePick(Data::SeismWavePick::Type, QGraphicsItem *, QChart *, QPointF,
           QSizeF, QBrush, qreal);

  /* Устанавливает якорь для основного pick*/
  void setAnchor(const QPointF);
  void setPickColor(const QColor);

  void updateGeometry();

  qreal getXPos() { return _anchor.x(); }
  QSizeF scallByAxis(QSizeF scaleS);
  Data::SeismWavePick::Type getType() { return _type; }
  int getComponentAmount() { return static_cast<int>(_anchor.x()); }

  QRectF boundingRect() const;
  void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
  void resize(QSizeF);

signals:
  void changed(float pick);
  void deleted();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);

private:
  const float DRAG_OFFSET = 0.0007;
  const qreal MAX_WIDTH;
  const QSizeF DEFAULT_SIZE;
  const qreal MAX_BORDER;
  Data::SeismWavePick::Type _type;
  QChart *_chart;
  QPointF _pos;
  QSizeF _size;

  QPointF _anchor;
  QRectF _rect;
  QBrush _pickBrush;

private:
};
} // namespace EventOperation
