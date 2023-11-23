

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;
void displayObject();
void init();

float cameraX = 0.0, cameraY = 3.0, cameraZ = 4.0;  // camera

void onKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': cameraZ -= 0.1f; break;
    case 's': cameraZ += 0.1f; break;
    case 'a': cameraX -= 0.1f; break;
    case 'd': cameraX += 0.1f; break;
    }
    glutPostRedisplay();
}

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 768);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("simple");
    init();
    glutDisplayFunc(displayObject);
    glutKeyboardFunc(onKeyPress);
    GLenum err = glewInit();
    if (err == GLEW_OK)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        printf("OpenGL version supported by this platform (%s): \n",
            glGetString(GL_VERSION));
        printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
        glutMainLoop();
    }
}

void displayObject()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // General Light
    GLfloat lmodelambient[] = { .2, .2, .2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodelambient);
    // Material
    GLfloat math_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // Blue
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, math_ambient);
    // Directional Light
    GLfloat lightposition0[] = { -1.0f, 0.0f, 2.0f, 1.0f };
    GLfloat lightcolor0[] = { 0.5f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightposition0);
    // Spotlight
    GLfloat lightposition1[] = { 0.0f, 4.0f, 0.0f, 1.0f };
    GLfloat lightcolor1[] = { 1.0f, 0.2f, 0.2f, 1.0f };
    GLfloat spotdirection[] = { 0.0f, -1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightcolor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightposition1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);

    // display octahedron
    glutSolidOctahedron();
    glFlush();
}

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1024.0 / 768.0, 1.0, 10.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}