#ifndef HISTOGRAMVIEW_HPP
#define HISTOGRAMVIEW_HPP

#include <QGraphicsView>


class QGraphicsItemGroup;

namespace ise {
  class GrayScaleHistogram;
}


class HistogramView : public QGraphicsView
{
public:
  HistogramView(QWidget *parent = NULL);
  HistogramView(std::vector<double> &histo, QWidget *parent = NULL);

  /**
   * Set a new GrayScaleHistogram.
   * Will do a setMinMax().
   */
  virtual void setHistogram( std::vector<double> &histo );

  /**
   * Change aboslute min & max of histogram view,
   * without changing the underlying GrayScaleHistogram.
   * It is useful to move the levels outside the underlying GrayScaleHistogram limits
   * [when we change of color space, we can then transform the levels, before setting a new histogram]
   */
  virtual void setMinMax(int min, int max);

  inline int absoluteMin() const { return m_min; }
  inline int absoluteMax() const { return m_max; }

protected:
  void wheelEvent(QWheelEvent *);
  void populate( std::vector<double> &histo );


protected:
  static const int HEIGHT;

  QGraphicsItemGroup *m_histogramItem;
  double m_min;
  double m_max;

};

#endif /* ! HISTOGRAMVIEW_HPP */
