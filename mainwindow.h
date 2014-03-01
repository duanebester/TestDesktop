#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QNetworkAccessManager>


namespace Ui {
class MainWindow;
class QLabel;
class QProgressBar;
class QNetworkAccessManager;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotRequestFinished(QNetworkReply *);
    void slotSetProgress(qint64, qint64);

private:
    Ui::MainWindow *ui;
    QProgressBar *m_progress;
    QNetworkAccessManager *m_network;
};

#endif // MAINWINDOW_H
