/*Include the generic C libaries for loops, pointers ect*/
#include <stdio.h>
#include <stdlib.h>

/*Include the C maths libaries*/
#include <math.h>

/*Contains the graphical package*/
#include <graphics_lib.h>

/*Defines the moon structure for stopring details related to the moon*/
struct moon_struct
{

    /*
    x - x coodinate of centre of moon
    y - y coordinate of centre of moon
    d - diameter of moon
    i - radius of area of gravitational infuence
    */

    int x;
    int y;
    int d;
    int i;

};

/*Defines the rocket struct for stopring details related to the rocket*/
struct rocket_struct
{

    /*
    x - x coordinate of the rockets current location
    y - y coordinate of the rockets current location
    v - the rocket's current velocity
    a - the rockets launch angle as chosen by the user
    m - the mass of the rocket
    d - the distance travelled by the rocket
    f - the force of attraction acting on the rocket
    ar - the launch angle in radians
    */

    double x;
    double y;
    double v;
    double a;
    double m;
    double d;
    double f;
    double ar;

};

/*Sets up the GFX window and runs the first game*/
int main(void)
{

    /*Open 640x480 GFX window*/
    GFX_InitWindow(1280, 720);

    /*Initiate text, event queue and bitmap handling
    The order of this cannot be changed*/
    GFX_InitFont();

    /*Register mouse and keyboard events*/
    GFX_CreateEventQueue();
	GFX_InitMouse();
	GFX_RegisterMouseEvents();
	GFX_InitKeyboard();
	GFX_RegisterKeyboardEvents();

	/*Initiate bitmap handling*/
    GFX_InitBitmap();


    /*Call to activate random number generator*/
    srand (time(NULL));

    /*Draw the background*/
    drawBackground();

    /*Show the welcome screen text*/
    welcomeScreen();

    /*Write these changes to the screen*/
    GFX_UpdateDisplay();

    /*Wait for the user to press enter, as displayed by the welcome screen
    This is useful for creating in program breakpoints*/
    waitForEnter();

    /*Run the main game loop, this calls the endgame function post gameplay*/
    playGame();

    /*Quit the whole program, the 0 represents a succsessful execution*/
    return 0;

}

/*Presents the user with a logo/press key to continue screen*/
void welcomeScreen(void)
{

    /*Draw the title on screen*/
    GFX_DrawText(590, 130, "Interstellar");

    /*Draw the how to play instructions*/
    GFX_DrawText(540, 200, "You must travel to Mars");
    GFX_DrawText(470, 250, "This means selecting an appropriate velocity");
    GFX_DrawText(420, 300, "and angle of launch, remember to factor in the effect");
    GFX_DrawText(550, 350, "of the moons gravity");

    /*Draw the continue prompt onscreen*/
    GFX_DrawText(540, 480, "Press enter to continue...");

    /*Leave the function*/
    return;

}

/*Waits for the user to press enter, the returns nothing*/
void waitForEnter(void)
{

    /*Create an local int variable called keyPressed to store which key the user presses*/
    int keyPressed;

    /*Create a while loop to run while done = 0*/
	while (true)
	{

        /* Wait for an keyboard or mouse event*/
        GFX_WaitForEvent();

        /*Check the event queue to see if the event registered is a key press*/
        if (GFX_IsEventKeyDown())
        {

            /*If the event was a key press get the allegro assigned integer for that key*/
            GFX_GetKeyPress(&keyPressed);

            /*Check to see if the key pressed is 67, as assigned by allegro*/
            if (keyPressed == ALLEGRO_KEY_ENTER)
            {

                /*If it is enter, return to main()*/
                return;

            }

        }

    }

}

