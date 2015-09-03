#ifndef HISTOGRAMVIEW_HPP
#define HISTOGRAMVIEW_HPP

#include <QGraphicsView>

class QGraphicsItemGroup;

class HistogramView : public QGraphicsView
{
public:
  HistogramView(QWidget *parent = NULL);
  HistogramView( std::map<double,double>  &histo, QWidget *parent = NULL);

  virtual void setHistogram( std::map<double,double> &histo );

  /**
   * Change aboslute min & max of histogram view,
   * without changing the underlying GrayScaleHistogram.
   * It is useful to move the levels outside the underlying GrayScaleHistogram limits
   * [when we change of color space, we can then transform the levels, before setting a new histogram]
   */
  virtual void setMinMax(int min, int max);

protected:
  void wheelEvent(QWheelEvent *event);
  void resizeEvent(QResizeEvent *event);

  void draw(QSize sz);

  template <class T>
  void addText( const T value, QPointF pos);
  void addAxis( const QSize &sz );

  int PosX( double value );
  int PosY( double value, const QSize &sz );

protected:
  QGraphicsItemGroup *m_histogramItems;
  QPen m_axisPen, m_textPen;

  static const int m_Border = 10;

  float m_xRatio, m_yRatio;
  double m_minX, m_minY, m_maxX, m_maxY;
  std::map<double,double>  m_histo;

};

#endif /* ! HISTOGRAMVIEW_HPP */
