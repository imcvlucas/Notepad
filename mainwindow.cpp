#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
   currentFile.clear();
   ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
   // Open a dialog box
   QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
   QFile file(fileName);
   currentFile = fileName;
   // Throw error
   if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
       return;
   }
   setWindowTitle(fileName);
   QTextStream in(&file);
   QString text = in.readAll();
   ui->textEdit->setText(text);
   file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
   // Open a dialog box
   QString fileName = QFileDialog::getSaveFileName(this, "Save as");
   QFile file(fileName);
   // Throw error
   if (!file.open(QFile::WriteOnly | QFile::Text)) {
       QMessageBox::warning(this, "warning", "Cannot save file: " + file.errorString());
       return;
   }
   currentFile = fileName;
   setWindowTitle(fileName);
   QTextStream out(&file);
   QString text = ui->textEdit->toPlainText();
   out << text;
   file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
