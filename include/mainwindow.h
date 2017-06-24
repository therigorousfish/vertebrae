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

#ifndef VERTEBRAE_MAINWINDOW_H__
#define VERTEBRAE_MAINWINDOW_H__

#include <QtWidgets/QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~MainWindow();

private:
	Ui::MainWindow *ui;
};

#endif // VERTEBRAE_MAINWINDOW_H__