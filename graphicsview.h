#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>


class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);
    void toDefault();

private:
    QPoint pos_saved;
    double scale_;
    void scrollContentsBy(int, int );
    void wheelEvent(QWheelEvent*);
    void mousePressEvent(QMouseEvent *event);

signals:
    void mousePressed(int x, int y);

};

#endif // GRAPHICSVIEW_H