/*Calculate random properties for the moon - stored in struct moon, needs the moon structure*/
void calculateMoon(struct moon_struct * moon)
{

    /*Get random numbers for x, y and r for the creation of the moon*/
    moon->x = GFX_RandNumber(350, 930);
    moon->y = GFX_RandNumber(350, 370);

    /*Create an local int variable to store the randomly generated diameter option*/
    int diameterOption;

    /*Get a random bumber between 1 and 5 to choose between the 5 .bmp files for the 5 different moon sizes*/
    diameterOption = GFX_RandNumber(1, 5);

    /*Translate the randomly generated diameter option */
    switch (diameterOption)
    {

        /*
        This whole switch statement follows the same outline as below
        Moon diameters are...

        Ran Int - Diameter

        1 - 75
        2 - 100
        3 - 125
        4 - 150
        5 - 175
        */

        /*If the randomly generated number is 1*/
        case 1:

            /*Set the diameter in the class to 75*/
            moon->d = 75;

            /*Leave the switch statement*/
            break;

        case 2:
            moon->d = 100;
            break;

        case 3:
            moon->d = 125;
            break;

        case 4:
            moon->d = 150;
            break;

        case 5:
            moon->d = 175;
            break;

    }

    /*Calculate and store the moon's area of influence's radius - the diameter is useless in calculation*/
    moon->i = ((moon->d /2) * 5);

    /*Return*/
    return;

}

/*Draws the Earth, Mars and the Moon, needs the moon structure*/
void drawPlanets(struct moon_struct * moon)
{

    /*Bitmaps all follow the same structure, as outlined on the earth bitmap,
    Individual detals can be found abouve each decleration statement
    Bitmap's must have clear backgrounds as background management was not implemented*/

    /*Identifier - Size in pixels - Coordinates*/
    /*Earth - 300x300 - 130,130*/

    /*BITMAP - typedef for bitmaps
      earthBitmap - variable name of bitmap
      GFX_LoadBitmap - call GFX libarys bitmap loading function
      which takes the file path from the parent directory where
      the code blocks project is stored
    */
    BITMAP earthBitmap = GFX_LoadBitmap("Bitmaps/Earth.bmp");

    /*Use the GFX_DrawBitmap function to draw the bitmap - has to be loaded prior to this
    DrawBitmap takes the arguments "Bitmap variable name" and the coordinates where the centre of the bitmap
    will be drawn as comma seperated variables*/
    GFX_DrawBitmap(earthBitmap, 130, 130);

    /*Free up some memory by "unloading" the bitmap, takes the variable name of the loaded bitmap as an argument*/
	GFX_FreeBitmap(earthBitmap);

	/*Mars - 150x150 @ 590,450*/
	BITMAP marsBitmap = GFX_LoadBitmap("Bitmaps/Mars.bmp");
	GFX_DrawBitmap(marsBitmap, 1200, 640);
	GFX_FreeBitmap(marsBitmap);

    /*Position the moon at the randomly generated cordinates
    The diameter is checked against the size of the bitmaps
    And then the correctly sized bitmap is implemented
    Following the same layout as above*/
    if (moon->d == 75)
    {

        /*Moon - 75x75 @ moon->x, moon->y*/
        BITMAP moonBitmap = GFX_LoadBitmap("Bitmaps/Moon75.bmp");
        GFX_DrawBitmap(moonBitmap, moon->x, moon->y);
        GFX_FreeBitmap(moonBitmap);

    }

    if (moon->d == 100)
    {

        /*Moon - 100x100 @ moon->x, moon->y*/
        BITMAP moonBitmap = GFX_LoadBitmap("Bitmaps/Moon100.bmp");
        GFX_DrawBitmap(moonBitmap, moon->x, moon->y);
        GFX_FreeBitmap(moonBitmap);

    }

    if (moon->d == 125)
    {

        /*Moon - 125x125 @ moon->x, moon->y*/
        BITMAP moonBitmap = GFX_LoadBitmap("Bitmaps/Moon125.bmp");
        GFX_DrawBitmap(moonBitmap, moon->x, moon->y);
        GFX_FreeBitmap(moonBitmap);

    }

    if (moon->d == 150)
    {

        /*Moon - 150x150 @ moon->x, moon->y*/
        BITMAP moonBitmap = GFX_LoadBitmap("Bitmaps/Moon150.bmp");
        GFX_DrawBitmap(moonBitmap, moon->x, moon->y);
        GFX_FreeBitmap(moonBitmap);

    }

    if (moon->d == 175)
    {

        /*Moon - 175x175 @ moon->x, moon->y*/
        BITMAP moonBitmap = GFX_LoadBitmap("Bitmaps/Moon175.bmp");
        GFX_DrawBitmap(moonBitmap, moon->x, moon->y);
        GFX_FreeBitmap(moonBitmap);

    }

    /*Set the GFX libaries pen colour of white - integer value 11*/
    GFX_SetColour(11);

    /*Draw a circle, colour specified above, to represent the moons maximum area of influence*/
    GFX_DrawCircle(moon->x, moon->y, moon->d/2*5, 5);

    GFX_DrawText(20, 500, "Use the arrow keys");
    GFX_DrawText(20, 520, "to control the ");
    GFX_DrawText(20, 540, "launch parameters");
    GFX_DrawText(20, 560, "Press enter to launch...");

    /*Draw the angle promt at the top of the screen*/
    GFX_DrawLine(200, 20, 300, 20, 2);
    GFX_DrawLine(200, 20, 290, 60, 2);
    GFX_DrawArc(200, 20, 40, 0, 27, 2);

    /*Leave the function*/
    return;

}

