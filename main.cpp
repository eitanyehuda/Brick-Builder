#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <stack>

#include "header/board.h"
#include "header/camera.h"
#include "header/inputHandler.h"
#include "header/objParser.h"
#include "header/light.h"

int windowSizeX = 700;
int windowSizeY = 700;

char oneByOnePath[] = "ObjectFiles/oneByOne.obj";
char twoByTwoPath[] = "ObjectFiles/twoByTwo.obj";
char twoByThreePath[] = "ObjectFiles/twoByThree.obj";
char twoByFourPath[] = "ObjectFiles/twoByFour.obj";

Board board;
Camera camera;

Light l1;
Light l2;

Camera *InputHandler::camera;
Board *InputHandler::board;
std::vector<Light *> InputHandler::lights;
bool Light::lightsOn;

Mesh oneByOneMesh;
Mesh twoByTwoMesh;
Mesh twoByThreeMesh;
Mesh twoByFourMesh;

void loadMaterial(MaterialType mType, bool lightsOn){
    Material mat = Material(mType);

    if (lightsOn){
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat.amb);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat.diff);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat.spec);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat.shiny);
    }else{
        glColor3f(mat.diff[0],mat.diff[1],mat.diff[2]);
    }
}

void printInstructions()
{

    char inst[] = "Welcome to BrickBuilder!\n"
    "Click your left mouse button to place the object that is previwed\n"
    "Right click and select from the menu the object type and colour that you wish to preview.\n"
    "Click and drag with the middle mouse to move the camera around the scene.\n"
    "Scroll with the middle mouse in and out.\n"
    "Press h to show/hide the grid.\n"
    "Press k to show/hide the lights\n"
    "Press [ and ] to increase/decrease the level at which you are placing bricks.\n"
    "Press c to clear the screen of bricks.\n"
    "Press r to rotate the brick preview.\n"
    "Press l (L) to toggle the lights being on or off.\n"
    "Press s to save. You need to enter a filename with .txt on the end of it for this to work. It is saved in the same directory as the exe.\n"
    "Press o to open a file. You need to enter the full file name including .txt, and it needs to be in the same directory as the exe.\n"
    "NOTE: you will notice that the ring around the grid will change colour depending on if a brick position is valid or not. Red for invalid, green for valid!\n"
    ;

    std::cout << inst << std::endl;
}

/* init function - initializes everything at the begining */
void init(void)
{
    Point3D origin = Point3D(0, 0, 0);

    board = Board(origin, 5, 10, 10, std::vector<Brick>());
    camera = Camera(Point3D(1, 100, 100), origin, Vec3D(0, 1, 0));
    InputHandler::camera = &camera;
    InputHandler::board = &board;
    InputHandler::lights = std::vector<Light *>();

    l1 = Light();
    l1.position[1] = 50;
    l1.position[2] = -50;
    l2 = Light();
    l2.position[1] = 50;
    l2.position[2] = 50;
    InputHandler::lights.push_back(&l1);
    InputHandler::lights.push_back(&l2);
    Light::lightsOn = true;

    glEnable(GL_LIGHTING);

    for (int i = 0; i < InputHandler::lights.size(); i++)
    {
        int hex = 16384 + i; // the hex code for GL_LIGHT0 + i
        glEnable(hex);
    }

    oneByOneMesh = ObjParser::loadMesh(oneByOnePath);
    twoByTwoMesh = ObjParser::loadMesh(twoByTwoPath);
    twoByThreeMesh = ObjParser::loadMesh(twoByThreePath);
    twoByFourMesh = ObjParser::loadMesh(twoByFourPath);

    glClearColor(0.2, 0.2, 0.2, 0); // background colour
    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-100, 100, -100, 100, -500, 500);
    gluPerspective(45, 1, 1, 5000);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    printInstructions();
}

void drawGrid(Point3D center, int cellSize, int length, int width)
{
    glPushMatrix();

    glLineWidth(2);
    glTranslatef(center.mX, center.mY, center.mZ);
    glBegin(GL_LINES);

    loadMaterial(MaterialType::whiteRubber, Light::lightsOn);

    glNormal3f(0.0, 1.0, 0.0);

    // horizontal lines
    for (int i = -length; i <= length; i++)
    {
        glVertex3f(-width * cellSize, 0, i * cellSize);
        glVertex3f(width * cellSize, 0, i * cellSize);
    }
    // vertical lines
    for (int i = -width; i <= width; i++)
    {
        glVertex3f(i * cellSize, 0, -length * cellSize);
        glVertex3f(i * cellSize, 0, length * cellSize);
    }

    glEnd();
    glPopMatrix();
}

void drawAxis()
{
    float size = board.length * board.cellSize;

    glPushMatrix();

    glLineWidth(4);
    glBegin(GL_LINES);

    loadMaterial(MaterialType::redRubber, Light::lightsOn);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size, 0.0, 0.0);

    loadMaterial(MaterialType::yellowRubber, Light::lightsOn);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, size, 0.0);

    loadMaterial(MaterialType::blueRubber, Light::lightsOn);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, size);
    glEnd();

    glPopMatrix();
}

void drawMesh(MeshType meshType, MaterialType materialType, bool wireFrame)
{
    Mesh m;
    switch (meshType)
    {
    case 0: // 1 x 1
        m = oneByOneMesh;
        break;
    case 1: // 2 x 2
        m = twoByTwoMesh;
        break;
    case 2: // 2 x 3
        m = twoByThreeMesh;
        break;
    case 3: // 2 x 4
        m = twoByFourMesh;
        break;
    default: // 2 x 3
        m = twoByThreeMesh;
        break;
    }

    glBegin(GL_TRIANGLES);

    loadMaterial(materialType, Light::lightsOn);

    for (int i = 0; i < m.vertices.size(); i++)
    {
        if (m.vertices.size() != m.normals.size())
        {
            break;
        }

        Vec3D normal = m.normals.at(i);
        Point3D vertex = m.vertices.at(i);
        glNormal3f(normal.mX, normal.mY, normal.mZ);
        glVertex3f(vertex.mX, vertex.mY, vertex.mZ);
    }
    glEnd();
}

