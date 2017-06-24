/* 
 * This file is part of Vertebrae.
 * 
 * Vertebrae is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU Lesser General Public License as   
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)

{
	ui->setupUi(this);

	// set up shortcuts
	ui->actionQuit->setShortcuts(QKeySequence::Quit);
	connect(ui->actionQuit, SIGNAL(triggered()), SLOT(close()));
}

MainWindow::~MainWindow()
{
	delete ui;
}