/*Draws the background on the GFX screen*/
void drawBackground(void)
{

    /*Background BITMAP*/
    /*For more information on the drawing of bitmaps see drawPlaets()*/
	BITMAP backgroundBitmap = GFX_LoadBitmap("Bitmaps/Background.bmp");
    GFX_DrawBitmap(backgroundBitmap, 640, 360);
	GFX_FreeBitmap(backgroundBitmap);

    /*Leave the function*/
	return;
}

/*Draw the users current velocity and launch angle, needs the rocket structure*/
void drawControlBoard(struct rocket_struct * rocket)
{

    /*Create an array to store the rockets current angle of travel
    and after that, the velocity*/
    char text[20];

    /*Convert the rockets angle of travel into a string from a double
    and store in the string "text".
    This has to be done as the angle is stored as a double and cannot
    be printed to the GFX screen as text.*/
    sprintf(text, "%lf", rocket->a);

    /*Draw a black rectange to provide a background for the data, this improves readability
    and prevents clashes with the moons AoE ring - also white*/
    GFX_DrawFilledRectangle(20,655,320,700,0);

    /*Draw the text shown below at the sppecified coordinates*/
    GFX_DrawText(25, 660, "Launch Angle in degrees:");

    /*Draw the contents of the string "text"*/
    GFX_DrawText(230, 660, text);

    /*Convert the double (rockets velocity) into a string and store in "text"*/
    sprintf(text, "%lf", rocket->v);

    /*Draw the contents of the string "text"*/
    GFX_DrawText(230, 680, text);

    /*Draw the text shown below at the sppecified coordinates*/
    GFX_DrawText(25, 680, "Velocity in KM/s:");

    /*Leave the function*/
    return;

}

/*Draws the rocket using the location stored in the rocket struct, needs rocket passing too it*/
void drawRocket(struct rocket_struct * rocket)
{

    /*Convert the double values of the rockets location to int so
    they are compatable with the GFX lib's bitmap writer*/
    int mapX = rocket->x;
    int mapY = rocket->y;

    /*WRite the rocket to the screen - more details on bitmap writing can be found in drawPlanets()*/
    BITMAP rocketBitmap = GFX_LoadBitmap("Bitmaps/Rocket.bmp");
    GFX_DrawBitmap(rocketBitmap, mapX, mapY);
	GFX_FreeBitmap(rocketBitmap);

    /*Leave the function*/
    return;
}

/*Creates and stores a random integer, needs a max and min number passing to it*/
int getRandom(int max_number, int min_number)
{

    /*Declare the local variable to store the random number*/
    int random;

    /*Calculate the random number using rand()*/
    random = rand() % (max_number + 1 - min_number) + min_number;

    /*Return the newly calculates the random number, ending the function*/
    return random;

}

