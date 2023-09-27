#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_encrypt_clicked();

    void on_btn_decrypt_clicked();

private:
    Ui::MainWindow *ui;
//    QString _filePath;

private:
    QString encrypt(const QString& plainText);//加密函数
    QString decrypt(const QString& encryptedText);//解密函数
};
#endif // MAINWINDOW_H
