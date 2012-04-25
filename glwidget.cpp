#include "glwidget.h"

#include "helper.h"

GLWidget::GLWidget(QWidget *parent) :
        QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba | QGL::AlphaChannel | QGL::DirectRendering), parent)
{
}

void GLWidget::initializeGL()
{
    // Set up the rendering context, define display lists etc.:
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_CULL_FACE);

    // fix outlines z-fighting with the quads
    glPolygonOffset(1, 1);
    glEnable(GL_POLYGON_OFFSET_FILL);
}

void GLWidget::resizeGL(int w, int h)
{
    w = w & ~1; h = h & ~1;
    // setup viewport, projection etc.:
    glViewport(0, 0, (GLint)w, (GLint)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2.0, w/2.0, h/2.0, -h/2.0, -1, 1);
    glScaled(16.0, 16.0, 1.0/16.0);
    double mTransposed[] = {
         2,  1, 1, 0,
         0, -2, 2, 0,
        -2,  1, 1, 0,
         0,  0, 0, 1
    };
    glMultMatrixd(mTransposed);
    //glMultTransposeMatrixd(m[0]);

}

void boxhelper(double x, double y, double z, double xs, double ys, double zs, QBrush const & brush, bool outline = true);

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    boxhelper(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, QBrush(QColor(192, 192, 192)));
}

void boxhelper(double x, double y, double z, double xs, double ys, double zs, QBrush const & brush, bool outline)
{
    QBrush brushTop = brush;

    QBrush brushEW = brush;
    brushEW.setColor( brush.color().darker(120));

    QBrush brushNS = brush;
    brushNS.setColor( brush.color().darker(150));

    glBegin(GL_QUADS);
    glhApplyBrush(brushTop);
    // top side
    glVertex3d(x     , y + ys, z     );
    glVertex3d(x     , y + ys, z + zs);
    glVertex3d(x + xs, y + ys, z + zs);
    glVertex3d(x + xs, y + ys, z     );

    // bottom side
    glVertex3d(x     , y     , z     );
    glVertex3d(x + xs, y     , z     );
    glVertex3d(x + xs, y     , z + zs);
    glVertex3d(x     , y     , z + zs);

    glhApplyBrush(brushEW);
    // east side
    glVertex3d(x     , y     , z     );
    glVertex3d(x     , y + ys, z     );
    glVertex3d(x + xs, y + ys, z     );
    glVertex3d(x + xs, y     , z     );

    // west side
    glVertex3d(x     , y     , z + zs);
    glVertex3d(x + xs, y     , z + zs);
    glVertex3d(x + xs, y + ys, z + zs);
    glVertex3d(x     , y + ys, z + zs);

    glhApplyBrush(brushNS);
    // north side
    glVertex3d(x     , y     , z     );
    glVertex3d(x     , y     , z + zs);
    glVertex3d(x     , y + ys, z + zs);
    glVertex3d(x     , y + ys, z     );

    // south side
    glVertex3d(x + xs, y     , z     );
    glVertex3d(x + xs, y + ys, z     );
    glVertex3d(x + xs, y + ys, z + zs);
    glVertex3d(x + xs, y     , z + zs);

    glEnd();

    if (!outline)
        return;

    QPen outlinePen;
    outlinePen.setWidthF(1);

    glhApplyPen(outlinePen);
    glBegin(GL_LINE_LOOP);
    // top side
    glVertex3d(x     , y + ys, z     );
    glVertex3d(x + xs, y + ys, z     );
    glVertex3d(x + xs, y + ys, z + zs);
    glVertex3d(x     , y + ys, z + zs);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // bottom side
    glVertex3d(x     , y     , z     );
    glVertex3d(x + xs, y     , z     );
    glVertex3d(x + xs, y     , z + zs);
    glVertex3d(x     , y     , z + zs);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // east side
    glVertex3d(x     , y     , z     );
    glVertex3d(x + xs, y     , z     );
    glVertex3d(x + xs, y + ys, z     );
    glVertex3d(x     , y + ys, z     );
    glEnd();

    glBegin(GL_LINE_LOOP);
    // west side
    glVertex3d(x     , y     , z + zs);
    glVertex3d(x + xs, y     , z + zs);
    glVertex3d(x + xs, y + ys, z + zs);
    glVertex3d(x     , y + ys, z + zs);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // north side
    glVertex3d(x     , y     , z     );
    glVertex3d(x     , y     , z + zs);
    glVertex3d(x     , y + ys, z + zs);
    glVertex3d(x     , y + ys, z     );
    glEnd();

    glBegin(GL_LINE_LOOP);
    // south side
    glVertex3d(x + xs, y     , z     );
    glVertex3d(x + xs, y     , z + zs);
    glVertex3d(x + xs, y + ys, z + zs);
    glVertex3d(x + xs, y + ys, z     );
    glEnd();
}
