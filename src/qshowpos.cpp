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
 *   Copyright (C) 2014 by CEA LIST / LVIC   *
 *   Gael.de-Chalendar@cea.fr   *
 ***************************************************************************/

#include <QtGui>
#include "qshowpos.h"
#include "qshowposWidget.h"

#include <QTextStream>
#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <iostream>

#define VERSION "0.0.1"

QShowPos::QShowPos(const QStringList& files) :  m_currentDirectory()
{
  QFont font = QApplication::font();
  font.setPointSize(12);
  QApplication::setFont(font);

  m_textEdit = new QShowPosWidget(this);
  setCentralWidget( m_textEdit );

  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  readSettings();

  connect( m_textEdit->document(), SIGNAL( contentsChanged() ),
           this, SLOT( documentWasModified() ) );

  if (!files.isEmpty())
  {
    loadFile(files.first());
  }
}

void QShowPos::closeEvent( QCloseEvent *event )
{
  qDebug() << "QShowPos::closeEvent";
  event->accept();
}

void QShowPos::open()
{
  qDebug() << "QShowPos::open";
  QString fileName = QFileDialog::getOpenFileName( this, 
      tr("Select a File"), m_currentDirectory.isEmpty()?QString():m_currentDirectory  );

  if ( !fileName.isEmpty() )
  {
    m_currentDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
    loadFile( fileName );
  }
}

void QShowPos::about()
{
  qDebug() << "QShowPos::about";
  QMessageBox::about( this, tr( "Q Show Position" ),
                      tr( "The <b>Q Show Position</b> tool shows the postion of the cursor in a file in UTF16 codepoints.<br>Version %1<br>"
                          "Copyright 2014 CEA LIST/LVIC, released under AGPL" ).arg(VERSION) );
}

void QShowPos::documentWasModified()
{
  qDebug() << "QShowPos::documentWasModified";
  setWindowModified( true );
}

void QShowPos::createActions()
{
  qDebug() << "QShowPos::createActions";
  openAct = new QAction( QIcon( ":/fileopen.xpm" ), tr( "&Open..." ), this );
  openAct->setShortcut( tr( "Ctrl+O" ) );
  openAct->setStatusTip( tr( "Open an existing file" ) );
  connect( openAct, SIGNAL( triggered() ), this, SLOT( open() ) );

  exitAct = new QAction( tr( "E&xit" ), this );
  exitAct->setShortcut( tr( "Ctrl+Q" ) );
  exitAct->setStatusTip( tr( "Exit the application" ) );
  connect( exitAct, SIGNAL( triggered() ), this, SLOT( close() ) );

  aboutAct = new QAction( tr( "&About" ), this );
  aboutAct->setStatusTip( tr( "Show the application's About box" ) );
  connect( aboutAct, SIGNAL( triggered() ), this, SLOT( about() ) );

  aboutQtAct = new QAction( tr( "About &Qt" ), this );
  aboutQtAct->setStatusTip( tr( "Show the Qt library's About box" ) );
  connect( aboutQtAct, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );

  m_gotoAct = new QAction( tr( "Go to..." ), this );
  m_gotoAct->setStatusTip( tr( "Opens a dialog to ask where to move inside the text" ) );
  connect( m_gotoAct, SIGNAL( triggered() ), this, SLOT( slotGoto() ) );


  m_searchAction = new QAction( tr( "Search" ), this );
  m_searchAction->setShortcut( tr( "Ctrl+F" ) );
  m_searchAction->setStatusTip( tr( "Search a string of text" ) );
  connect( m_searchAction, SIGNAL( triggered() ), this, SLOT( slotSearch() ) );

  m_searchNextAction = new QAction( tr( "Search Next" ), this );
  m_searchNextAction->setShortcut( tr( "F3" ) );
  m_searchNextAction->setStatusTip( tr( "Search the next occurrence of the last searched text" ) );
  connect( m_searchNextAction, SIGNAL( triggered() ), this, SLOT( slotSearchNext() ) );
  
}

void QShowPos::createMenus()
{
  qDebug() << "QShowPos::createMenus";
  fileMenu = menuBar()->addMenu( tr( "&File" ) );
  fileMenu->addAction( openAct );
  fileMenu->addSeparator();
  fileMenu->addAction( exitAct );

  editMenu = menuBar()->addMenu( tr( "&Edit" ) );
  editMenu->addSeparator();
  editMenu->addAction( m_searchAction );
  editMenu->addAction( m_searchNextAction );
  
  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu( tr( "&Help" ) );
  helpMenu->addAction( aboutAct );
  helpMenu->addAction( aboutQtAct );
}

void QShowPos::createToolBars()
{
  qDebug() << "QShowPos::createToolBars";
  fileToolBar = addToolBar( tr( "File" ) );
  fileToolBar->addAction( openAct );

  editToolBar = addToolBar( tr( "Edit" ) );
  editToolBar->addAction( m_gotoAct );
}

void QShowPos::createStatusBar()
{
  qDebug() << "QShowPos::createStatusBar";
  statusBar()->showMessage( tr( "Ready" ) );
}

void QShowPos::readSettings()
{
  qDebug() << "QShowPos::readSettings";
  QSettings settings( "CEA LIST", "qshowpos" );
}

void QShowPos::writeSettings()
{
  qDebug() << "QShowPos::writeSettings";
  QSettings settings( "CEA LIST", "qshowpos" );
}

