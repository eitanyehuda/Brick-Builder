# Brick-Builder
LEGO Style 3D Brick editor 

![Screenshot2](https://user-images.githubusercontent.com/23744162/146427726-575880db-034a-4fef-8af9-223873412a64.png)
![Screenshot1](https://user-images.githubusercontent.com/23744162/146424235-4c6b38d0-9ff7-45b7-aee3-2c161b6a0653.png)

Eitan Yehuda
Thomas Britnell

Graphics Final project 2021


Program Usage:

Welcome to BrickBuilder!

Click your left mouse button to place the object that is previwed

Right click and select from the menu the object type and colour that you wish to preview.

Click and drag with the middle mouse to move the camera around the scene.\nScroll with the middle mouse in and out.

Press h to show/hide the grid.

Press k to show/hide the lights

Press [ and ] to increase/decrease the level at which you are placing bricks.

Press c to clear the screen of bricks.

Press r to rotate the brick preview.

Press l (L) to toggle the lights being on or off.

Press s to save. You need to enter a filename with .txt on the end of it for this to work. It is saved in the same directory as the exe.

Press o to open a file. You need to enter the full file name including .txt, and it needs to be in the same directory as the exe.

NOTE: you will notice that the ring around the grid will change colour depending on if a brick position is valid or not. Red for invalid, green for valid!



Design Decisions:


We have a number of different advanced graphics features working on this project.

This includes an .obj parser, with custom objects made by myself in blender that include normals and vertexes. 

These custom objects are able to be outfitted in multiple different material colours, which is selectable by the user.

There are multiple light sources as part of the scene which give objects local shading based on their normals. 

The camera movement implemented is significantly more advanced than just moving the camera in a single direction at a time with buttons. 

The project is streamlined with features such as an expanding grid, which allows the user to place their blocks freely without worrying about changing or selecting a grid size. 

The indication of whether a brick can be placed somewhere is elegantly integrated into the multifunctional ring around the grid.

This ring also serves to show the user which level their selected brick will be placed on. 

There is a wide variety of custom pieces which can be rotated to fit many different designs. 

Pressing the 'h' key allows users to turn off the grid and other UI elements if they wish to take a screenshot of their design.

You can easily save and load objects using the file input/output features. 

There is a max and a min level on how you can zoom, to make sure that the user never sees the clipping planes, making the program more professional.

There is also a max and a min level that the user can build; past a vertical limit they cannot place more bricks. This is to prevent them from placing bricks beyond what they can see with the camera.

Overall I think we are really pleased with how the project turned out! It was a really fun course! 
