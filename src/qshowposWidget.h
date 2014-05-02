/*
 *    Copyright 2014 CEA LIST
 * 
 *    This file is part of QShowPos.
 * 
 *    QShowPos is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Affero General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    QShowPos is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 * 
 *    You should have received a copy of the GNU Affero General Public License
 *    along with QShowPos.  If not, see <http://www.gnu.org/licenses/>
 */
/***************************************************************************
 *   Copyright (C) 2014 by CEA LIST / LVIC *
 *   Gael.de-Chalendar@cea.fr   *
 ***************************************************************************/

#ifndef QSHOWPOSWIDGET_H
#define QSHOWPOSWIDGET_H

#include <QTextEdit>

class QShowPos;

class QShowPosWidget : public QTextEdit
{
Q_OBJECT

public:
  QShowPosWidget(QShowPos* parent);

  virtual ~QShowPosWidget() {}

protected:
  void mousePressEvent ( QMouseEvent * event );
  QShowPos* m_parent;
public slots:
    void slotCursorPositionChanged();
};

#endif // QSHOWPOSWIDGET_H
