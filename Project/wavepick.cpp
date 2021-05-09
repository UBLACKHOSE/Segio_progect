#include "wavepick.h"

#include <QtCharts/QChart>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <type_traits>

#include <iostream> // TODO: remove

namespace EventOperation {
WavePick::WavePick(Data::SeismWavePick::Type type, QGraphicsItem *parent,
                   QChart *chart, QPointF pos, QSizeF size, QBrush brush,
                   qreal maxBorder)
    : QGraphicsItem(parent), _chart(chart), _pos(pos), _size(size),
      _pickBrush(brush), DEFAULT_SIZE(size), MAX_WIDTH(size.width()),
      MAX_BORDER(maxBorder) {
  setFlag(QGraphicsItem::ItemIgnoresTransformations);
  _type = type;
  _anchor = pos;
  setPos(_anchor);
  _rect = QRectF(0, 0, size.width(), size.height());
  updateGeometry();
}

void WavePick::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                     QWidget *) {
  QPainterPath path;
  path.addRect(_rect);

  painter->setPen(Qt::NoPen);
  painter->setBrush(_pickBrush);
  painter->drawPath(path);
}

void WavePick::resize(QSizeF scaleC) {
  _size =
      QSizeF(_size.width() * scaleC.width(), _size.height() * scaleC.height());
  _rect.setSize(_size);
}

void WavePick::setAnchor(const QPointF point) { _anchor = point; }

void WavePick::updateGeometry() {
  prepareGeometryChange();
  _rect.moveCenter(QPointF(0, 0));
  setPos(_chart->mapToPosition(_anchor));
}

QSizeF WavePick::scallByAxis(QSizeF scaleS) {
  qreal scaleY = scaleS.height();
  qreal scaleX = scaleS.width();
  _size.setWidth(_size.width() * scaleY); // some optimal const
  _size.setHeight(3);
  _rect.setSize(_size);
  return _rect.size();
}

// rect from left border to right border.
QRectF WavePick::boundingRect() const {
  QPointF anchor = mapFromParent(_chart->mapToPosition(_anchor));
  QRectF rect;
  rect.setLeft(qMin(_rect.left(), _anchor.x()));
  rect.setRight(qMax(_rect.right(), anchor.x()));
  rect.setTop(qMin(_rect.top(), _anchor.y()));
  rect.setBottom(qMax(_rect.bottom(), _anchor.y()));
  return rect;
}

void WavePick::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (event->buttons() == Qt::RightButton &&
      (Qt::AltModifier == QGuiApplication::keyboardModifiers()) &&
      abs(_anchor.y() - _chart->mapToValue(mapToParent(event->pos())).y()) <=
          DRAG_OFFSET) {
    emit deleted();
  }
  event->setAccepted(true);
}

void WavePick::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton &&
      (Qt::AltModifier == QGuiApplication::keyboardModifiers())) {
    QPointF newPosition =
        QPointF(_chart->mapToValue(mapToParent(event->pos())));
    if (newPosition.y() < MAX_BORDER && newPosition.y() > 0) {
      setPos(QPointF(
          pos().x(),
          mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton))
              .y()));
      _anchor = QPointF(_anchor.x(), newPosition.y());
      updateGeometry();
    }
    return;
  }
}

void WavePick::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  emit changed(_anchor.y());
}

void WavePick::mouseDoubleClickEvent(
    QGraphicsSceneMouseEvent *event) // second variant delete pick
{
  qreal newY = QPointF(_chart->mapToValue(mapToParent(event->pos()) -
                                          event->buttonDownPos(Qt::LeftButton)))
                   .y();
  _anchor = QPointF(_anchor.x(), newY);
}

} // namespace EventOperation
