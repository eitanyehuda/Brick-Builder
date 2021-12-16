#include "header/inputHandler.h"

const int VERTICAL_MAX = 40;

Point3D InputHandler::initialMiddleClickPosition;
float InputHandler::previousMiddleClickPosition[2];
bool InputHandler::rightClick;
bool InputHandler::leftClick;
bool InputHandler::middleClick;


bool InputHandler::hideGrid =false;
bool InputHandler::hideLights = true;

//The ray created when the mouse is clicked
GLdouble start[3] = {0,0,0};
GLdouble end[3] = {0,0,0};

std::stack<PlaceBrickCommand> InputHandler::actionStack = std::stack<PlaceBrickCommand>();

Vec3D InputHandler::mouseRay = Vec3D();
Point3D InputHandler::planeIntercept = Point3D();

void InputHandler::mouse(int button, int state, int x , int y){
    y = 700 - y; // flip y
    PlaceBrickCommand c;

    if (button == GLUT_LEFT_BUTTON) // LMB pressed
    {
        if (state == GLUT_UP)
        {
            leftClick = false;
        }
        if (state == GLUT_DOWN)
        {
            leftClick = true;

            InputHandler::updateMouseRay(x,y);

            if (board->checkAvailable() && InputHandler::checkGridIntersection()){

                Point3D positionOnBoard = InputHandler::mousePositionOnBoard();
                // positionOnBoard = positionOnBoard.multiply(board->cellSize); //scale to board

                c = PlaceBrickCommand(Brick(positionOnBoard,board->selectedWireframe.orientation, board->selectedWireframe.material, board->selectedWireframe.meshType),board);
                
                actionStack.push(c);
                actionStack.top().execute();

            }
        }
    }

    else if (button == GLUT_MIDDLE_BUTTON) // MMB pressed
    {
        if (state == GLUT_UP)
        {
            middleClick = false;
            previousMiddleClickPosition[0] = camera->rotation[0]; // y position of mouse
            previousMiddleClickPosition[1] = camera->rotation[1]; // x position of mouse
        }
        if (state == GLUT_DOWN)
        {
            middleClick = true;
            initialMiddleClickPosition = Point3D(x,y,0);
        }
    }

    else if(button == 3){//mouse scroll up
        if (state == GLUT_UP){return;}
        camera->zoomIn();
    }

    else if(button == 4){//mouse scroll down
        if (state == GLUT_UP){return;}
        camera->zoomOut();
    }
}

//Mouse movement
void InputHandler::motion(int x, int y){
    y = 700 - y; // flip y locally

    if(middleClick){
        Vec3D clickDistance = Vec3D::createVector(initialMiddleClickPosition, Point3D(x,y,0));
        camera->rotation[1] = clickDistance.mX + previousMiddleClickPosition[1]; // y axix rotation depends on x coords of mouse
        camera->rotation[0] = clickDistance.mY + previousMiddleClickPosition[0]; // x axis rotation depends on y coords of mouse
    }
}

void InputHandler::passiveMotion(int x, int y){
    y = 700 - y; // flip y locally

    InputHandler::updateMouseRay(x,y);
    if (InputHandler::checkGridIntersection()){
        Point3D positionOnBoard = InputHandler::mousePositionOnBoard();
        board->selectedWireframe.position = positionOnBoard;
        board->resizeGrid();
    }
    else{
        board->width+=1;
        board->length+=1;
    }
}

void InputHandler::updateMouseRay(int x, int y){ // will return cursor position on board (using ray tracing)
//adapted from lecture code

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ; // click coords

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (float)x;
    winY = (float)y;

    //near plane
    gluUnProject(winX,winY,0.0,modelview,projection,viewport,&start[0],&start[1],&start[2]);

    //far plane
    gluUnProject(winX,winY,1.0,modelview,projection,viewport,&end[0],&end[1],&end[2]);

    Vec3D newRay = Vec3D::createVector(Point3D(start[0],start[1],start[2]),Point3D(end[0],end[1],end[2]));
    newRay.start = Point3D(start[0], start[1], start[2]); 
    InputHandler::mouseRay = newRay;
}

bool InputHandler::checkGridIntersection(){
    Point3D intercept = board->plane.rayPlaneIntersection(InputHandler::mouseRay);
    if (intercept.mX < board->width*board->cellSize && intercept.mX >= -board->width*board->cellSize
        && intercept.mZ < board->length*board->cellSize && intercept.mZ >= -board->length*board->cellSize){
            InputHandler::planeIntercept = intercept;
            return true;
    }
    return false;
}

