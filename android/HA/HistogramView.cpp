#include "HistogramView.h"

#include <iostream> //DEBUG

#include <cassert>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QWheelEvent>


int WIDTH = 255;
const int HistogramView::HEIGHT = 100;

HistogramView::HistogramView(QWidget *parent)
    : QGraphicsView(parent),
      m_histogramItem(NULL),
      m_min(0), m_max(0)
{
    setScene(new QGraphicsScene(parent));
}


HistogramView::HistogramView(std::vector<double> &histo, QWidget *parent)
    : QGraphicsView(parent),
      m_histogramItem(NULL),
      m_min(0), m_max(0)
{
    //setAlignment(Qt::AlignCenter); //default
    setScene(new QGraphicsScene(parent));

    setHistogram(histo);
}

void HistogramView::setHistogram( std::vector<double> &histo )
{
    QGraphicsScene *sc = scene();
    if (sc)
    {
        if (m_histogramItem != NULL)
        {
            sc->removeItem(m_histogramItem);
            delete m_histogramItem;
            m_histogramItem = NULL;
        }
        populate(histo);
    }
}

//T is the numeric type of the value
template <class T>
void addTextOnX(QGraphicsItemGroup *gig,
           const QPen &pen,
           const T value,
           const int scaleWidth,
           QPointF pos)
{

    const QPointF pos2(pos.x(), pos.y() + scaleWidth);

    QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(pos, pos2));
    line->setPen(pen);
    gig->addToGroup(line);

    QString str;
    str.setNum(value);
    QGraphicsTextItem *text = new QGraphicsTextItem(str);
    text->setPos(pos2.x() - text->boundingRect().width()/2,
                 pos2.y());
    gig->addToGroup(text);
}

//T is the numeric type of the value
template <class T>
void addTextOnY(QGraphicsItemGroup *gig,
           const QPen &pen,
           const T value,
           const int scaleWidth,
           QPointF pos)
{

    const QPointF pos2(pos.x() - scaleWidth, pos.y());

    QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(pos, pos2));
    line->setPen(pen);
    gig->addToGroup(line);

    QString str;
    str.setNum(value);
    QGraphicsTextItem *text = new QGraphicsTextItem(str);
    text->setPos(pos2.x() - text->boundingRect().width(),
                 pos2.y() - text->boundingRect().height()/2);
    gig->addToGroup(text);
}




void HistogramView::populate( std::vector<double> &histo )
{
    QGraphicsScene *sc = scene();
    assert(sc);

    m_min = 1e20;
    m_max = -1e20;

    for (auto ih: histo)
    {
        if ( ih < m_min)  m_min = ih;
        if ( ih > m_max)  m_max = ih;
    }

    if (m_max < m_min)
        return;

    //compute max frequency
    size_t maxFrequency = 0;
    for (size_t i=0; i<histo.size(); ++i)
        if (histo[i] > maxFrequency)
            maxFrequency = histo[i];

    const int width = static_cast<int>(m_max - m_min +1);
    const int height = maxFrequency == 0 ? 1 : static_cast<int>(maxFrequency);

    const float xRatio = 1.0; //WIDTH/static_cast<float>(width);
    const float yRatio = - HEIGHT/static_cast<float>(height); //y points downwards

    assert(m_histogramItem == NULL);

    m_histogramItem = new QGraphicsItemGroup;


    const int x0 = -1 + m_min;
    const int x1 = x0 + width*xRatio;

    //axes
    QPen axisPen(QColor(255,0,0), 1);
    QPainterPath p;
    p.moveTo(x0, 1);
    p.lineTo(x1, 1);
    p.moveTo(x0, 1);
    p.lineTo(x0, -HEIGHT); //y points downwards in Qt default coordinate system
    QGraphicsPathItem *pathItem = new QGraphicsPathItem(p);
    pathItem->setPen(axisPen);
    m_histogramItem->addToGroup(pathItem);


    const int GRAD_WIDTH = 10;

    //texts on axes
    addTextOnY(m_histogramItem, axisPen, maxFrequency, GRAD_WIDTH,
               QPointF(x0, static_cast<double>(maxFrequency * yRatio)));

    addTextOnX(m_histogramItem, axisPen, m_min, GRAD_WIDTH,
               QPointF(x0+1, 1));

    addTextOnX(m_histogramItem, axisPen, m_max, GRAD_WIDTH,
               QPointF(x1, 1));



    //bars of histogram itself
    QPen barPen(QColor(0,0,0), 1);
    for (size_t i=0; i<histo.size(); ++i) {

        const float x = m_min + i * xRatio ;
        const float y = histo[i] * yRatio;
        if (y != 0) {
            QGraphicsLineItem *bar = new QGraphicsLineItem(QLineF(x, 0, x, y));
            bar->setPen(barPen);
            m_histogramItem->addToGroup(bar);
        }
    }


    sc->addItem(m_histogramItem);


    //update scene rectangle.
    QRectF rectSc = m_histogramItem->boundingRect();
    scene()->setSceneRect(rectSc);

    assert(scene()->sceneRect() == sceneRect());


    //!!! How to have a correct size ? without scrollbars ?

    //ensureVisible(m_histogramItem);

    //fitInView(rectSc);
    //ensureVisible(rectSc, margin, margin);


    //const QRectF rectSc = scene()->sceneRect();
    //updateSceneRect(rectSc);

    /*
  //will ensure that we have no scrollbar
  // but once the parent widget is resized, it will never shrinks...
  // [QuantifLevelDialog : K1K2K3 color space, change back and forth between K1 & K2 & K3 channels]
  const int margin = 10;
  const QSize newSize = QSize(static_cast<int>(rectSc.width()+0.5+margin),
                  static_cast<int>(rectSc.height()+0.5+margin));
  setMinimumSize(newSize);
  */

}


void
HistogramView::wheelEvent(QWheelEvent * /* event */)
{
    /*
 if (event->delta() > 0)
   scale(1.2, 1.2);
 else
   scale(1 / 1.2, 1 / 1.2);
 //centerOn(127,0);
 */
}


void
HistogramView::setMinMax(int min ,int max)
{
    m_min = min;
    m_max = max;
}
