#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<vector<float>> vertices;      // contains vertices by their index number
vector<vector<int>> faces;           // contains vector of faces
GLfloat light_diffuse[] = {211/255.0F,211/255.0F,211/255.0F, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 2.0, 1.0, 0.0};  /* Infinite light location. */

vector<float> findNormal(vector<float> v1,vector<float> v2,vector<float> v3)
{
    float e1x=v2[0]-v1[0];
    float e1y=v2[1]-v1[1];
    float e1z=v2[2]-v1[2];

    float e2x=v3[0]-v1[0];
    float e2y=v3[1]-v1[1];
    float e2z=v3[2]-v1[2];

    float normx=e1y*e2z-e1z*e2y;
    float normy=e1z*e2x-e1x*e2z;
    float normz=e1x*e2y-e1y*e2x;

    float norm=normx*normx+normy*normy+normz*normz;
    norm=sqrt(norm);

    normx/=norm;
    normy/=norm;
    normz/=norm;

    return {normx,normy,normz};
}
 
void initGL()
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glClearColor(124/255.0F,252/255.0F,0/255.0F,1.0f);
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
    glTranslatef(0.05f, -0.2f, -0.5f); 

    for(int i=0;i<faces.size();i++)
    {
        glBegin(GL_TRIANGLES);
            vector<float> vert1=vertices[faces[i][0]];
            vector<float> vert2=vertices[faces[i][1]];
            vector<float> vert3=vertices[faces[i][2]];
            vector<float> norm=findNormal(vert1,vert2,vert3);
            glNormal3f(norm[0],norm[1],norm[2]);
            glColor3f(1,0,0);
            glVertex3f(vert1[0],vert1[1],vert1[2]);
            glColor3f(0,1,0);     
            glVertex3f(vert2[0],vert2[1],vert2[2]);
            glColor3f(0,0,1);
            glVertex3f(vert3[0],vert3[1],vert3[2]);
        glEnd();
    }
    
    glutSwapBuffers();
}
 

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;                        // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);                        // To operate on the Projection matrix
    glLoadIdentity();                                   // Reset
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void readObjFile(int argc, char** argv)
{
    vertices.push_back({});                             // vertices are not zero indexed
    ifstream infile(argv[argc-1]);
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
            faces.push_back({(int)a,(int)b,(int)c});
    }
}
 
int main(int argc, char** argv) {
    readObjFile(argc,argv);
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