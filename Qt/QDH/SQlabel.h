#ifndef CSQLabel_H
#define CSQLabel_H

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

#include <QPixmap>
#include <QResizeEvent>
#include <QWheelEvent>

#include <QDialog>
#include <QWindow>
#include <QLayout>
#include <QPaintEvent>


class CSQLabel : public QLabel
{
	Q_OBJECT

public:
    explicit CSQLabel(QWidget *parent = nullptr);
	~CSQLabel();
	CSQLabel(const CSQLabel &cp);

    void SetImage(QImage &image);
	void resizeEvent(QResizeEvent *event);
	
	void EnableMouseEvent();
	void DisableMouseEvent();

	void EnableFullScreen(bool enable, int startX, int startY, int width, int height);
	void DisableFullScreen();

private:
    void Show(QBitmap image);

};

#endif // CSQLabel_H
