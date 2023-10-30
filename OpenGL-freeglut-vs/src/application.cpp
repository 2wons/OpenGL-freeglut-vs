#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

float faceColor[3] = { 0.1f, 0.2f, 0.4f };

float leftEyeColor[3] = { 1.0f, 1.0f, 1.0f };

float rightEyeColor[3] = { 1.0f, 1.0f, 1.0f };

GLfloat facePos[2] = { 0.0f, 0.0f };
//test


GLuint faceVBO, leftEyeVBO, rightEyeVBO, mouthVBO;

void createVBO(GLuint* vboId, GLfloat* vertices, int size)
{
    glGenBuffers(1, vboId);
    glBindBuffer(GL_ARRAY_BUFFER, *vboId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void updateVBO(GLuint* vboId, GLfloat* vertices, int size) {
    glBindBuffer(GL_ARRAY_BUFFER, *vboId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void drawVBO(GLuint vboId, int size, float* color)
{
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3fv(color);
    glDrawArrays(GL_POLYGON, 0, size);
}

void face()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    // Draw face
    drawVBO(faceVBO, 4, faceColor);

    // Draw right eye
    drawVBO(rightEyeVBO, 4, rightEyeColor);

    // Draw left eye
    drawVBO(leftEyeVBO, 4, leftEyeColor);

    // Draw mouth
    glBindBuffer(GL_ARRAY_BUFFER, mouthVBO);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_LINES, 0, 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();  // Swap the front and back buffers
}

void changeEyeColor(float arr[])
{
    arr[0] = rand() / (float)RAND_MAX;
    arr[1] = rand() / (float)RAND_MAX;
    arr[2] = rand() / (float)RAND_MAX;
}

void onClick(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN) return;

    switch (button)
    {
    case GLUT_LEFT_BUTTON:    changeEyeColor(leftEyeColor);  break;

    case GLUT_RIGHT_BUTTON:   changeEyeColor(rightEyeColor); break;
    }

    glutPostRedisplay();
}

void onKeyPress(unsigned char key, int x, int y)
{
    bool positionChanged = false;
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'w':
    case 'W':
        facePos[1] += 0.05f;
        positionChanged = true;
        break;
    case 'a':
    case 'A':
        facePos[0] -= 0.05f;
        positionChanged = true;
        break;
    case 's':
    case 'S':
        facePos[1] -= 0.05f;
        positionChanged = true;
        break;
    case 'd':
    case 'D':
        facePos[0] += 0.05f;
        positionChanged = true;
        break;
    }

    if (positionChanged)
    {
        GLfloat faceVertices[] = {
            -0.5f + facePos[0], -0.5f + facePos[1],  0.0f,
            -0.5f + facePos[0],  0.5f + facePos[1],  0.0f,
            0.5f + facePos[0],  0.5f + facePos[1],  0.0f,
            0.5f + facePos[0], -0.5f + facePos[1],  0.0f,
        };

        GLfloat leftEyeVertices[] = {
            -0.3f + facePos[0], 0.1f + facePos[1], 0.0f,
            -0.3f + facePos[0], 0.2f + facePos[1], 0.0f,
            -0.2f + facePos[0], 0.2f + facePos[1], 0.0f,
            -0.2f + facePos[0], 0.1f + facePos[1], 0.0f,
        };

        GLfloat rightEyeVertices[] = {
            0.3f + facePos[0], 0.1f + facePos[1], 0.0f,
            0.3f + facePos[0], 0.2f + facePos[1], 0.0f,
            0.2f + facePos[0], 0.2f + facePos[1], 0.0f,
            0.2f + facePos[0], 0.1f + facePos[1], 0.0f
        };


        GLfloat mouthVertices[] = {
            -0.3f + facePos[0],  -0.15f + facePos[1], 0.0f,
            0.3f + facePos[0],  -0.15f + facePos[1], 0.0f
        };
        updateVBO(&faceVBO, faceVertices, sizeof(faceVertices));
        updateVBO(&leftEyeVBO, leftEyeVertices, sizeof(leftEyeVertices));
        updateVBO(&rightEyeVBO, rightEyeVertices, sizeof(rightEyeVertices));
        updateVBO(&mouthVBO, mouthVertices, sizeof(mouthVertices));
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("lab4 Babasa");
    glutDisplayFunc(face);
    glutKeyboardFunc(onKeyPress);
    glutMouseFunc(onClick);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    GLenum err = glewInit();

    if (err == GLEW_OK)
    {
        GLfloat faceVertices[] = {
            -0.5f + facePos[0], -0.5f + facePos[1],  0.0f,
            -0.5f + facePos[0],  0.5f + facePos[1],  0.0f,
            0.5f + facePos[0],  0.5f + facePos[1],  0.0f,
            0.5f + facePos[0], -0.5f + facePos[1],  0.0f,
        };

        GLfloat leftEyeVertices[] = {
            -0.3f + facePos[0], 0.1f + facePos[1], 0.0f,
            -0.3f + facePos[0], 0.2f + facePos[1], 0.0f,
            -0.2f + facePos[0], 0.2f + facePos[1], 0.0f,
            -0.2f + facePos[0], 0.1f + facePos[1], 0.0f,
        };

        GLfloat rightEyeVertices[] = {
            0.3f + facePos[0], 0.1f + facePos[1], 0.0f,
            0.3f + facePos[0], 0.2f + facePos[1], 0.0f,
            0.2f + facePos[0], 0.2f + facePos[1], 0.0f,
            0.2f + facePos[0], 0.1f + facePos[1], 0.0f
        };


        GLfloat mouthVertices[] = {
            -0.3f + facePos[0],  -0.15f + facePos[1], 0.0f,
            0.3f + facePos[0],  -0.15f + facePos[1], 0.0f
        };
        createVBO(&faceVBO, faceVertices, sizeof(faceVertices));
        createVBO(&leftEyeVBO, leftEyeVertices, sizeof(leftEyeVertices));
        createVBO(&rightEyeVBO, rightEyeVertices, sizeof(rightEyeVertices));
        createVBO(&mouthVBO, mouthVertices, sizeof(mouthVertices));
        glutMainLoop();
    }
}