Point3D InputHandler::mousePositionOnBoard(){
    int interceptX = InputHandler::planeIntercept.mX;
    int interceptZ = InputHandler::planeIntercept.mZ;
    if(interceptX < 0){
        interceptX -= board->cellSize;
    }
    if(interceptZ < 0){
        interceptZ -= board->cellSize;
    }

    int x = interceptX / board->cellSize;
    int y = InputHandler::board->plane.position.mY; // level of the board
    int z = interceptZ / board->cellSize;

    return Point3D(x,y,z);
}

void InputHandler::processMenuEvents(int option) {

	switch (option) {
        //one by one
		case 0 :
            board->selectedWireframe.meshType = MeshType::oneByOne;
            board->selectedWireframe.material = MaterialType::ruby;
			break;
		case 1 :
            board->selectedWireframe.meshType = MeshType::oneByOne;
            board->selectedWireframe.material = MaterialType::bluePlastic;
			 break;
		case 2 :
            board->selectedWireframe.meshType = MeshType::oneByOne;
            board->selectedWireframe.material = MaterialType::gold;
			break;
        case 3 :
            board->selectedWireframe.meshType = MeshType::oneByOne;
            board->selectedWireframe.material = MaterialType::orangeRubber;
			 break;
		case 4 :
            board->selectedWireframe.meshType = MeshType::oneByOne;
            board->selectedWireframe.material = MaterialType::whiteRubber;
			break;

        //two by three
		case 5 :
            board->selectedWireframe.meshType = MeshType::twoByTwo;
            board->selectedWireframe.material = MaterialType::ruby;
            break;
        case 6 :
            board->selectedWireframe.meshType = MeshType::twoByTwo;
            board->selectedWireframe.material = MaterialType::bluePlastic;
            break;
        case 7 :
            board->selectedWireframe.meshType = MeshType::twoByTwo;
            board->selectedWireframe.material = MaterialType::gold;
            break;
        case 8 :
            board->selectedWireframe.meshType = MeshType::twoByTwo;
            board->selectedWireframe.material = MaterialType::orangeRubber;
			 break;
		case 9 :
            board->selectedWireframe.meshType = MeshType::twoByTwo;
            board->selectedWireframe.material = MaterialType::whiteRubber;
			break;

        //two by four
        case 10 :
            board->selectedWireframe.meshType = MeshType::twoByThree;
            board->selectedWireframe.material = MaterialType::ruby;
            break;
        case 11 :
            board->selectedWireframe.meshType = MeshType::twoByThree;
            board->selectedWireframe.material = MaterialType::bluePlastic;
            break;
        case 12 :
            board->selectedWireframe.meshType = MeshType::twoByThree;
            board->selectedWireframe.material = MaterialType::gold;
            break;
        case 13 :
            board->selectedWireframe.meshType = MeshType::twoByThree;
            board->selectedWireframe.material = MaterialType::orangeRubber;
			 break;
		case 14 :
            board->selectedWireframe.meshType = MeshType::twoByThree;
            board->selectedWireframe.material = MaterialType::whiteRubber;
			break;

        //two by five
        case 15 :
            board->selectedWireframe.meshType = MeshType::twoByFour;
            board->selectedWireframe.material = MaterialType::ruby;
            break;
        case 16 :
            board->selectedWireframe.meshType = MeshType::twoByFour;
            board->selectedWireframe.material = MaterialType::bluePlastic;
            break;
        case 17 :
            board->selectedWireframe.meshType = MeshType::twoByFour;
            board->selectedWireframe.material = MaterialType::gold;
            break;
        case 18 :
            board->selectedWireframe.meshType = MeshType::twoByFour;
            board->selectedWireframe.material = MaterialType::orangeRubber;
			 break;
		case 19 :
            board->selectedWireframe.meshType = MeshType::twoByFour;
            board->selectedWireframe.material = MaterialType::whiteRubber;
			break;
	}
    board->selectedWireframe.allignOffsets();
}

