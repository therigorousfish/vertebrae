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

#include "scene\actor.h"

#include <QDebug>
#include <algorithm>

Actor::Actor(Actor *parent/* = nullptr*/)
	: m_parent(parent)
	, m_scene(nullptr)
	, m_children()
{
	qDebug() << "Actor(" << (size_t) parent << ")";
}

Actor::~Actor()
{
	qDebug() << "~Actor";
}

QVariant Actor::getProperty(const QString &name) const
{
	auto found = std::find_if(m_properties.cbegin(), m_properties.cend(), [&name](const auto& pair){
		return pair.first == name;
	});
	if (found != m_properties.cend())
		return found->second;
	return QVariant();
}

void Actor::setProperty(const QString &name, const QVariant& value)
{
	auto found = std::find_if(m_properties.begin(), m_properties.end(), [&name](auto& pair) {
		return pair.first == name;
	});
	if (found == m_properties.end())
		m_properties.emplace_back(name, value);
	else
		found->second = value;
}

void Actor::addChild(Actor::Ptr child)
{
	m_children.push_back(std::move(child));
	if (m_scene) {
		child->setScene(m_scene);
	}
}

Actor::Ptr Actor::removeChild(Actor* child)
{
	auto found = std::find_if(m_children.begin(), m_children.end(), [&](const Actor::Ptr& c) {
		return c.get() == child;
	});

	Actor::Ptr res = nullptr;
	if (found != m_children.end()) {
		res = std::move(*found);
		if (res->m_scene) {
			// remove the item and his decendents from the scene
			res->setScene(nullptr);
		}
		m_children.erase(found);
	}
	return std::move(res);
}

std::vector<Actor*> Actor::children() const
{
	std::vector<Actor*> ret(m_children.size());

	std::transform(m_children.begin(), m_children.end(), ret.begin(), std::mem_fn(&Actor::Ptr::get));

	return ret;
}

void Actor::setScene(Scene *scene)
{
	// set the new scene for this item
	m_scene = scene;
	// and all of his decended
	for (Actor::Ptr &child : m_children) {
		child->setScene(scene);
	}
}