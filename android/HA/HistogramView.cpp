#include "HistogramView.h"

#include <iostream> //DEBUG

#include <cassert>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QWheelEvent>
#include <QPointF>
#include <QTime>
#include <QTextBlockFormat>
#include <QTextCursor>

double AutoRound(double d)
{
    if ( d<-9999 ) return round( d / 1000) * 1000;
    if ( d<-999.9 )  return round( d / 100) * 100;
    if ( d<-99.99 ) return round( d / 10) * 10;

    if ( d>9999 )  return (round( d / 1000)) * 1000;
    if ( d>999.9 )  return (round( d / 100)) * 100;
    if ( d>99.99 ) return (round( d / 10)) * 10;

    return round( d );
}

HistogramView::HistogramView(QWidget *parent)
    : QGraphicsView(parent),
      m_histogramItems(NULL),
      m_xRatio(1), m_yRatio(1),
      m_minX(0), m_maxX(0),
      m_minY(0), m_maxY(0)
{
    setScene(new QGraphicsScene(parent));

    m_axisPen.setColor( QColor(255,128,0) );
    m_axisPen.setWidth(2);

    m_gridPen.setColor( QColor(128,128,128) );
    m_gridPen.setStyle( Qt::DashDotLine );

    m_textPen.setColor( QColor(255,128,0) );

    m_measurePen.setColor( QColor(128,0,128) );

    m_shadowPen.setColor( QColor(192,192,192) );
}


HistogramView::HistogramView(std::map<double,double> &histo, QWidget *parent)
    : QGraphicsView(parent),
      m_histogramItems(NULL),
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

        m_minX = AutoRound( m_minX );
        m_minY = AutoRound( m_minY );

        m_maxX = AutoRound( m_maxX );
        m_maxY = AutoRound( m_maxY );
    }
}

//T is the numeric type of the value
template <class T>
void HistogramView::addText( const T value,
                             QPointF pos)
{
    QString str;
    str.setNum(value);

    QGraphicsTextItem *text = new QGraphicsTextItem( str );
    text->setPos(pos);
    //pos.setX( pos.x - text->boundingRect().width() ) ;
    m_histogramItems->addToGroup(text);
}

void HistogramView::addAxis( const QSize &sz )
{
    QPainterPath p;
    p.moveTo( m_Border, m_Border );
    p.lineTo( m_Border, sz.height() - m_Border );
    p.lineTo( sz.width()-m_Border, sz.height() - m_Border  );

    QGraphicsPathItem *pathItemS = new QGraphicsPathItem(p);
    pathItemS->setPen(m_shadowPen);
    pathItemS->moveBy(1,1);
    m_histogramItems->addToGroup(pathItemS);

    QGraphicsPathItem *pathItem = new QGraphicsPathItem(p);
    pathItem->setPen(m_axisPen);
    m_histogramItems->addToGroup(pathItem);
}

void HistogramView::addGridLine(  const double value, tAxis ax,  const QSize &sz )
{
    QPainterPath p;
    if (ax == H)
    {
        p.moveTo( m_Border/2,  PosY(value,sz) );
        p.lineTo( sz.width() - m_Border, PosY(value,sz)  );
        addText( value, QPointF( sz.width() - 3 * m_Border, PosY(value,sz) - 20 ));
    }
    else
    {
        p.moveTo( PosX(value), m_Border );
        p.lineTo( PosX(value), sz.height() - m_Border  );
        addText( value, QPointF( PosX(value), sz.height() - m_Border - 20 ) );
    }

    QGraphicsPathItem *pathItem = new QGraphicsPathItem(p);
    pathItem->setPen(m_gridPen);
    m_histogramItems->addToGroup(pathItem);
}

double HistogramView::PosX( double value )
{
    return 1.0 * m_Border + ( -m_minX + value ) * m_xRatio;
}

double HistogramView::PosY( double value, const QSize &sz )
{
    return 1.0 * sz.height() - m_Border - ( -m_minY + value ) * m_yRatio;
}

void HistogramView::draw( QSize sz )
{
    QGraphicsScene *sc = scene();
    assert(sc);

    m_xRatio = 1.0 * ( sz.width() - 4*m_Border ) / ( m_maxX - m_minX );
    m_yRatio = 1.0 * ( sz.height() - 2*m_Border ) / ( m_maxY - m_minY );

    // eleimino la vecchia scena
    if (m_histogramItems != NULL)
    {
        sc->removeItem(m_histogramItems);
        delete m_histogramItems;
        m_histogramItems = NULL;
    }
    m_histogramItems = new QGraphicsItemGroup;

    // inizio i disegni
    addAxis( sz );

    //texts on axes
    //addText( m_minY, QPointF( 0, PosY(m_minY,sz) ) );
    //addText( m_maxY, QPointF( 0, PosY(m_maxY,sz) ) );

    addGridLine( 0, H, sz );

    int nlines = 5;
    for (int i=0; i<nlines; i++)
        addGridLine(  AutoRound( m_minY + (m_maxY-m_minY)*i/nlines  ), H, sz );

    //vertical line histogram from zero
    const float y2 = PosY (0, sz);
    for (auto ih: m_histo)
    {
        const float x1 = PosX (ih.first);
        const float y1 = PosY (ih.second, sz);
        if (y1 != 0)
        {
            QGraphicsLineItem *pt = new QGraphicsLineItem( QLineF(x1, y2, x1, y1) );
            pt->setPen(m_measurePen);
            m_histogramItems->addToGroup(pt);
        }
    }

    sc->addItem(m_histogramItems);

    //update scene rectangle.
    QRectF rectSc = m_histogramItems->boundingRect();
    scene()->setSceneRect(rectSc);

    setRenderHint(QPainter::HighQualityAntialiasing, true);

    assert(scene()->sceneRect() == sceneRect());
}

void HistogramView::Shadowize( int px )
{
    foreach( QGraphicsItem *item, scene()->items( m_histogramItems->boundingRect() ) )
    {
       item->moveBy(1,1);
    }
}

void HistogramView::wheelEvent(QWheelEvent *event )
{
    Shadowize(2);
    /*  if (event->delta() > 0)
        scale(1.2, 1.2);
    else
        scale(1 / 1.2, 1 / 1.2);*/
}

void HistogramView::resizeEvent(QResizeEvent *event)
{
    static QTime ct;
    if ( QTime::currentTime() > ct )
    {
        ct  = QTime::currentTime().addMSecs(100);
        draw( event->size() );
    }
}

void HistogramView::setMinMax(int min ,int max)
{
    m_minX = min;
    m_maxX = max;
}
