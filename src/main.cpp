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
 *   Copyright (C) 2007 by CEA LIST / LVIC   *
 *   Gael.de-Chalendar@cea.fr   *
 ***************************************************************************/

#include <QApplication>
#include <QDebug>
#include "qshowpos.h"

int main( int argc, char *argv[] )
{
  Q_INIT_RESOURCE( qshowpos );
  QApplication app( argc, argv );
  QStringList args;
  if (argc >= 1)
  for (unsigned int i = 1; i < argc; i++)
  {
//     qDebug() << "Arg" << i << argv[i];
    args << QString::fromUtf8(argv[i]) ;
  }
  QShowPos mw(args);
  mw.show();
  return app.exec();
}

