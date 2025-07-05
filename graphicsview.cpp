#include "graphicsview.h"
#include "qapplication.h"
#include <QScrollBar>
#include <QMimeData>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setSceneRect(0, 0, 820, 720);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    scale_ = 1;

}

bool is_moving = 0;

void GraphicsView::scrollContentsBy(int dx, int dy) {
    QGraphicsView::scrollContentsBy(dx,dy);
    QRect rect= this->sceneRect().toRect();
    if (this->horizontalScrollBar()->value() == this->horizontalScrollBar()->maximum()) {
        rect.adjust(0,0,(10+abs(this->sceneRect().left())) * (1/scale_),0);
    }
    if (this->horizontalScrollBar()->value() == this->horizontalScrollBar()->minimum()) {
        rect.adjust(-(10+abs(this->sceneRect().right()))* (1/scale_),0,0,0);
    }
    if (this->verticalScrollBar()->value() == this->verticalScrollBar()->maximum()) {
        rect.adjust(0,0,0,( 10+abs(this->sceneRect().top()))* (1/scale_));
    }
    if (this->verticalScrollBar()->value() == this->verticalScrollBar()->minimum()) {
        rect.adjust(0,-(10+abs(this->sceneRect().bottom()))* (1/scale_),0,0);
    }
    this->setSceneRect(rect);
    this->scene()->update();
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto coordsInScene = this->mapToScene(event->pos());
        emit mousePressed(coordsInScene.x(), coordsInScene.y());
    }
    QGraphicsView::mousePressEvent(event);

}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
   {
       QGraphicsView::wheelEvent(event);
   }
    else {
          if(event->angleDelta().ry() != 0 ) {
                if((scale_ >= 10 && event->angleDelta().ry() < 0) || (scale_ < 0.1 && event->angleDelta().ry() > 0) || (scale_ <= 10 && scale_ >=0.1)) {
                scale(event->angleDelta().ry()/abs(event->angleDelta().ry()) * 0.05 + 0.99, event->angleDelta().ry()/abs(event->angleDelta().ry()) * 0.05 + 0.99);
                scale_ *= (event->angleDelta().ry()/abs(event->angleDelta().ry()) * 0.05 + 0.99);
          }
        }
    }
}

void GraphicsView::toDefault() {
    scale_ = 1;
    this->resetTransform();

    this->centerOn(this->scene()->sceneRect().center());
}


