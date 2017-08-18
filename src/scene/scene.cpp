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

#include "scene\scene.h"
#include "scene\viewport.h"

Scene::Scene(QObject *parent/* = Q_NULLPTR*/)
	: QObject(parent)
	, m_root(std::make_unique<Actor>())
	, m_sceneRect()
	, m_hasSceneRect(false)
	, m_viewports()
{
	m_root->setScene(this);
}

Scene::Scene(QRectF &sceneRect, QObject *parent/* = Q_NULLPTR*/)
	: QObject(parent)
	, m_root(std::make_unique<Actor>())
	, m_sceneRect(sceneRect)
	, m_hasSceneRect(true)
	, m_viewports()
{
	m_root->setScene(this);
}

Scene::Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent/* = Q_NULLPTR*/)
	: QObject(parent)
	, m_root(std::make_unique<Actor>())
	, m_sceneRect(x, y, width, height)
	, m_hasSceneRect(true)
	, m_viewports()
{
	m_root->setScene(this);
}

Scene::~Scene()
{
}


void Scene::setSceneRect(QRectF &sceneRect)
{
	m_sceneRect = sceneRect;
}

void Scene::setSceneRect(qreal x, qreal y, qreal width, qreal height)
{
	m_sceneRect = QRectF(x, y, width, height);
}

void Scene::addActor(Actor::Ptr item)
{
	m_root->addChild(std::move(item));
}

void Scene::addViewport(Viewport *view)
{
	m_viewports.push_back(view);
	view->m_scene = this;
}