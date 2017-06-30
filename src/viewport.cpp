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

#include "viewport.h"

#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>

Viewport::Viewport(QWidget *parent/* = Q_NULLPTR*/)
	: QOpenGLWidget(parent)
	, m_xRot(0)
	, m_yRot(0)
	, m_zRot(0)
	, m_program(nullptr)
{
	/*QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setMajorVersion(4);
	format.setMinorVersion(5);
	format.setSamples(4);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);*/

	m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
}


Viewport::~Viewport()
{
	cleanup();
}

void Viewport::cleanup()
{
	makeCurrent();
	m_logoVbo.destroy();
	delete m_program;
	m_program = 0;
	doneCurrent();
}


static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";

void Viewport::initializeGL()
{
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Viewport::cleanup);

	initializeOpenGLFunctions();
	glClearColor(0.5, 0.5, 0.5, 1);

	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
	m_program->bindAttributeLocation("vertex", 0);
	m_program->bindAttributeLocation("normal", 1);
	m_program->link();

	m_program->bind();
	m_projMatrixLoc = m_program->uniformLocation("projMatrix");
	m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
	m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
	m_lightPosLoc = m_program->uniformLocation("lightPos");

	m_vao.create();
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

	// Setup our vertex buffer object.
	m_logoVbo.create();
	m_logoVbo.bind();
	m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

	// Store the vertex attribute bindings for the program.
	setupVertexAttribs();

	// Our camera never changes in this example.
	m_camera.setToIdentity();
	m_camera.translate(0, 0, -1);

	// Light position is fixed.
	m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

	m_program->release();
}

void Viewport::resizeGL(int w, int h)
{
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void Viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_world.setToIdentity();
	m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
	m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
	m_program->bind();
	m_program->setUniformValue(m_projMatrixLoc, m_proj);
	m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
	QMatrix3x3 normalMatrix = m_world.normalMatrix();
	m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

	glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

	m_program->release();
}

void Viewport::setupVertexAttribs()
{
	m_logoVbo.bind();
	//QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
	m_logoVbo.release();
}
