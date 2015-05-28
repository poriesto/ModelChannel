#include "GLWindow.hpp"

void GLWindow::initMainwnd(void)
{
	char *ar[] = {"-w", "GLUT_RGB", "GLUT_DEPTH"};
	int args = 3;
	app = this;

	//glutInit(&argc,  ar);
	glutInit(&args, ar);
	glutInitDisplayMode(mode);
	glutInitWindowSize(rect.w, rect.h);
	glutInitWindowPosition(initPosx, initPosy);
	main = glutCreateWindow(name.c_str());
	glutDisplayFunc(Render);
	glutKeyboardFunc(Keyboard);
	glutVisibilityFunc(Visible);
	glutMouseFunc(Mice);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
}
//public methods
void GLWindow::setname(std::string name)
{
	this->name = name;
}

void GLWindow::setinitPosition(int x, int y)
{
	initPosx = x; initPosy = y;
}

void GLWindow::setwidthheight(int w, int h)
{
	rect.w = w; rect.h = h;
}

void GLWindow::setwidthheight(Rect rect)
{
	this->rect = rect;
}

Rect GLWindow::getRect(void)
{
	return rect;
}

//private static methods
void GLWindow::Render(void)
{
	app->render();
	glutSwapBuffers();
}

void GLWindow::Mice(int button, int state, int x, int y)
{
	app->mouse(button, state, x, y);
	glutPostWindowRedisplay(app->main);
}

void GLWindow::Idlefunc(void)
{
	app->idlefunc();
}

void GLWindow::Keyboard(unsigned char key, int x, int y)
{
	app->keyboard(key, x, y);
	glutPostWindowRedisplay(app->main);
};

void GLWindow::Motion(int x, int y)
{
	app->motion(x, y);
};

void GLWindow::PassiveMotion(int x, int y)
{
	app->passmotion(x, y);
};

void GLWindow::Resize(int w, int h)
{
	app->resize(w, h);
	glutPostWindowRedisplay(app->main);
};

void GLWindow::Visible(int vis)
{
	glutPostWindowRedisplay(app->main);
};
