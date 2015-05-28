//
// Created by Alexander on 27.05.2015.
//

#include "Graph.h"
void Graph::resize(int w, int h) {

}
void Graph::initGL(void) {
    //glClearColor(1.0 , 1.0 , 1.0 , 1.0); ///цвет фона окна
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
            0, plot.FrameSize.back()+300,
            0, plot.speed.back()+30, -1.0,1.0);
}

void Graph::render() {
    std::string t;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glBegin(GL_LINES);   ///начнём рисовать первую координатную ось - OY. Будем это делать при помощи линий


    glColor3f(0,0,1);
    glVertex2f(20, 0);
    glVertex2f(20, plot.speed.back()*3000);   ///вторая точка оси
    glEnd();
    //OX
    glColor3f(0,1,0);
    glBegin(GL_LINES);  ////теперь проделаем тоже для оси
    glVertex2f(0,plot.speed.front()+.5);
    glVertex2f(plot.FrameSize.back(),plot.speed.back()+.5);
    glEnd();
    //some names
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(20, 25);
    t = "Transfer Rate";
    for(int i = 0; i<t.size(); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t.at(i));
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(plot.FrameSize.back(), 2);
    t = "FrameSize";
    for(int i = 0; i<t.size(); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t.at(i));
    //params on axis
    for(auto i = 0.01; i < 1.0; i+=0.02){
        t = to_str(i);
        glRasterPos2f(20, i*30);
        for(int j = 0; j<t.size(); j++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, t.at(j));
    }
    for(auto i = 100; i <= plot.FrameSize.back(); i+=100){
        t = to_str(i);
        glRasterPos2f(i, 30*0.01);
        for(int j = 0; j<t.size(); j++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, t.at(j));
    }
    glPopMatrix();
    glFlush();

    GLdouble r,g,b;
    for(auto plots : pls) {
        generator(0,1,r); generator(0,1,g); generator(0,1,b);
        //glColor3f(1.0, 0.0, 0.0); ///выберем для неё красный цвет
        glColor3f(r,g,b);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < plot.speed.size(); i++) {
            glColor3f(r,g,b);
            glVertex2d(plots.FrameSize[i], plots.speed[i]*30);
        }
        std::stringstream ss;
        ss << "Code(" << plots.code.codeLength << ", " << plots.code.DataLength << ", " <<
        plots.code.errorsCorrection << ", " << plots.code.bitsWord << ")";
        (ss.str()).data();
        glEnd();

        glPushMatrix();
        glRasterPos2f(1250+1, *(std::max_element(plots.speed.begin(), plots.speed.end())) *30);
        for (int i = 0; i < ss.str().size(); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ss.str().at(i));
        glPopMatrix();
        glFlush();
    }

}

void Graph::text(char* str) {
    char *p;
    for (p = str; *p; p++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
    }
}