void InputHandler::createGLUTMenu() {

	//submenus then main menu
    int sub1 = glutCreateMenu(InputHandler::processMenuEvents);
    glutAddMenuEntry("Red",0);
    glutAddMenuEntry("Blue",1);
    glutAddMenuEntry("Yellow",2);
    glutAddMenuEntry("Orange",3);
    glutAddMenuEntry("Grey",4);
    int sub2 = glutCreateMenu(InputHandler::processMenuEvents);
    glutAddMenuEntry("Red",5);
    glutAddMenuEntry("Blue",6);
    glutAddMenuEntry("Yellow",7);
    glutAddMenuEntry("Orange",8);
    glutAddMenuEntry("Grey",9);
    int sub3 = glutCreateMenu(InputHandler::processMenuEvents);
    glutAddMenuEntry("Red",10);
    glutAddMenuEntry("Blue",11);
    glutAddMenuEntry("Yellow",12);
    glutAddMenuEntry("Orange",13);
    glutAddMenuEntry("Grey",14);
    int sub4 = glutCreateMenu(InputHandler::processMenuEvents);
    glutAddMenuEntry("Red",15);
    glutAddMenuEntry("Blue",16);
    glutAddMenuEntry("Yellow",17);
    glutAddMenuEntry("Orange",18);
    glutAddMenuEntry("Grey",19);
       
    int menu = glutCreateMenu(InputHandler::processMenuEvents);
   
    glutAddSubMenu("1x1", sub1);
    glutAddSubMenu("2x2", sub2);
    glutAddSubMenu("2x3", sub3);
    glutAddSubMenu("2x4", sub4);
    
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void prepareDataForSave(float* data){
    
    data[0] = static_cast<float>(InputHandler::board->bricks.size());


    int i  = 1;

    for (Brick brick: InputHandler::board->bricks){
        data[i] = brick.position.mX; 
        data[i+1] = brick.position.mY; 
        data[i+2] = brick.position.mZ; 
        data[i+3] = brick.orientation;
        data[i+4] = static_cast<float>(brick.material);
        data[i+5] = static_cast<float>(brick.meshType);

        i+= FileHandler::BRICK_DATA_SIZE;
    }
}

void loadScene(std::vector<float> data){
    InputHandler::board->bricks.clear();
    while (!InputHandler::actionStack.empty()){
        InputHandler::actionStack.pop();
    }

    for(int i = 0; i < data.at(0); i++){
        int j = i*FileHandler::BRICK_DATA_SIZE + 1;
        Brick temp = Brick(Point3D(data.at(j),data.at(j+1),data.at(j+2)),data.at(j+3),static_cast<MaterialType>(data.at(j+4)), static_cast<MeshType>(data.at(j+5)));

        InputHandler::board->bricks.push_back(temp);
    }

}


void InputHandler::keyboard(unsigned char key, int x, int y){
    std::string input;
    
    int datasize = 1+InputHandler::board->bricks.size()*FileHandler::BRICK_DATA_SIZE;
    float data[datasize];

    std::vector<float> loadedData;


    switch (key){
        case 27:
            exit(0);
        break;
        case 'U':
        case 'u':
            if(!actionStack.empty()){
                actionStack.top().undo();
                actionStack.pop();
            }
        break;
        case 'H':
        case 'h':
            InputHandler::hideGrid = !InputHandler::hideGrid;
        break;
        case 'K':
        case 'k':
            InputHandler::hideLights = !InputHandler::hideLights;
        break;

        case ']':
            if (board->plane.position.mY < VERTICAL_MAX){
                board->plane.position.mY += board->cellSize;
            } 
        break;
        case '[':
            if (board->plane.position.mY > 0){
                board->plane.position.mY -= board->cellSize;
            }
        break;
        case 'C':
        case 'c':
            board->bricks.clear();
        break;
        case 'R':
        case 'r':
            board->selectedWireframe.orientation = (board->selectedWireframe.orientation + 1 ) % 2;
            board->selectedWireframe.allignOffsets();
        break;
        case 'L':
        case 'l':
            Light::lightsOn = !Light::lightsOn;
            if (Light::lightsOn){
                glEnable(GL_LIGHTING);
                for(int i = 0; i < InputHandler::lights.size(); i++){
                    int hex = 16384 + i;//the hex code for GL_LIGHT0 + i
                    glEnable(hex);
                }
            }
            else{
                glDisable(GL_LIGHTING);
                for(int i = 0; i < InputHandler::lights.size(); i++){
                    int hex = 16384 + i;
                    glDisable(hex);
                }
            }
        break;
        case 'S' :
        case 's' :
            std::cout << "enter the filename including extension .txt"  << std::endl;
            std::cin >> input;

            prepareDataForSave(data);

            FileHandler::saveFile(input,data);
        break; 
        case 'O':
        case 'o':   
            std::cout << "enter the filename to open including extension .txt"  << std::endl;
            std::cin >> input;

            if (FileHandler::loadFile(input,&loadedData) == 0){
                loadScene(loadedData);
            }
            else{
                std::cout<<"File Invalid!" <<std::endl;
            }
        break;
    }
}