void QShowPos::loadFile( const QString &fileName )
{
  qDebug() << "QShowPos::loadFile" << fileName;
  QFile file( fileName );

  if ( !file.open( QFile::ReadOnly | QFile::Text ) )
  {
    QMessageBox::warning( this, tr( "Application" ),
                          tr( "Cannot read file %1:\n%2." )
                          .arg( fileName )
                          .arg( file.errorString() ) );
    return;
  }

  m_textEdit->clear();
  m_textEdit->document()->setModified( false );
  setWindowModified( false );

  QTextStream in( &file );
  in.setCodec(QTextCodec::codecForName("UTF-8"));
  QApplication::setOverrideCursor( Qt::WaitCursor );


  QTextCursor cursor = m_textEdit->textCursor();
  QTextCharFormat modifier = cursor.charFormat();
  modifier.setBackground(QBrush(QColor(Qt::white)));
  cursor.mergeCharFormat(modifier);
  m_textEdit->setTextCursor(cursor);
  m_textEdit->setTextColor( Qt::black );
  m_textEdit->setPlainText(in.readAll());
  QApplication::restoreOverrideCursor();

  setCurrentFile( fileName );
  statusBar()->showMessage( tr( "File loaded" ), 2000 );
}

void QShowPos::setCurrentFile( const QString &fileName )
{
  qDebug() << "QShowPos::setCurrentFile" << fileName;
  m_curFile = fileName;
  m_textEdit->document()->setModified( false );
  setWindowModified( false );

  QString shownName;

  if ( m_curFile.isEmpty() )
    shownName = "untitled.txt";
  else
    shownName = strippedName( m_curFile );

  setWindowTitle( tr( "%1[*] - %2" ).arg( shownName ).arg( tr( "Application" ) ) );
}

QString QShowPos::strippedName( const QString &fullFileName )
{
  qDebug() << "QShowPos::strippedName";
  return QFileInfo( fullFileName ).fileName();
}

QShowPos::~QShowPos()

{
  qDebug() << "QShowPos::~QShowPos";
}

void QShowPos::slotSearch()
{
  qDebug() << "QShowPos::slotSearch";
  if (!m_lastSearchResult.isNull())
  {
    m_textEdit->undo();
  }
  
  QString searchText = QInputDialog::getText(this, tr("Search Text"), tr("Enter the text to search&nbsp;:"));
  
  if (searchText.isEmpty())
  {
    return;
  }

  QTextDocument* doc = m_textEdit->document();
  m_lastSearchResult = doc->find(searchText, 0);

  if (!m_lastSearchResult.isNull())
  {
    qDebug() << searchText << "found at" << m_lastSearchResult.position();
    QTextCharFormat modifier = m_lastSearchResult.charFormat();
    modifier.setUnderlineColor(Qt::black);
    modifier.setUnderlineStyle (QTextCharFormat::WaveUnderline);
    modifier.setFontUnderline(true);
    modifier.setFontOverline(true);
    modifier.setBackground(QBrush(Qt::black));
    modifier.setForeground(QBrush(Qt::white));
    
    m_lastSearchResult.beginEditBlock();
    m_lastSearchResult.mergeCharFormat(modifier);
    m_lastSearchResult.endEditBlock();
    m_textEdit->setTextCursor(m_lastSearchResult);
  }
  else
  {
    qDebug() << searchText << "NOT found";
  }
}

void QShowPos::slotSearchNext()
{
  qDebug() << "QShowPos::slotSearchNext";
  if (m_lastSearchResult.isNull())
  {
    return;
  }
  m_textEdit->undo();

  QTextDocument* doc = m_textEdit->document();
  m_lastSearchResult = doc->find(m_lastSearchResult.selectedText (), m_lastSearchResult.position()+1);

  if (!m_lastSearchResult.isNull())
  {
    qDebug() << m_lastSearchResult.selectedText() << "found again at" << m_lastSearchResult.position();
    QTextCharFormat modifier = m_lastSearchResult.charFormat();
    modifier.setUnderlineColor(Qt::black);
    modifier.setUnderlineStyle (QTextCharFormat::WaveUnderline);
    modifier.setFontUnderline(true);
    modifier.setFontOverline(true);
    modifier.setBackground(QBrush(Qt::black));
    modifier.setForeground(QBrush(Qt::white));
    
    m_lastSearchResult.beginEditBlock();
    m_lastSearchResult.mergeCharFormat(modifier);
    m_lastSearchResult.endEditBlock();
    m_textEdit->setTextCursor(m_lastSearchResult);
  }
  else
  {
    qDebug() << m_lastSearchResult.selectedText() << "NOT found again";
  }
}

void QShowPos::slotGoto()
{
  qDebug() << "QShowPos::slotGoto";
  bool ok;
  int offset = QInputDialog::getInteger(this, tr("Jump to input"),
                                        tr("Go to:"), 0, 0, m_textEdit->document()->toPlainText().size(),
                                          1,&ok);
  if (ok)
  {
    QTextCursor cursor = m_textEdit->textCursor ();
    cursor.setPosition(offset);
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
    m_textEdit->setTextCursor(cursor);
  }
}

void QShowPos::selectEventAt(quint32 position, const QPoint& eventPos)
{
  qDebug() << "QShowPos::selectEventAt: "<<position<<", " << eventPos;
  statusBar()->showMessage( tr( "Position: %1").arg(position) );
}

