//
// Created by Alexander on 27.05.2015.
//

#ifndef DIPLOM_GRAPH_H
#define DIPLOM_GRAPH_H
#include "GLWindow.hpp"
#include <GL\glu.h>
#include <GL\gl.h>
#include <iostream>
#include "api.hpp"
#include <list>

class Graph : public GLWindow {
public:

    Graph() {
        Graph::mode = GLUT_RGBA | GLUT_SINGLE;
        Graph::subwindows = 0;
    }
    virtual ~Graph() { }

    void setPls(const std::list<Plot> &pls) {
        Graph::pls = pls;
        Graph::plot = Graph::pls.front();
    }

private:
    std::list<Plot>pls;
    Plot plot;
    void text(char* str);
protected:
    void resize(int w, int h);
    void initGL(void);
    void createsubwindows(void){};
    void render(void);
    void keyboard(unsigned char key, int x, int y){};
    void mouse(unsigned int button, int state, int x, int y){};
    void motion(int x, int y){};
    void passmotion(int x, int y){};
    void idlefunc(void){};
};


#endif //DIPLOM_GRAPH_H
