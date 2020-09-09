#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<vector<float>> vertices;      // contains vertices by their index number
 
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
 
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);     

    glLoadIdentity();                 
    glTranslatef(0.1f, -0.2f, -0.8f); 

    glBegin(GL_TRIANGLES);
        ifstream infile("input.obj");
        string line;
        while(getline(infile, line))
        {
            istringstream iss(line);
            char ch;
            float tr1,tr2,tr3;
            if(!(iss>>ch>>tr1>>tr2>>tr3))
                break;
            if(ch=='f')
            {
                vector<float> vert1=vertices[tr1];
                vector<float> vert2=vertices[tr2];
                vector<float> vert3=vertices[tr3];
                glColor3f(1,0,0);     
                glVertex3f(vert1[0],vert1[1],vert1[2]);
                glColor3f(0,1,0);     
                glVertex3f(vert2[0],vert2[1],vert2[2]);
                glColor3f(0,0,1);     
                glVertex3f(vert3[0],vert3[1],vert3[2]);
            }
        }
    glEnd();
    glutSwapBuffers();
}
 

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void readObjFile()
{
    vertices.push_back({});   // vertices are not zero indexed
    ifstream infile("input.obj");
    string line;
    while(getline(infile, line))
    {
        istringstream iss(line);
        char ch;
        float a,b,c;
        if(!(iss>>ch>>a>>b>>c))
            break;
        if(ch=='v')
            vertices.push_back({a,b,c});
        else
            break;
    }
}
 
int main(int argc, char** argv) {
    readObjFile();
    glutInit(&argc, argv);            
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Bunny");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutMainLoop();
    return 0;
}