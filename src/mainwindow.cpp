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
#include "scene\viewport.h"

MainWindow::MainWindow(QWidget *parent/* = Q_NULLPTR*/)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
	, m_viewport(new Viewport(this))

{
	m_ui->setupUi(this);

	// set up shortcuts
	m_ui->actionQuit->setShortcuts(QKeySequence::Quit);
	connect(m_ui->actionQuit, SIGNAL(triggered()), SLOT(close()));

	setCentralWidget(m_viewport);
}

MainWindow::~MainWindow()
{
	delete m_viewport;
	delete m_ui;
}