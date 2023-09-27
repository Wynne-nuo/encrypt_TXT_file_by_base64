#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    _filePath = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_encrypt_clicked()
{
    //打开一个文件对话框，并获取选择的文件路径
    QString filePath = "";
    filePath = QFileDialog::getOpenFileName();
    qDebug()<<"要加密的文件路径为： "<<filePath;

    QString encryptText;
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly| QIODevice::Text)){
        QTextStream in(&inputFile);
        QString dataText = in.readAll();
        inputFile.close();
        qDebug()<<"-----data:\n"<<dataText;

        encryptText = encrypt(dataText);
        qDebug()<<"-----encryptText:\n"<<encryptText;
    }

    QFile outputFile(filePath);
    if (outputFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&outputFile);
        out << encryptText;
        outputFile.close();
        qDebug() << "encrypt completed.";
    } else {
        qDebug() << "Failed to open output file.";
    }
}

void MainWindow::on_btn_decrypt_clicked()
{
    //打开一个文件对话框，并获取选择的文件路径
    QString filePath = "";
    filePath = QFileDialog::getOpenFileName();
    qDebug()<<"要解密的文件路径为： "<<filePath;

    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly| QIODevice::Text)) {
        QTextStream in(&inputFile);
        QString encryptedText = in.readAll();
        inputFile.close();
        qDebug()<<"-----encryptedText:\n"<<encryptedText;
        QString decryptedText = decrypt(encryptedText);

        QFile outputFile(filePath);
        if (outputFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&outputFile);
            out << decryptedText;
            outputFile.close();
            qDebug() << "Decryption completed.";
            qDebug() <<"-----decryptedText:\n"<<decryptedText;
        } else {
            qDebug() << "Failed to open output file.";
        }
    } else {
        qDebug() << "Failed to open input file.";
    }
}

QString MainWindow::encrypt(const QString &plainText)
{
    QByteArray byteArray = plainText.toUtf8();
    QByteArray encryptedData = byteArray.toBase64();
    return QString(encryptedData);
}

QString MainWindow::decrypt(const QString &encryptedText)
{
    QByteArray encryptedData = encryptedText.toUtf8();
    QByteArray decryptedData = QByteArray::fromBase64(encryptedData);
    return QString(decryptedData);
}

