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
 *   Copyright (C) 2007 by CEA LIST / LVIC *
 *   Gael.de-Chalendar@cea.fr   *
 ***************************************************************************/

#ifndef QSHOWPOS_H
#define QSHOWPOS_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QModelIndex>
#include <QTextCursor>

class QAction;
class QMenu;
class QShowPosWidget;

class QShowPos:public QMainWindow
{
  Q_OBJECT

public:
  QShowPos(const QStringList& files);
  ~QShowPos();

  void selectEventAt(quint32 position, const QPoint& eventPos);

protected:
  void closeEvent( QCloseEvent *event );

private Q_SLOTS:
  void open();

  void about();

  void documentWasModified();

  void slotGoto();

  void slotSearch();

  void slotSearchNext();
  
private:
  void createActions();

  void createMenus();

  void createToolBars();

  void createStatusBar();

  void readSettings();

  void writeSettings();

  void loadFile( const QString &fileName );

  void setCurrentFile( const QString &fileName );

  QString strippedName( const QString &fullFileName );

  QShowPosWidget* m_textEdit;

  QString m_curFile;
  QString m_currentDirectory;

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *helpMenu;

  QToolBar *fileToolBar;
  QToolBar *editToolBar;
  
  QAction *openAct;
  QAction *exitAct;
  QAction *aboutAct;
  QAction *aboutQtAct;
  QAction *m_gotoAct;
  QAction* m_searchAction;
  QAction* m_searchNextAction;
  
  QTextCursor m_lastSearchResult;
};

#endif
