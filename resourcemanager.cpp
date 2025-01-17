#include "resourcemanager.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QDockWidget>
#include <QPushButton>

ResourceManager::ResourceManager(QDockWidget* Dock) {


    treeView=new QTreeView();
    fileModel=new QFileSystemModel();

    fileModel->setRootPath(QDir::currentPath());///init the model
    fileModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    ///设置根路径
    treeView->setRootIndex(fileModel->index(QDir::currentPath()));

    treeView->setModel(fileModel);

    // Hide size, type, date columns - show only filename
    treeView->setHeaderHidden(true);
    for (int i = 1; i < fileModel->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    Dock->setWidget(treeView);

    treeViewStyleSheet=R"(
            background-color: rgb(31, 31, 31);
            color: rgb(240, 240, 240);

    )";

    treeView->setStyleSheet(treeViewStyleSheet);

    connect(treeView,&QTreeView::clicked,this,&ResourceManager::on_FileClick);
    connect(treeView,&QTreeView::doubleClicked,this,&ResourceManager::on_FileDoubleClick);


}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::SetCurPath(QString path)
{
    fileModel->setRootPath(path);
    treeView->setRootIndex(fileModel->index(path));

    qDebug()<<"the fileModel has been set to :"<<path;

}

void ResourceManager::RefreshModel()
{

}

void ResourceManager::ModifyStyle()
{

}

void ResourceManager::on_FileClick(const QModelIndex &index)
{
    QString filename=fileModel->filePath(index);
    emit(fileClick(filename));
    qDebug()<<"emit Click,filename:"<<filename;
    qDebug()<<"filePath:"<<fileModel->filePath(index);

}

void ResourceManager::on_FileDoubleClick(const QModelIndex &index)
{
    QString filename=fileModel->filePath(index);
    emit(fileDoubleClick(filename));
    qDebug()<<"emit doubleClick,filename:"<<filename;
    qDebug()<<"filePath:"<<fileModel->filePath(index);

}

