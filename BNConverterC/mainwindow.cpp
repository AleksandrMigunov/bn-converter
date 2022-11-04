/* Copyright (C) 2022 Aleksandr Migunov

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
  
You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>. */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "convert.h"
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

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

//closing the program
void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox* messagebox = new QMessageBox (QMessageBox::Question,
                                               tr("Confirm Dialog"), tr("Really quit?"),
                                               QMessageBox::Yes | QMessageBox::No, this);
    messagebox->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox->setButtonText(QMessageBox::No, tr("No"));
    int n = messagebox->exec();
    delete messagebox;

    if (n == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionNew_original_triggered()
{
    ui->textEdit->clear();
}

void MainWindow::on_actionNew_converted_triggered()
{
    ui->textEdit_2->clear();
}

void MainWindow::on_actionOpen_original_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("Text Files(*.txt)"));
    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");

            QString text = in.readAll();
            File.close();
            ui->textEdit->setAcceptRichText(false);
            ui->textEdit->setText(text);

        }
        else {
            QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
        }
    }
}

void MainWindow::on_actionOpen_converted_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("Text Files(*.txt)"));
    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");

            QString text = in.readAll();
            File.close();

            ui->textEdit_2->setAcceptRichText(false);
            ui->textEdit_2->setText(text);
        }
        else {
            QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
        }
    }
}

void MainWindow::on_actionSave_original_triggered()
{
    ui->textEdit->setReadOnly(false);
    ui->textEdit->setAcceptRichText(false);

    QString file = "";

    file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                        tr("Text Files (*.txt)"));

    if(!file.isEmpty())
    {
        QDir direct;
        QString dir = direct.filePath(file);
        QString FileName = dir;
        QFile File(FileName);

        if(File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&File);

            out.setCodec("UTF-8");
            out << ui->textEdit->toPlainText();

            File.flush();
            File.close();

            QMessageBox::information(this, tr("File was saved"),
                                     tr("File was saved as") + " " + FileName);
        }
    }
}

void MainWindow::on_actionSave_converted_triggered()
{
    ui->textEdit_2->setReadOnly(false);
    ui->textEdit_2->setAcceptRichText(false);

    QString file = "";

    file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                        tr("Text Files (*.txt)"));

    if(!file.isEmpty())
    {
        QDir direct;
        QString dir = direct.filePath(file);
        QString FileName = dir;
        QFile File(FileName);

        if(File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&File);

            out.setCodec("UTF-8");
            out << ui->textEdit_2->toPlainText();

            File.flush();
            File.close();

            QMessageBox::information(this, tr("File was saved"),
                                     tr("File was saved as") + " " + FileName);
        }
    }
}

void MainWindow::on_actionIngush_with_original_triggered()
{
    QMessageBox::information(this, tr("Converting..."),
                             tr("Conversion will begin after you click \"OK\". It might take some time. Please  wait."));

    QString f1 = "BibleNames.txt";
    QFile File1(f1);
    File1.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File1);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setText(text);
    File1.close();

    lang = "Ingush";
    addorig = "True";

    converter_from_original(lang, addorig);

    QString f2 = "BibleNamesIngush.txt";
    QFile File2(f2);
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in2(&File2);
    in2.setCodec("UTF-8");
    QString text2 = in2.readAll();
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setText(text2);
    File2.close();
}

void MainWindow::on_actionIngush_without_original_triggered()
{
    QMessageBox::information(this, tr("Converting..."),
                             tr("Conversion will begin after you click \"OK\". It might take some time. Please  wait."));

    QString f1 = "BibleNames.txt";
    QFile File1(f1);
    File1.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File1);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setText(text);
    File1.close();

    lang = "Ingush";
    addorig = "False";

    converter_from_original(lang, addorig);
    sorter(lang, addorig);

    QString f2 = "BibleNamesIngushOnlyordered.txt";
    QFile File2(f2);
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in2(&File2);
    in2.setCodec("UTF-8");
    QString text2 = in2.readAll();
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setText(text2);
    File2.close();
}

void MainWindow::on_actionAvar_with_original_triggered()
{
    QMessageBox::information(this, tr("Converting..."),
                             tr("Conversion will begin after you click \"OK\". It might take some time. Please  wait."));

    QString f1 = "BibleNames.txt";
    QFile File1(f1);
    File1.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File1);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setText(text);
    File1.close();

    lang = "Avar";
    addorig = "True";

    converter_from_original(lang, addorig);

    QString f2 = "BibleNamesAvar.txt";
    QFile File2(f2);
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in2(&File2);
    in2.setCodec("UTF-8");
    QString text2 = in2.readAll();
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setText(text2);
    File2.close();
}

void MainWindow::on_actionAvar_without_original_triggered()
{
    QMessageBox::information(this, tr("Converting..."),
                             tr("Conversion will begin after you click \"OK\". It might take some time. Please  wait."));

    QString f1 = "BibleNames.txt";
    QFile File1(f1);
    File1.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File1);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setText(text);
    File1.close();

    lang = "Avar";
    addorig = "False";

    converter_from_original(lang, addorig);
    sorter(lang, addorig);

    QString f2 = "BibleNamesAvarOnlyordered.txt";
    QFile File2(f2);
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in2(&File2);
    in2.setCodec("UTF-8");
    QString text2 = in2.readAll();
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setText(text2);
    File2.close();
}

void MainWindow::on_actionChechen_with_original_triggered()
{
    QMessageBox::information(this, tr("Converting..."),
                             tr("Conversion will begin after you click \"OK\". It might take some time. Please  wait."));

    QString f1 = "BibleNames.txt";
    QFile File1(f1);
    File1.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File1);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setText(text);
    File1.close();

    lang = "Chechen";
    addorig = "True";

    converter_from_original(lang, addorig);

    QString f2 = "BibleNamesChechen.txt";
    QFile File2(f2);
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in2(&File2);
    in2.setCodec("UTF-8");
    QString text2 = in2.readAll();
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setText(text2);
    File2.close();
}

void MainWindow::on_actionChechen_without_original_triggered()
{
    QMessageBox::information(this, tr("Converting..."),
                             tr("Conversion will begin after you click \"OK\". It might take some time. Please  wait."));

    QString f1 = "BibleNames.txt";
    QFile File1(f1);
    File1.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File1);
    in.setCodec("UTF-8");
    QString text = in.readAll();
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setText(text);
    File1.close();

    lang = "Chechen";
    addorig = "False";

    converter_from_original(lang, addorig);
    sorter(lang, addorig);

    QString f2 = "BibleNamesChechenOnlyordered.txt";
    QFile File2(f2);
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in2(&File2);
    in2.setCodec("UTF-8");
    QString text2 = in2.readAll();
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setText(text2);
    File2.close();
}

void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text = tr("This is a program for converting Biblical names \
from original into some Caucasian languages.") + "\n\n";

    about_text += tr("Copyright (C) 2022 Aleksandr Migunov") + "\n\n";

    about_text += "This program is free software; you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by \
the Free Software Foundation; either version 3 of the License, or \
(at your option) any later version. \n\n";

    about_text += "This program is distributed in the hope that it will be useful, \
but WITHOUT ANY WARRANTY; without even the implied warranty of \
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \
GNU General Public License for more details. \n\n";

    about_text += "You should have received a copy of the GNU General Public License \
along with this program. If not, see <https://www.gnu.org/licenses/>.";

    QMessageBox::about(this, tr("About Program"), about_text);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}