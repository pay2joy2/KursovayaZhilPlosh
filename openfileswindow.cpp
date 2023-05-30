
#include "openfileswindow.h"
#include "./ui_openfileswindow.h"
#include "mainwindow.h"


OpenFilesWindow::OpenFilesWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OpenFilesWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("home.ico"));
}

OpenFilesWindow::~OpenFilesWindow()
{
    delete ui;
}

void OpenFilesWindow::on_OpenFile_clicked()
{
    QStringList filelist;
    QString filename;
    const QStringList filters({"Text files (*.txt)"});
    QFileDialog dialog(this);
    dialog.setNameFilters(filters);
    if(dialog.exec())
    {
        filelist = dialog.selectedFiles();
        filename = filelist[0];
        char *filenameChar;
        filenameChar = filename.toLocal8Bit().data();
        std::ifstream f(filenameChar);
        std::string line;
        Fond *Head, *Tail;
        Head = NULL;
        Tail = NULL;
        while (std::getline(f,line))
        {
            Fond *temp = new Fond;
            temp->next = NULL;
            char *LineChar = _strdup(line.c_str());
            temp->building = atoi(strtok(LineChar, " "));
            temp->flat = atoi(strtok(NULL, " "));
            temp->name = strtok(NULL, " ");
            temp->contract = atoi(strtok(NULL, " "));
            if (Head == NULL)
            {
                Head = temp;
                Tail = temp;
            }
            else
            {
                Tail->next = temp;
                Tail = temp;
            }
        }
        MainWindow *mainwindow = new MainWindow;
        connect (this, &OpenFilesWindow::signal, mainwindow, &MainWindow::slot);
        emit signal(Head,filename);
        f.close();
        mainwindow->show();
        this->close();
    }
}

void OpenFilesWindow::on_NewCode_clicked()
{
    QString filename;
    QFileDialog dialog(this);
    filename = dialog.getSaveFileName(this, "Create New File","", tr("Text files (*.txt)"));
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        Fond* Head;
        Head = NULL;
        MainWindow *mainwindow = new MainWindow;
        connect(this, &OpenFilesWindow::signal, mainwindow, &MainWindow::slot);
        emit signal(Head, filename);
        file.close();
        mainwindow->show();
        this->close();
    }
}

