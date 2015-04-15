/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Copyright (C) 2013 Ivan Komissarov.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef KEYSEQUENCEEDIT_H
#define KEYSEQUENCEEDIT_H

#include <qglobal.h>

#if QT_VERSION >= 0x050000

#include <QObject>
#include <QKeySequenceEdit>

/*!
 * \brief Qt5's QKeySequenceEdit
 */
class KeySequenceEdit : public QKeySequenceEdit
{
    Q_OBJECT
public:
    explicit KeySequenceEdit(QWidget* parent=NULL);
};

#else

#include <QWidget>


class KeySequenceEditPrivate;

class KeySequenceEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QKeySequence keySequence READ keySequence WRITE setKeySequence NOTIFY keySequenceChanged USER true)

public:
    explicit KeySequenceEdit(QWidget *parent = 0);
    explicit KeySequenceEdit(const QKeySequence &keySequence, QWidget *parent = 0);
    ~KeySequenceEdit();

    QKeySequence keySequence() const;

public Q_SLOTS:
    void setKeySequence(const QKeySequence &keySequence);
    void clear();

Q_SIGNALS:
    void editingFinished();
    void keySequenceChanged(const QKeySequence &keySequence);

protected:
    KeySequenceEdit(KeySequenceEditPrivate &d, QWidget *parent, Qt::WindowFlags f);

    bool event(QEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    Q_DISABLE_COPY(KeySequenceEdit)
    Q_DECLARE_PRIVATE(KeySequenceEdit)
};

#endif // QT_VERSION >= 0x050000

#endif // KEYSEQUENCEEDIT_H


