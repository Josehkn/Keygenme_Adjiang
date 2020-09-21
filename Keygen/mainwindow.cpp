#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keygen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Generate_clicked()
{
   QPlainTextEdit &pte_nombre = *ui->pte_nombre;
   QString nombre = pte_nombre.toPlainText(); //obtener el nombre para pasarlo por los algoritmos criptograficos
   if (nombre.toStdString() != "")
   {
        ui->pte_serial->setPlainText(serial_generate(nombre));
   }
}

void MainWindow::on_About_clicked()
{
    QMessageBox message(QMessageBox::Information, QObject::tr("About"), QObject::tr("Le dedico este keygen a pu\n Y un especial agradecimiento a JoeCracker y Apuromafo; que con sus palabras y ánimos"));

    message.setIconPixmap(QPixmap(":/po/poro.jpg"));
    message.addButton(QMessageBox::Close);
    message.exec();
}
