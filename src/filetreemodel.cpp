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

#include "filetreemodel.h"
#include "fileitem.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
FileTreeModel::FileTreeModel(QObject *parent)
    : QStandardItemModel(parent)
{
    header << tr("Name") << tr("Size") << tr("Allocated")
           << tr("Files") << tr("Folders") << tr("% of Parent")
           << tr("Last Modified") << tr("Owner");
    setHorizontalHeaderLabels(header);
}

void FileTreeModel::updateNode(FileNode node)
{
    auto item = map[node.filepath];
    if(!item) return;
    FileItem* iter = item;
    iter->node = node;
    iter->setData(node.filename, Qt::DisplayRole);
    iter = iter->next;
    quint64 oldsize = iter->data(Qt::UserRole).toULongLong();
    quint64 newsize = node.size;
    if (newsize == oldsize) return;
    iter->setData(node.getSize(), Qt::DisplayRole);
    iter->setData(node.size, Qt::UserRole);
    iter = iter->next;

    iter = iter->next;
    iter->setData(node.files, Qt::DisplayRole);

    iter = iter->next;
    iter->setData(node.folders, Qt::DisplayRole);

    iter = iter->next;

    iter = iter->next;
    iter->setData(node.lastModified, Qt::DisplayRole);

    iter = iter->next;
    iter->setData(node.owner, Qt::DisplayRole);


    if (item->parent()) {
        item = static_cast<FileItem *>(item->parent());
        auto newNode = item->node;
        newNode.size = newNode.size - oldsize + newsize;
        updateNode(newNode);
    }
}

void FileTreeModel::addNode(FileNode node) {
    auto row = buildRow(node);
    auto item = parent(node.filepath);
    if (item) {
        item->appendRow(row);
    } else {
        appendRow(row);

    }
    map[node.filepath] = static_cast<FileItem *>(row[0]);
}

QList<QStandardItem *> FileTreeModel::buildRow(FileNode& node) {
    QList<QStandardItem*> row;
    auto nameItem = new FileItem(node.filename);
    nameItem->node = node;
    auto sizeItem = new FileItem(node.getSize());
    sizeItem->setData(node.size, Qt::UserRole);
    row << nameItem                         // Name
        << sizeItem                         // Size
        << new FileItem()                   // Allocated
        << new FileItem(node.files)         // Files
        << new FileItem(node.folders)       // Folders
        << new FileItem()                   // % of Parent
        << new FileItem(node.lastModified)  // Last Modified
        << new FileItem(node.owner)         // Owner
            ;
    for(int i = 0; i < row.size() - 1; i++) {
        (static_cast<FileItem*>(row[i]))->next = static_cast<FileItem*>(row[i+1]);
    }
    return row;
}

FileItem *FileTreeModel::parent(QString path) {
    QFileInfo fileInfo(path);
    auto parentPath = fileInfo.absoluteDir().absolutePath();
    auto item = map[parentPath];
    return item;
}
