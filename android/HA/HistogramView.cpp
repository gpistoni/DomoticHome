#include "HistogramView.h"

#include <iostream> //DEBUG

#include <cassert>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QWheelEvent>
#include <QPointF>

HistogramView::HistogramView(QWidget *parent)
    : QGraphicsView(parent),
      m_xRatio(1), m_yRatio(1),
      m_minX(0), m_maxX(0),
      m_minY(0), m_maxY(0)
{
    setScene(new QGraphicsScene(parent));

    m_axisPen.setColor( QColor(255,128,0) );
    m_axisPen.setWidth(2);

    m_textPen.setColor( QColor(255,128,0) );

}


HistogramView::HistogramView(std::map<double,double> &histo, QWidget *parent)
    : QGraphicsView(parent),
      m_xRatio(1), m_yRatio(1),
      m_minX(0), m_maxX(0),
      m_minY(0), m_maxY(0)
{
    //setAlignment(Qt::AlignCenter); //default
    setScene(new QGraphicsScene(parent));

    setHistogram(histo);
}

void HistogramView::setHistogram( std::map<double,double> &histo )
{
    QGraphicsScene *sc = scene();
    if (sc)
    {
        m_histo = histo;
    }
}

//T is the numeric type of the value
template <class T>
void HistogramView::addText( const T value,
                             QPointF pos)
{
 /*   QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(pos, pos2));
    line->setPen(m_textPen);
    m_histogramItems->addToGroup(line);
    */

    QString str;
    str.setNum(value);
    QGraphicsTextItem *text = new QGraphicsTextItem(str);
    text->setPos(pos);
    m_histogramItems->addToGroup(text);
}

void HistogramView::addAxis( const QSize &sz )
{
    QPainterPath p;
    p.moveTo( m_Border, sz.height() - m_Border );
    p.lineTo( sz.width()-m_Border, m_Border );
    p.moveTo( m_Border, sz.height() - m_Border );
    p.lineTo( m_Border, m_Border ); //y points downwards in Qt default coordinate system

    QGraphicsPathItem *pathItem = new QGraphicsPathItem(p);
    pathItem->setPen(m_axisPen);
    m_histogramItems->addToGroup(pathItem);
}

int HistogramView::PosX( double value )
{
   return m_Border + ( -m_minX + value ) * m_xRatio;
}

int HistogramView::PosY( double value, const QSize &sz )
{
   return sz.height() - m_Border - ( -m_minY + value ) * m_yRatio;
}

void HistogramView::draw( QSize sz )
{
    QGraphicsScene *sc = scene();
    assert(sc);

    m_minX = 1e20;
    m_maxX = -1e20;
    m_minY = 1e20;
    m_maxY = -1e20;

    for (auto ih: m_histo)
    {
        if ( ih.first < m_minX )  m_minX = ih.first;
        if ( ih.first > m_maxX )  m_maxX = ih.first;
        if ( ih.second < m_minY )  m_minY = ih.second;
        if ( ih.second > m_maxY )  m_maxY = ih.second;
    }

    if (m_maxX-m_minX < 1) m_maxX = m_minX + 1;
    if (m_maxY-m_minY < 1) m_maxY = m_minY + 1;


    const float m_xRatio = (sz.width()-2*m_Border) / ( m_maxX - m_minX);
    const float m_yRatio = (sz.height() -2*m_Border) / ( m_maxY - m_minY);

      // eleimino la vecchia scena
    if (m_histogramItem != NULL)
            {
                sc->removeItem(m_histogramItem);
                delete m_histogramItem;
                m_histogramItem = NULL;
            }

    m_histogramItem = new QGraphicsItemGroup;


    // inizio i disegni
    addAxis( sz );

    //texts on axes
    addText( 0, QPointF(m_Border, m_maxY * m_yRatio));

    /*
    addTextOnX(m_histogramItems, axisPen, m_minX, m_Border,
               QPointF(m_Border+1, 1));

    addTextOnX(m_histogramItems, axisPen, m_maxX, m_Border,
               QPointF(m_Border, m_Border));*/

    //vertical line histogram
    const float y2 = sz.height()-m_Border;
    QPen barPen(QColor(0,0,0), 1);
    for (auto ih: m_histo)
    {
        const float x1 = m_Border + ( -m_minX + ih.first) * m_xRatio ;
        const float y1 = sz.height()- m_Border - (-m_minY + ih.second) * m_yRatio;
        if (y1 != 0)
        {
            QGraphicsLineItem *bar = new QGraphicsLineItem(QLineF(x1, y2, x1, y1));
            bar->setPen(barPen);
            m_histogramItems->addToGroup(bar);
        }
    }

    sc->addItem(m_histogramItems);

    //update scene rectangle.
    QRectF rectSc = m_histogramItems->boundingRect();
    scene()->setSceneRect(rectSc);

    assert(scene()->sceneRect() == sceneRect());
}


void HistogramView::wheelEvent(QWheelEvent *event )
{
 if (event->delta() > 0)
   scale(1.2, 1.2);
 else
   scale(1 / 1.2, 1 / 1.2);
}

void HistogramView::resizeEvent(QResizeEvent *event)
{
    draw( event->size() );
}


void HistogramView::setMinMax(int min ,int max)
{
    m_minX = min;
    m_maxX = max;
}