/*Move the rocket inside the moons ring of gravitational influence*/
void moveInsideAoE(struct rocket_struct * rocket, struct moon_struct * moon)
{

    /*A resultant force is calculated from the previous force acting on the rocket and the current force being applied to it by the moon*/

    /*Create variables to process the x and y legnths of the triangle's used for calculating vectors
    and create variables to store the new angle and velocity being applied by the moon*/
    double x, y, angle, velocity;

    /*Calculate the force acting on the rocket and add it to the previous force*/
    /*pow runs with compiler and does not play well with variables*/
    /*v = a t(1) and a=f/m*/

    /*Calculate the distance as x and y resultants between the rocket and the moon*/
    x = moon->x - rocket->x;
    y = moon->y - rocket->y;

    /*Calculate the force acting on the rocket, created by the moon using f = (G*m1*m2)/r^2*/
    rocket->f = (6.67408 * pow(10.0, -11.0) * rocket->m * 7.34767309 * pow(10.0, 8.0) / sqrt(x*x+y*y));

    /*Calculate the velocity which needs to be added because of the moon using v = at with t as 1 as one loop is 1 second in game time*/
    velocity = rocket->f / rocket->m;

    /*Detect if the rocket is to the left of the moon*/
    if (moon->x > rocket->x)
    {

        /*Calculate the resultant angle between the rocket and the moon*/
        angle = atan(y/x);

        /*Detect if the rocket is above of the moon*/
        if (rocket->y < moon->y)
        {

            /*Alter the angle acordingly*/
            angle = angle + 3.14159265359;

        }

        /*Detect if the rocket is below of the moon*/
        if (rocket->y > moon->y)
        {

            /*Alter the angle acordingly*/
            angle = 3.14159265359/2 - angle;

        }

    }

    /*Detect if the rocket is to the right of the moon*/
    if (moon->x < rocket->x)
    {

         /*Calculate the resultant angle between the rocket and the moon*/
        angle = atan(x/y);

        /*Detect if the rocket is above of the moon*/
        if (rocket->y < moon->y)
        {

            /*Alter the angle acordingly*/
            angle = 3.14159265359*1.5 - angle;

        }

        /*Detect if the rocket is below of the moon*/
        if (rocket->y > moon->y)
        {

            /*The angle does not need altering, however this is here incase the maths is wrong as the gravity is erratic*/
            angle = angle;

        }

    }

    /*Calculate the resultant vector x/y components and move the rocket accordingly*/
    rocket->x += (cos(angle) * velocity) + (cos(rocket->ar) * rocket->v) * pow(10, -3);
    rocket->y += (sin(angle) * velocity) + (sin(rocket->ar) * rocket->v) * pow(10, -3);

    /*Increase the rockets velocity due to the effect of the moon*/
    rocket->v += velocity;

    /*Calculate and store the rockets ne angle of travel*/
    rocket->ar = (angle + rocket->a) /2;

    /*Return to the play game loop*/
    return;

}

/*Move the rocket for 1 second when it is outside the moon's area of infuence*/
void moveOutsideAoE(struct rocket_struct * rocket)
{

    /*If the problem is split up into a triangle, the hypotonuse represents the resultant movement (rockets velocity).
    Therefore, the other two sides can be used to represent the x and y components of the rockets movement.
    Using simple trig the "legnth" of the other two sides represnts the rockets x and y velocities.
    These are multiplied by 10^-3 to make them KM/S rather than M/S
    This method of execution means that one cycle of the games main while loop is equivilant to 1 second in game time*/

    /*Calculate the rockets movement along the x axis and write it to the rocket struct*/
    rocket->x += cos(rocket->ar) * rocket->v * pow(10, -3);

    /*Calculate the rockets movement along the y axis and write it to the rocket struct*/
    rocket->y += sin(rocket->ar) * rocket->v * pow(10, -3);

    /*Return to the function that called this one*/
    return;

}