void drawBricks()
{
    for (Brick b : board.bricks)
    {
        glPushMatrix();

        glTranslatef(b.position.mX * board.cellSize, b.position.mY, (b.position.mZ + b.orientation) * board.cellSize);
        glRotatef(b.orientation * 90, 0, 1, 0);

        drawMesh(b.meshType, b.material, false);

        glPopMatrix();
    }
}

void drawPlane(Point3D planePosition, int cellSize, int length, int width)
{
    glPushMatrix();

    glLineWidth(3);
    glTranslatef(planePosition.mX, planePosition.mY, planePosition.mZ);

    glBegin(GL_LINES);

    if (board.checkAvailable())
    {

        loadMaterial(MaterialType::greenRubber, Light::lightsOn);
    }
    else
    {
        loadMaterial(MaterialType::redRubber, Light::lightsOn);
    }

    glNormal3f(0.0, 1.0, 0.0);

    glVertex3f(-width * cellSize, 0, -length * cellSize);
    glVertex3f(width * cellSize, 0, -length * cellSize);

    glVertex3f(-width * cellSize, 0, length * cellSize);
    glVertex3f(width * cellSize, 0, length * cellSize);

    glVertex3f(-length * cellSize, 0, -width * cellSize);
    glVertex3f(-length * cellSize, 0, width * cellSize);

    glVertex3f(length * cellSize, 0, -width * cellSize);
    glVertex3f(length * cellSize, 0, width * cellSize);

    glEnd();

    glPopMatrix();
}

void drawWireFrame()
{
    glPushMatrix();

    glTranslatef(board.selectedWireframe.position.mX * board.cellSize, board.selectedWireframe.position.mY, (board.selectedWireframe.position.mZ + board.selectedWireframe.orientation) * board.cellSize);
    glRotatef(board.selectedWireframe.orientation * 90, 0, 1, 0);

    drawMesh(board.selectedWireframe.meshType, board.selectedWireframe.material, true);

    glPopMatrix();
}

void drawFloor(Point3D center, int cellSize, int length, int width)
{
    glPushMatrix();

    glTranslatef(center.mX, center.mY, center.mZ);

    glBegin(GL_QUADS);

    loadMaterial(MaterialType::translucentOrange, Light::lightsOn);

    glNormal3f(0.0, 1.0, 0.0);

    glVertex3f(width * cellSize, 0, -length * cellSize);
    glVertex3f(-width * cellSize, 0, -length * cellSize);

    glVertex3f(-width * cellSize, 0, length * cellSize);
    glVertex3f(width * cellSize, 0, length * cellSize);

    glEnd();

    glPopMatrix();
}

void drawBoard(Board *board)
{
    glPushMatrix();

    drawFloor(board->center, board->cellSize, board->length, board->width);
    drawBricks();
    drawWireFrame();
    if (!InputHandler::hideGrid)
    {
        drawAxis();
        drawPlane(board->plane.position, board->cellSize, board->length, board->width);
        drawGrid(board->center, board->cellSize, board->length, board->width);
    }

    glPopMatrix();
}

void processLights(bool show)
{

    int i = 0;
    for (auto &light : InputHandler::lights)
    {
        glPushMatrix();

        int hex = 16384 + i;
        glLightfv(hex, GL_POSITION, light->position);
        glLightfv(hex, GL_DIFFUSE, light->values[0]);
        glLightfv(hex, GL_AMBIENT, light->values[1]);
        glLightfv(hex, GL_SPECULAR, light->values[2]);

        if (show)
        {
            glTranslatef(light->position[0], light->position[1], light->position[2]);

            loadMaterial(MaterialType::yellowRubber, Light::lightsOn);

            glutSolidSphere(3, 16, 16);
        }

        glPopMatrix();
        i++;
    }
}

/* display function - draws everything */
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera.position.mX, camera.position.mY, camera.position.mZ, camera.target.mX, camera.target.mY, camera.target.mZ, camera.upVector.mX, camera.upVector.mY, camera.upVector.mZ);

    glRotatef(-camera.rotation[0], 1, 0, 0);
    glRotatef(camera.rotation[1], 0, 1, 0);

    drawBoard(&board);

    processLights(!InputHandler::hideLights);

    glutSwapBuffers();
}

void update(int unused)
{
    glutPostRedisplay();
    glutTimerFunc(17, update, 0);
}

/* main function - program entry point */
int main(int argc, char **argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);                                    // starts up GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Sets dispaly mode to double,rgb,depth

    glutInitWindowSize(windowSizeX, windowSizeY);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Brick Builder"); // creates the window

    glutDisplayFunc(drawScene); // registers "display" as the display callback function
                                // glutReshapeFunc(reshape);
    glutKeyboardFunc(InputHandler::keyboard);
    // glutSpecialFunc(special);
    glutMouseFunc(InputHandler::mouse);
    glutMotionFunc(InputHandler::motion);
    glutPassiveMotionFunc(InputHandler::passiveMotion);

    InputHandler::createGLUTMenu();

    glutTimerFunc(17, update, 0); // timer

    glEnable(GL_DEPTH_TEST); // culling
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    init();

    glutMainLoop(); // starts the event loop

    return (0); // return may not be necessary on all compilers
}