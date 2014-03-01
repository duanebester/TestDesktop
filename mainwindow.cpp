#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>
#include <QUrl>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QJsonDocument>
#include <QJsonArray>

static const char *REQUEST_URL = "http://localhost:8080/wpi/users/10";
//static const char *USER = "user";
//static const char *PASSWORD = "asas";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_progress->setRange(0,100);

    ui->m_progress->hide();

    m_network = new QNetworkAccessManager(this);
        QNetworkRequest request;
        //request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg(USER).arg(PASSWORD).toAscii()).toBase64());
        request.setUrl(QUrl(REQUEST_URL));
        QNetworkReply *reply = m_network->get(request);

        QObject::connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
                                SLOT(slotSetProgress(qint64,qint64)));
        QObject::connect(m_network, SIGNAL(finished(QNetworkReply *)),
                                    SLOT(slotRequestFinished(QNetworkReply *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotRequestFinished(QNetworkReply *reply)
{
    ui->m_progress->setValue(100);

    if (reply->error() > 0) {
        ui->lcdStatus->display("OFF");
    }
    else {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();

        // TODO: Poll for Status
        if (array.isEmpty()) {
            ui->lcdStatus->display("OFF");
        }
        else
        {
            ui->lcdStatus->display("hey");
        }

        qDebug() << data;

        ui->outputEdit->setText("0");
        ui->startEdit->setText("1000");
        ui->endEdit->setText("50000");
        ui->periodEdit->setText("500");
    }

    ui->m_progress->hide();
}

void MainWindow::slotSetProgress(qint64 received, qint64 total)
{
    ui->m_progress->show();
    if (total > 0 && received > 0) {
        ui->m_progress->setValue((int) total / received);
    }
}
