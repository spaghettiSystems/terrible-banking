#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"
#include "filedatabase.h"
#include "record.h"

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

QList<QStandardItem *> dbToQT(fileDatabase db){
    QList<QStandardItem *> dataToBeReturned;

    for(record entry: db.dbBuffer){
        QStandardItem* temp = new QStandardItem(QString::number(entry.id));
        temp->setEditable(0);

        QList<QStandardItem *> data;

        QStandardItem* mergeTest;

        mergeTest = new QStandardItem("First Name");
        mergeTest->setEditable(0);
        mergeTest->appendRow(new QStandardItem(QString::fromStdString(entry.firstName)));

        data.append(mergeTest);

        mergeTest = new QStandardItem("Last Name");
        mergeTest->setEditable(0);
        mergeTest->appendRow(new QStandardItem(QString::fromStdString(entry.lastName)));
        data.append(mergeTest);

        mergeTest = new QStandardItem("Balance");
        mergeTest->setEditable(0);
        mergeTest->appendRow(new QStandardItem(QString::number(entry.balance)));
        data.append(mergeTest);

        temp->appendColumn(data);

        dataToBeReturned.append(temp);
    }
    return dataToBeReturned;
}



void MainWindow::on_pushButton_clicked()
{
    QString file = ui->lineEdit->text();
    if(file.isEmpty()){
        return;
    }
    mainDB.openFile(file.toStdString());

    model = new QStandardItemModel();


    model->insertColumn(0, dbToQT(mainDB));
    model->setHeaderData(0, Qt::Horizontal, "Data");

    middleModel = new QSortFilterProxyModel();
    middleModel->setSourceModel(model);

    middleModel->setFilterKeyColumn(0);
    middleModel->setRecursiveFilteringEnabled(1);


    ui->treeView->setModel(middleModel);
    ui->treeView->expandAll();

}

void MainWindow::on_pushButton_2_clicked()
{
    if(!mainDB.initialized){
        return;
    }

    for(QModelIndex index: modified){
        if(index.parent().parent().isValid() &&
                middleModel->checkIndex(index.parent().parent()) &&
                middleModel->checkIndex(index)){
            QVariant modifiedData = middleModel->data(index);
            QVariant modifiedDataCategory = middleModel->data(index.parent());
            QVariant modifiedDataID = middleModel->data(index.parent().parent());
            unsigned __int64 id = modifiedDataID.toULongLong();
            if(modifiedDataCategory.toString().compare("First Name") == 0){
                mainDB.editRecordByID(id, modifiedData.toString().toStdString());
            }
            else if(modifiedDataCategory.toString().compare("Last Name") == 0){
                mainDB.editRecordByID(id, "", modifiedData.toString().toStdString());
            }
            else if(modifiedDataCategory.toString().compare("Balance") == 0){
                mainDB.editRecordByID(id, "", "", modifiedData.toInt(), true);
            }
            else{
                break;
            }
        }
    }
    modified.clear();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{


}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    if(!mainDB.initialized){
        return;
    }
    modified.push_back(index);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(!mainDB.initialized){
        return;
    }

    MainWindow::on_pushButton_2_clicked();

    QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid()){
        return;
    }
    QModelIndex finalIndex = (index.parent().isValid())? (index.parent().parent().isValid())? index.parent().parent():index.parent():index;
    unsigned __int64 id = model->data(finalIndex).toULongLong();
    mainDB.deleteRecordByID(id);
    model->removeRow(finalIndex.row());
}

void MainWindow::on_pushButton_5_clicked()
{
    if(!mainDB.initialized){
        return;
    }

    MainWindow::on_pushButton_2_clicked();

    mainDB.addRecord();

    QList<QStandardItem *> dataToBeReturned;

    model = new QStandardItemModel();

    model->insertColumn(0, dbToQT(mainDB));
    model->setHeaderData(0, Qt::Horizontal, "Data");

    middleModel = new QSortFilterProxyModel();
    middleModel->setSourceModel(model);

    middleModel->setFilterKeyColumn(0);
    middleModel->setRecursiveFilteringEnabled(1);

    ui->treeView->setModel(middleModel);
    ui->treeView->expandAll();

}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if(!mainDB.initialized){
        return;
    }
    if(!modified.empty()){
        MainWindow::on_pushButton_2_clicked();
    }
    middleModel->layoutAboutToBeChanged();

    middleModel->setFilterFixedString(arg1);

    middleModel->layoutChanged();

}

void MainWindow::on_lineEdit_2_editingFinished()
{
    if(!mainDB.initialized){
        return;
    }
    middleModel->layoutAboutToBeChanged();
    middleModel->setFilterFixedString("");
    middleModel->layoutChanged();
    ui->treeView->expandAll();
}
