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

#ifndef FILEITEM_H
#define FILEITEM_H

#include <QObject>
#include <QStandardItem>
#include "filetreemodel.h"

class FileItem : public QStandardItem {
public:
    FileItem();

    FileItem(QString name);

    FileItem(int num);
    FileItem(const QIcon &icon, const QString &text);

    FileItem* next = nullptr;

    FileNode node;
private:
    void init();
};

#endif // FILEITEM_H
