#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include "util/utility.h"
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    connect(ui->tableWidget, SIGNAL(currentCellChanged(int, int,int,int)), this, SLOT(onCellChanged(int, int,int,int)));


    reload();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addBtn_clicked()
{
    QNetworkAccessManager* mgr = new QNetworkAccessManager(this);

    _request = new QNetworkRequest(QUrl("http://172.16.17.70:8181/add_user_info_list/"));
    _request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect(mgr ,SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));

    _params.clear();
    _params.addQueryItem("userId", "dfd");
    _params.addQueryItem("password_md5", "423424");

    QString name = ui->lineEditName->text();
    QString sex = ui->lineEditSex->text();
    QString type = ui->lineEditType->text();

    _params.addQueryItem("NAME", name);
    _params.addQueryItem("SEX", sex);
    _params.addQueryItem("TYPE", type);

    QByteArray arr = _params.toString().toUtf8();
    _reply = mgr->post(*_request, arr);
}

void MainWindow::on_editBtn_clicked()
{
    QNetworkAccessManager* mgr = new QNetworkAccessManager(this);

    _request = new QNetworkRequest(QUrl("http://172.16.17.70:8181/update_user_info_list/"));
    _request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect(mgr ,SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));

    _params.clear();
    _params.addQueryItem("userId", "dfd");
    _params.addQueryItem("password_md5", "423424");

    int row=ui->tableWidget->currentRow();
    QString user_id = ui->tableWidget->item(row,0)->text();
    QString name = ui->lineEditName->text();
    QString sex = ui->lineEditSex->text();
    QString type = ui->lineEditType->text();

    QStringList params;
    params.append(user_id + "&" + name + "&" + sex + "&" + type);
    _params.addQueryItem("USER_INFO_LIST", params.join(","));

    QByteArray arr = _params.toString().toUtf8();
    _reply = mgr->post(*_request, arr);
}

void MainWindow::on_delBtn_clicked()
{
    QNetworkAccessManager* mgr = new QNetworkAccessManager(this);

    _request = new QNetworkRequest(QUrl("http://172.16.17.70:8181/delete_user_info_list/"));
    _request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect(mgr ,SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));

    _params.clear();
    _params.addQueryItem("userId", "dfd");
    _params.addQueryItem("password_md5", "423424");

    int row=ui->tableWidget->currentRow();
    QString user_id = ui->tableWidget->item(row,0)->text();

    _params.addQueryItem("ID", user_id);

    QByteArray arr = _params.toString().toUtf8();
    _reply = mgr->post(*_request, arr);
}

void MainWindow::onFinish(QNetworkReply *reply)
{
    QString replyStr = reply->readAll();
    _dataJSON = Utility::getJSONFromString(replyStr);

    if (_dataJSON.contains("req_path")) {
        if (_dataJSON.contains("req_result"))

        if (_dataJSON.contains("data")) {
            QJsonArray dataArray = _dataJSON["data"].toArray();
            int rowCount = dataArray.count();
            ui->tableWidget->setRowCount(rowCount);

            for (int i=0; i<rowCount; i++) {
                QJsonObject rowJSON = dataArray.at(i).toObject();

                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(rowJSON["ID"].toString()));
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(rowJSON["NAME"].toString()));
                ui->tableWidget->setItem(i, 2, new QTableWidgetItem(rowJSON["SEX"].toString()));
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(rowJSON["TYPE"].toString()));

            }
        }
    }
}

void MainWindow::onCellChanged(int row, int column, int preRow, int preColumn)
{
    Q_UNUSED(preRow);
    Q_UNUSED(preColumn);
    if (row == -1){
        return;
    }
    QString name = ui->tableWidget->item(row,1)->text();
    QString sex = ui->tableWidget->item(row,2)->text();
    QString type = ui->tableWidget->item(row,3)->text();
    ui->lineEditName->setText(name);
    ui->lineEditSex->setText(sex);
    ui->lineEditType->setText(type);
}

void MainWindow::on_clear_clicked()
{
    ui->lineEditName->setText("");
    ui->lineEditSex->setText("");
    ui->lineEditType->setText("");
}

void MainWindow::reload()
{
    QNetworkAccessManager* mgr = new QNetworkAccessManager(this);

    _request = new QNetworkRequest(QUrl("http://172.16.17.70:8181/get_user_info_list/"));
    _request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
    connect(mgr ,SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));


    if (_request->url().toString().indexOf("http") == -1) {
        return;
    }
//    if (_reply != NULL) {
//        delete _reply;
//    }

    _params.addQueryItem("userId", "dfd");
    _params.addQueryItem("password_md5", "423424");
    QByteArray arr = _params.toString().toUtf8();
    _reply = mgr->post(*_request, arr);

 //   connect(_reply, SIGNAL(finished()), this, SLOT(onNetReplyFinished()));
}

void MainWindow::on_refreshBtn_clicked()
{
    reload();
}
