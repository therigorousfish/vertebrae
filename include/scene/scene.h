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

#ifndef VERTEBRAE_SCENE_H__
#define VERTEBRAE_SCENE_H__

#include <vector>

#include <QObject>
#include <QRectF>
#include "actor.h"

class Viewport;

class Scene : public QObject
{
	Q_OBJECT

public:
	friend class Viewport;

	Scene(QObject *parent = Q_NULLPTR);
	Scene(QRectF &sceneRect, QObject *parent = Q_NULLPTR);
	Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);
	virtual ~Scene();

	void setSceneRect(QRectF &sceneRect);
	void setSceneRect(qreal x, qreal y, qreal width, qreal height);
	void addActor(Actor::Ptr item);

signals:
	void changed(const QList<QRectF> &region);

private:
	void addViewport(Viewport *view);

	std::vector<Viewport *> m_viewports;
	Actor::Ptr m_root;
	QRectF m_sceneRect;
	bool m_hasSceneRect;
};

#endif // !VERTEBRAE_SCENE_H__
