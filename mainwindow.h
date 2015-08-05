#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onFinish(QNetworkReply *reply);
private slots:
    void on_addBtn_clicked();

    void on_editBtn_clicked();

    void on_delBtn_clicked();

    void onCellChanged(int row, int column, int preRow, int preColumn);
    void on_clear_clicked();

    void on_refreshBtn_clicked();

private:
    void reload();
    Ui::MainWindow *ui;
    QNetworkRequest* _request;
    QJsonObject _dataJSON;
    QUrlQuery _params;
    QNetworkReply* _reply;
};

#endif // MAINWINDOW_H
