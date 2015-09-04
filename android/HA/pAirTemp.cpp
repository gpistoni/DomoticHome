#include "pAirTemp.h"
#include "ui_pairtemp.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "HistogramView.h"

pAirTemp::pAirTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::pAirTemp)
{
    ui->setupUi(this);

    ui->label_header->setText("AIR TEMP");
    ui->label_footer->setText("----");

    std::map<double,double> histo;

    // Fill in points with n number of points
    for(int i = 0; i< 100; i++)
    {
        int x = 100 * qrand() / RAND_MAX;
        int y = 500 - 1000 * qrand() / RAND_MAX;
        histo[x]  = y;
    }

    // Create a view, put a scene in it and add tiny circles
    // in the scene
    HistogramView * view = new HistogramView();

    view->setHistogram(histo);
    ui->gridLayout->addWidget(view);
}

pAirTemp::~pAirTemp()
{
    delete ui;
}