/*Runs the game, including mathmatical processing of rocket path*/
void playGame(void)
{
    /*Declare the structure moon and rocket from the global template definition*/
    struct moon_struct moon;
    struct rocket_struct rocket;

    /*Wipe any previous games/the welcome screen off the GFX window*/
    GFX_ClearWindow();

    /*Calculate a new moon position game USES SOME SHITTY POINTER METHOD TO AVOID JUST COMPYING AND NOT RETURNING THE NEW STRUCT ORIG IS EDITED INSTEAD - ALSO HAS ROCKET DEC as struict changes do not show till leaving function */
    calculateMoon(&moon);

    GFX_ClearWindow();
    drawBackground();

    /*Draw the newly calculated game*/
    drawPlanets(&moon);

    /*Set the rockets initial values*/
    rocket.x = 200.0;
    rocket.y = 200.0;
    rocket.m  = 30000;
    rocket.d = 0;
    rocket.v = 3000;
    rocket.a = 20;
    rocket.f =0;
    rocket.d = 0;

    /*Draw the rocket in the starting position*/
    drawRocket(&rocket);

    /*Draw the rocket's control board with the set values stored in struct rocket*/
    drawControlBoard(&rocket);

    /*Write to the screen*/
    GFX_UpdateDisplay();

    /*Set fire to 0, so the loop below will run until this is changed*/
    int fire = 0;

    /*Create an local int variable called keyPressed to store which key the user presses*/
    int keyPressed;

    /*Run the loop while fire is equal to 0*/
    while (!fire)
    {

        /* Wait for an keyboard or mouse event*/
        GFX_WaitForEvent();

        /*Check the event queue to see if the event registered is a key press*/
        if (GFX_IsEventKeyDown())
        {

            /*If the event was a key press get the allegro assigned integer for that key*/
            GFX_GetKeyPress(&keyPressed);

            /*Check if the key pressed was the up arrow*/
            if (keyPressed == ALLEGRO_KEY_UP)
            {

                /*Check if the angle displayed currently is greater than 90 deg*/
                if (rocket.a < 90.0)
                {

                /*Add 5 degrees to the angle*/
                rocket.a += 5;

                }

            }

            /*Check if the key pressed was the down arrow*/
            if (keyPressed == ALLEGRO_KEY_DOWN)
            {

                /*Check if the angle displayed currently is less than -90 deg*/
                if (rocket.a > -90.0)
                {

                    /*Take 5 degrees from the angle*/
                    rocket.a -= 5;

                    }

            }

            /*Check if the key pressed was the enter key*/
            if (keyPressed == ALLEGRO_KEY_ENTER)
            {

                /*Make fire = 1, so the loop ends and the rocket "fires"*/
                fire = 1;

            }

            /*Check if the key pressed was the left arrow*/
            if (keyPressed == ALLEGRO_KEY_LEFT)
            {

                /*Take 100 km/s from the displayed velocity*/
                rocket.v -= 100;

            }

            /*Check if the key pressed was the right arrow*/
            if (keyPressed == ALLEGRO_KEY_RIGHT)
            {

                /*Add 100 km/s to the velocity*/
                rocket.v += 100;

            }

        }

        /*Clear the window to prevent flicker*/
        GFX_ClearWindow();

        /*Draw an entirely new game screen with updated locations*/
        drawBackground();
        drawPlanets(&moon);
        drawRocket(&rocket);
        drawControlBoard(&rocket);

        /*Write changes to the GFX window*/
        GFX_UpdateDisplay();

    }

    /*Check if the users chosen velocity is above the escape velocity*/
    if (rocket.v < 200)
    {

        /*Set the distance travelled to -1 to trigger the excape velocity message*/
        rocket.d = -1;

        /*Run the endgame loop*/
        endGame(&rocket);

    }

    /*Convert the launch angle to radians for processing*/
    rocket.ar  = rocket.a / 180 * 3.14159;

    /*Create variables to store the distance from the moon and mars*/
    double distFromMoon, distFromMars;

    /*While fire = 1 run the loop to fly the rocket*/
    while (fire == 1)
    {

        /*Add 1 to the rockets distance travelled to use as a score*/
        rocket.d += 1;

        /*Use pythag to calculate the distance between the rocket and the moon/mars
        pow(x,y) has not been used as it is calulated when the program is complied, meaning
        the value of it does not change if the variables inside do*/
        distFromMoon = sqrt((moon.x - rocket.x)*(moon.x - rocket.x)+(moon.y - rocket.y)*(moon.y - rocket.y));
        distFromMars = sqrt((1200 - rocket.x)*(1200 - rocket.x)+(640 - rocket.y)*(640 - rocket.y));

        /*Check if the rocket is inside the moons area of gravitational influence (AoE from here on)*/
        if (distFromMoon <= moon.i)
        {

            /*Call the function to move the rocket along its path inside the AoE*/
            moveInsideAoE(&rocket, &moon);

        }

        /*Check if the rocket has hit mars and landed*/
        if (distFromMars <= 75)
        {

            /*Set fire to 0, ending the fire loop*/
            fire = 0;

        }

        /*Check if the rocket has hit the moon*/
        if (distFromMoon <= moon.d/2)
        {

            /*Set the score to 0, as the user did not make it to mars*/
            rocket.d = 0;

            /*Set fire to 0, ending the fire loop*/
            fire = 0;

        }

        /*Check if the rocket has left the screen*/
        if (rocket.x < 0 || rocket.x > 1280 || rocket.y < 0 || rocket.y > 720)
        {

            /*Set the score to 0, as the user did not make it to mars*/
            rocket.d = 0;

            /*Set fire to 0, ending the fire loop*/
            fire = 0;

        }

        /*If the roockets position does not meet any of the above parameters, it needs to be moved normally*/
        else
        {

            /*Move forward under with no influence from the moon*/
            moveOutsideAoE(&rocket);

        }

        /*Clear the window so the old rocket position cannot be seen*/
        GFX_ClearWindow();

        /*Draw an entirely new game screen with updated locations*/
        drawBackground();
        drawPlanets(&moon);
        drawRocket(&rocket);
        drawControlBoard(&rocket);

        /*Write changes to the GFX window*/
        GFX_UpdateDisplay();

    }

    /*Run the endgame function, as the game has ended, passing the rocket struct so a score can be displayed*/
    endGame(&rocket);

    /*Should endGame fail for some reason the program will still return and quit*/
    return;

}

