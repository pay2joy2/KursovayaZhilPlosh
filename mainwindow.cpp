#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("home.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot(Fond *GetHead, QString filenameget)
{
    filename = filenameget;
    Head = GetHead;
    ui->tableWidget->setColumnCount(4);
    QTableWidgetItem *label1 = new QTableWidgetItem(tr("Дом"));
    QTableWidgetItem *label2 = new QTableWidgetItem(tr("Квартира"));
    QTableWidgetItem *label3 = new QTableWidgetItem(tr("Фамилия"));
    QTableWidgetItem *label4 = new QTableWidgetItem(tr("Договор"));
    ui->tableWidget->setHorizontalHeaderItem(0, label1);
    ui->tableWidget->setHorizontalHeaderItem(1, label2);
    ui->tableWidget->setHorizontalHeaderItem(2, label3);
    ui->tableWidget->setHorizontalHeaderItem(3, label4);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    int row = 0;
    if (Head != NULL)
    {
        Fond * temp;
        temp = Head;
        while (temp){
            ui->tableWidget->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(temp->building));
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row,0,item);
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(temp->flat));
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 1,item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString(temp->name));
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 2,item3);
            QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(temp->contract));
            item4->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 3,item4);
            row++;
            temp = temp->next;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,item);
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,item2);
    QTableWidgetItem *item3 = new QTableWidgetItem();
    item3->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,item3);
    QTableWidgetItem *item4 = new QTableWidgetItem();
    item4->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,item4);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->tableWidget->currentItem() != NULL){
        if(ui->tableWidget->currentItem()->isSelected())
        {
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Выберите строку которую надо удалить");
            msgBox.exec();
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText("Выберите строку которую надо удалить");
        msgBox.exec();
    }
}

void MainWindow::SaveToFileFunc(Fond *NewHead)
{

        if (NewHead != NULL)
        {
            std::ofstream f(filename.toLocal8Bit());
            Fond *temp;
            temp = NewHead;
            while(temp)
            {
                f << temp->building << " " << temp->flat << " " << temp->name << " " << temp->contract << "\n";
                temp = temp->next;
            }
            f.close();
            QApplication::closeAllWindows();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Вы уверены что хотите сохранить пустой файл?");
            QPushButton *YesBtn = msgBox.addButton("Да", QMessageBox::YesRole);
            msgBox.addButton("Нет", QMessageBox::NoRole);
            msgBox.exec();
            if (msgBox.clickedButton() == YesBtn)
            {
                std::ofstream f(filename.toLocal8Bit().data());
                f.close();
                QApplication::closeAllWindows();
            }
        }
}

bool MainWindow::CheckForEmptyCells()
{
    checkStateForChange = false;
    bool statecheck = true;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int a = 0; a < ui->tableWidget->columnCount(); a++)
        {
            if (ui->tableWidget->item(i,a)->text().size() == 0)
            {
                statecheck = false;
                ui->tableWidget->item(i,a)->setBackground(Qt::red);
            }
        }
    }
    checkStateForChange = true;
    if (statecheck == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Заполните все пустые ячейки перед сохранением");
        msgBox.exec();
    }
    return statecheck;
}

void MainWindow::on_SaveButton_clicked()
{
    Fond *NewHead, *NewTail;
    NewHead = NULL;
    NewTail = NULL;
    bool statecheck = CheckForEmptyCells();
    if (statecheck == true)
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            Fond *temp = new Fond;
            temp->next = NULL;
            temp->building = (ui->tableWidget->item(i,0)->text().toInt());
            temp->flat = (ui->tableWidget->item(i,1)->text().toInt());
            temp->name = (ui->tableWidget->item(i,2)->text().toStdString());
            temp->contract = (ui->tableWidget->item(i,3)->text().toInt());
            if (NewHead == NULL)
            {
                NewHead = temp;
                NewTail = temp;
            }
            else
            {
                NewTail->next = temp;
                NewTail = temp;
            }
        }
        SaveToFileFunc(NewHead);
    }
}

void MainWindow::on_SearchEntry_textChanged(const QString &arg1)
{
    ui->tableWidget->setCurrentItem(NULL);
    if (arg1.size() !=0)
    {
        QList <QTableWidgetItem*> listofitems = ui->tableWidget->findItems(arg1, Qt::MatchContains);
        for (int i =0; i< listofitems.length(); i++)
        {
            QTableWidgetItem *item = listofitems[i];
            item->setSelected(true);
        }
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if (ui->tableWidget->item(row,column)->background().color().red() && checkStateForChange == true)
    {
        ui->tableWidget->item(row,column)->setBackground(Qt::white);
    }
}

