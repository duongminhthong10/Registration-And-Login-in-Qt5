#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QSqlQuery>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->username->setPlaceholderText("Enter your UserName");
    ui->password->setPlaceholderText("Enter your Password");
    ui->email->setPlaceholderText("Enter your Email @gmail.com");
    ui->phone->setPlaceholderText("Enter your PhoneNumber");
    ui->usernameLogin->setPlaceholderText("Enter your UserName");
    ui->passwordLogin->setPlaceholderText("Enter your Password");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerBtn_clicked()
{

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("qt5register");

    if(database.open()){

        QString username = ui->username->text();
        QString password = ui->password->text();
        QString email = ui->email->text();
        QString phone = ui->phone->text();

        QSqlQuery qry;
        qry.prepare("INSERT INTO users (username, password, email, phone)"
                    "VALUES (:username, :password, :email, :phone)");
        qry.bindValue(":username",username);
        qry.bindValue(":password",password);
        qry.bindValue(":email",email);
        qry.bindValue(":phone",phone);

        if(qry.exec()){
            QMessageBox::information(this,"Inserted","Inserted Data Successfully");
        }
        else
        {
            QMessageBox::warning(this,"Not Connected","Inserted Failed");
        }


    }
    else
    {
        QMessageBox::warning(this,"Not connected","Connected is failed");
    }

}


void MainWindow::on_loginBtn_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL","Connect");
    db.setHostName("localhost");
    db.setPassword("");
    db.setUserName("root");
    db.setDatabaseName("qt5register");
    QString username = ui->usernameLogin->text();
    QString password = ui->passwordLogin->text();

    if(db.open()){
        // Creating My Quereis
        //QMessageBox::information(this,"Database Success","Login Success");
        QSqlQuery query(QSqlDatabase::database("Connect"));
        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));
        query.bindValue(":username",username);
        query.bindValue(":password",password);
        if(!query.exec())
        {
            QMessageBox::information(this,"Failed","Query Failed to Execute");
        }
        else{
            if(query.next()){
            QString usernameFromDB = query.value(1).toString();
            QString passwordFromDB = query.value(2).toString();

            if(usernameFromDB == username && passwordFromDB == password)
            {
                QMessageBox::information(this,"Success","Login Success");

                MyDialog dialog ;
                dialog.setModal(true);
                dialog.exec();
            }

        }
            else
            {
                QMessageBox::information(this,"Failed","Login Failed");
            }
        }


    }
    else
    {
        QMessageBox::warning(this,"Database Failed","Login ERROR");
    }
}


