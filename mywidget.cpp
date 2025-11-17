#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>

QString mFilename="C:/test/myfile.txt";

void Write(QString Filename,QString str)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList ColTotle;
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *col1,*col2,*col3,*col4;
    col1=new QTableWidgetItem(QString(ui->lineEdit->text()));
    col2=new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    col3=new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    col4=new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,col1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,col2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,col3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,col4);
}

void MyWidget::on_pushButton_2_clicked()
{
    QString saveFile="";
    mFilename=QFileDialog::getSaveFileName(this,"匯出",".");
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            saveFile+=ui->tableWidget->item(i,j)->text()+",";
        }
        saveFile+="\n";
    }
    Write(mFilename,saveFile);
}


void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入", ".");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Could not open the file for reading!";
        return;
    }

    QTextStream in(&file);
    QString line;

    ui->tableWidget->setRowCount(0);

    while (!in.atEnd()) {
        line = in.readLine();

        QStringList fields = line.split(",");

        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);

        for (int i = 0; i < fields.size() && i < ui->tableWidget->columnCount(); ++i) {
            ui->tableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
        }
    }

    file.close();
}



void MyWidget::on_pushButton_4_clicked()
{
    on_pushButton_2_clicked();
    close();
}

