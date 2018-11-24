#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../QLibrary/QHttpClient.h"
#include "qdebug.h"
#include "immintrin.h"
#include "qjsondocument.h"
//#include "QJsonObject.h"

void ContrastStretch(QImage &source)
{
    uchar* ptr = source.bits();

    for (int j = 0; j < source.byteCount(); ++j)
    {
        ptr[j] = ptr[j]*64;
    }
 //   qDebug() << CSQHttpClient::Timer.elapsed() << " - ContrastStretch bytes:" << source.byteCount();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString host = "127.0.0.1";
    quint16 port = 8080;

    CSQHttpClient::Setup(host, port, 10000 );

    try
    {
        //QString sstep = CSQHttpClient::GetValue( "Work.Elab.StepDone" );
        //ui->label_step->setText(QString(sstep));

 /*       // lista  ------------------------------------------------------------------------
        QStringList stepList = CSQHttpClient::GetStepList();
        ui->wStepList->clear();
        for ( QString var : stepList )
        {
            ui->wStepList->addItem(var);
        }

        // http request --------------------------------------------------------
        {
            CSQHttpClient client;
            CSQHttpClient::Timer.start();
            qDebug() << CSQHttpClient::Timer.elapsed() << " - " << QString("START GetProcessed --------------------").toLatin1();
            client.GetImage( "action?GetProcessed", m_image1 );

        }
*/
        QString str = CSQHttpClient::GetValue_Json();
        ui->labelLog->setText(str);

        //****************************************
        QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject jsonRoot = jsonDoc.object();

        QJsonObject jT1 = jsonRoot["T1"].toObject();
        QJsonValue v1 = jT1["name"];

        ui->listWidget->addItem( v1.toString() );

        QJsonValue v2 = jT1["extra"];
        ui->listWidget->addItem( v2.toString() );

        QJsonValue v3 = jT1["nonextra"];
        ui->listWidget->addItem( v3.toString() );
        //****************************************

       /* //new ------------------------------------------------------------------------
        QStringList states;

        states.push_back( CSQHttpClient::GetValue( "Work.General.StateHi" ) );
        states.push_back( CSQHttpClient::GetValue( "Work.General.StateLow" ) );

        ui->label_stateHi->setText("-");
        ui->label_stateLow->setText("-");
        if (states.size()>0)
            ui->label_stateHi->setText( states[0] );

        if (states.size()>1)
            ui->label_stateLow->setText( states[1] );
                    */

    }
    catch(...)
    {
    }
}

