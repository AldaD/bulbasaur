/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2018 ~ 2018 PikachuHy
 *
 *
 * Author:     PikachuHy <pikachuhy@163.com>
 * Maintainer: PikachuHy <pikachuhy@163.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QThreadPool>
#include <QtConcurrent>
#include <QFileSystemModel>
DWIDGET_USE_NAMESPACE
FileNode traversal(QString parentPath, FileTreeModel* model);

FileNode handleFile(QString filename, FileTreeModel* model) {
    FileNode fileNode(filename);
    QFileInfo fileInfo(filename);
    if (fileInfo.isDir()) {
        return traversal(filename, model);
    } else {
        fileNode.size = fileInfo.size();
        fileNode.type = FileNode::FILE;
//        qDebug() << filename << formatFileSize(fileInfo.size());
        model->addNode(fileNode);
        return fileNode;
    }
}
FileNode traversal(QString parentPath, FileTreeModel* model)
{
    QDir dir(parentPath);
    auto files = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::DirsFirst);
    FileNode fileNode(parentPath);
    fileNode.type = FileNode::DIR;
    model->addNode(fileNode);
    for(auto file: files) {
        QString filename = QString("%1/%2").arg(parentPath).arg(file);
        if(QFileInfo(filename).isSymLink()) continue;
        auto node = handleFile(filename, model);
        fileNode.size += node.size;
        model->updateNode(fileNode);
    }
//    qDebug () << parentPath << formatFileSize(total);
    return fileNode;
}

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    setMinimumSize(QSize(800, 600));
    QString homePath = QDir::homePath();
    model = new FileTreeModel(this);
    view = new QTreeView(this);
    view->setModel(model);

    setCentralWidget(view);
    QtConcurrent::run(traversal, homePath, model);
}

MainWindow::~MainWindow()
{

}
