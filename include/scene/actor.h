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

#ifndef VERTEBRAE_ACTOR_H__
#define VERTEBRAE_ACTOR_H__

#include <vector>
#include <memory>

#include <QString>
#include <QVariant>

#include <vector>
#include <utility>

class Scene;

class Actor
{
public:
	friend class Scene;
	typedef std::unique_ptr<Actor> Ptr;

    explicit Actor(Actor *parent = nullptr);
    virtual ~Actor();

	QVariant getProperty(const QString &name) const;
	void setProperty(const QString &name, const QVariant& value);

	void addChild(Actor::Ptr child);
	Actor::Ptr removeChild(Actor* child);

	std::vector<Actor*> children() const;

	void setScene(Scene *scene);

private:
	Actor *m_parent;
	Scene *m_scene;
	std::vector<std::pair<QString, QVariant>> m_properties;
	std::vector<Actor::Ptr> m_children;

};

#endif // LOGVERTEBRAE_ACTOR_H__O_H