/*Shows the user their score post game and offers replay/quit*/
void endGame(struct rocket_struct * rocket)
{

    /*Post game window wipe*/
    GFX_ClearWindow();

    /*Draw the background*/
    drawBackground();

    /*Create an array to store the score*/
    char text[20];

    /*Convert the score into a string from a double
    and store in the string "text".
    This has to be done as the score is stored as a double and cannot
    be printed to the GFX screen as text.
    The score is the distanced travelled/amount of loops performed*/
    sprintf(text, "%lf", rocket->d);

    /*Check if the user did not aceive escape velocity, checked in playGame()*/
    if (rocket->d == -1)
    {

        /*Notify the user of their mistake*/
        GFX_DrawText(500, 210, "You did not acheive escape velocity");

    }

    /*Run if the user acheived escape velocity*/
    else
    {

        /*Show the user their score*/
        GFX_DrawText(560, 220, "You're score was...");
        GFX_DrawText(590, 230, text);

    }

    /*Draw the replay button at 640,180 details on bitmap drawing can be found in drawPlanets()*/
    BITMAP replayBitmap = GFX_LoadBitmap("Bitmaps/Replay.bmp");
    GFX_DrawBitmap(replayBitmap, 640, 180);
    GFX_FreeBitmap(replayBitmap);

    /*Draw the replay button at 640,380 details on bitmap drawing can be found in drawPlanets()*/
    BITMAP quitBitmap = GFX_LoadBitmap("Bitmaps/Quit.bmp");
    GFX_DrawBitmap(quitBitmap, 640, 380);
    GFX_FreeBitmap(quitBitmap);

    /*Update the display*/
    GFX_UpdateDisplay();

    /*Create local variables to end the users loop when they make a valid choice, x click coordinate and y click coordinate respectively*/
    int choice,x,y;

    /*Set choice to 0 so the loop will run*/
    choice = 0;

    /*Run the following while loop when choice is not equal to 0*/
    while (!choice)
    {

        /*Wait for a mouse/keyboard event to be added to the event queue*/
        GFX_WaitForEvent();

        /*Check if the last event in the queue was a mouse button click, if it was not listen for a new event*/
        if (GFX_IsEventMouseButton())
        {

            /*Get the coordinates of the mouse click as integers stored as x and y*/
            GFX_GetMouseCoordinates(&x, &y);

            /*Check if the mouse click is within the x bounds of the buttons*/
            if (x >= 565 && x <= 715)
            {

                /*Check if the click is within the y bounds of the replay button button*/
                if (y >= 152 && y <= 208)
                {

                /*Replay the game by running the playGame() function*/
                playGame();

                }

                /*Check if the click is within the y bounds of the quit button*/
                else if (y >= 352 && y <= 408)
                {

                    /*Close the window and leave the IF statement tree*/
                    GFX_CloseWindow();

                }

            }

        }

    }

    /*Should the program not choose the replay option, it will run this and end the program (Failsafe close)*/
    return;

}

