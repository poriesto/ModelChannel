#include <GL/glut.h>
#include <string>
#include <stdlib.h>
struct Rect
{
	int w, h;
};
class GLWindow;
static GLWindow *app;

class GLWindow
{
	protected:
		Rect rect;
		int subwindows, initPosx, initPosy, main, argc;
		unsigned int mode;
		std::string name;
		void initMainwnd(void);
		
		//this methods must be implimented
		virtual void resize(int w, int h) = 0;
		virtual void initGL(void) = 0;
		virtual void createsubwindows(void) = 0;
		virtual void render(void){};
		virtual void keyboard(unsigned char key, int x, int y){};
		virtual void mouse(int button, int state, int x, int y){};
		virtual void motion(int x, int y) = 0;
		virtual void passmotion(int x, int y) = 0;
		virtual void idlefunc(void) = 0;
		
		void close()
		{
			glutDestroyWindow(main);
		}

		//dont touch this methods
	private:
		static void Render(void);
		static void Mice(int button, int state, int x, int y);
		static void Idlefunc(void);
		static void Keyboard(unsigned char key, int x, int y);
		static void Motion(int x, int y);
		static void PassiveMotion(int x, int y);
		static void Resize(int w, int h);
		static void Visible(int vis);
	public:
		//seters
		void setname(std::string name);
		void setinitPosition(int x, int y);
		void setwidthheight(int w, int h);
		void setwidthheight(Rect rect);
		
		//geters
		std::string getName(void){return name;}
		Rect getRect(void);
		
		//show the window
		void show(void){
			initMainwnd();
			initGL();
			glutMainLoop();
		};
};
