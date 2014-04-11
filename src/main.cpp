/*
 *    Copyright 2002-2013 CEA LIST
 * 
 *    This file is part of LIMA.
 * 
 *    LIMA is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Affero General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    LIMA is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 * 
 *    You should have received a copy of the GNU Affero General Public License
 *    along with LIMA.  If not, see <http://www.gnu.org/licenses/>
 */
/***************************************************************************
 *   Copyright (C) 2007 by CEA LIST / LVIC   *
 *   Gael.de-Chalendar@cea.fr   *
 ***************************************************************************/

#include <QApplication>
#include "qshowpos.h"

int main( int argc, char *argv[] )
{
  Q_INIT_RESOURCE( qshowpos );
  QApplication app( argc, argv );
  QShowPos * mw = new QShowPos();
  mw->show();
  return app.exec();
}

