#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QtCore>
#include <QtGui>
#include "filedatabase.h"
#include "inttypes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


static fileDatabase mainDB;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<QModelIndex> modified;

    QSortFilterProxyModel* middleModel;

    QStandardItemModel* model;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_treeView_activated(const QModelIndex &index);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_2_editingFinished();

private:
    Ui::MainWindow *ui;
    void loadDatabase();
};
#endif // MAINWINDOW_H
