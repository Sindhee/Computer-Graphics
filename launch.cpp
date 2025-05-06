#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>

// Function prototypes
//scene 1.
void drawSky();
void drawLand();
void drawSun();
void drawGrass();
void drawRocketAt(int,int);
void drawAstronaut();
void animateAstronaut();
void drawWavingCrowd(int);

//scene 2.
void flyingScene();
void drawFlyingRocket(int);

//scene 3.
void drawSpaceBackground();
void drawSmallRocketAt(int, int, float);
void spaceScene();
void createSpaceBackground();
void drawSpaceScene();

//scene 4.
void drawQuarterSolarSystem();
void drawEarthwithSmallestRocket(int, int, int);
void drawPlanet(int, int, int, int);
void drawPlanetWithRing(int, int, int, int);
void animateSolarSystem();

//scene 5.
void drawStaticEarthScene();
void drawRotatedRocketAt(int, int, float);
void animateOrbitingRocket();

//scene 6.
void drawSpaceAstronaut(int, int, float);
void spaceWalkScene();

//scene 7.
void drawInvertedRocketAt(int, int, float);
void returningToEarthScene();

//scene 8.
void drawReturningRocket(int);
void earthReturnScene();

//scene 9.
void drawClappingCrowd(int);
void drawStaticAstronaut(int, int);
void drawFinalScene();



void *spaceBackground = NULL;  // Global variable to store background
// Global variables for planet angles (in degrees)
float mercuryAngle = 0;
float venusAngle = 0;
float earthAngle = 0;
float marsAngle = 0;
float jupiterAngle = 0;
float saturnAngle = 0;
float uranusAngle = 0;
float neptuneAngle = 0;

// Double the original values
const float mercurySpeed = 0.08f;    // 2x faster
const float venusSpeed = 0.10f;      // 2x faster
const float earthSpeed = 0.04f;      // 2x faster
const float marsSpeed = 0.09f;       // 2x faster
const float jupiterSpeed = 0.06f;    // 2x faster
const float saturnSpeed = 0.019f;    // 2x faster
const float uranusSpeed = 0.04f;     // 2x faster
const float neptuneSpeed = 0.006f;   // 2x faster


float rocketAngle = 0; // Rocket's orbital position around Earth
const float rocketOrbitSpeed = 0.5f; // Adjust for rocket speed

// Global constants (add these at top of file)
const int EARTH_RADIUS = 125;


// Add these global constants
const float ORBIT_ROCKET_SCALE = 0.35f; // 35% of original size
const int ORBIT_RADIUS = EARTH_RADIUS + 80; // Closer orbit



int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    
     
    // Initialize random seed once at program start
    srand(time(NULL));
        
    // Initialize your background once
    createSpaceBackground(); 
    
    // Scene 1: Astronaut and launch
    animateAstronaut();
    
    // Scene 2: Rocket flying upward
    flyingScene();
    
    // Scene 3: Small rocket in space
    spaceScene();
    
    //Scene 4: solar system
    animateSolarSystem();
    
    //Scene 5:Rocket Orbiting Earth
    animateOrbitingRocket();
    
    //Scene 6: Space Walk
    spaceWalkScene();
    
    //Scene 7: Returning from space
    returningToEarthScene();
    
    //Scene 8: Returning to earth's atmosphere
    earthReturnScene();
    
    //Scene 9: MISSION ACCOMPLISHED
    drawFinalScene();
    
    getch();
    
    // Cleanup
    free(spaceBackground);
    
    getch();
    closegraph();
    return 0;
}

//scene 1

//1. bye scene
void drawBackground() {
        drawSky();
    	drawLand();
    	drawSun();
    	drawGrass();
    	drawRocketAt(getmaxx()/2, getmaxy()/2 + 100);
    	
    
}

void drawSky() {
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), getmaxy()/2);
}

void drawLand() {
    // Main ground
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(0, getmaxy()/2, getmaxx(), getmaxy());

    // Terrain contour
    setcolor(DARKGRAY);
    arc(getmaxx()/2, getmaxy()/2, 180, 360, 200);
    
    // Green field
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, getmaxy()/2 + 50, getmaxx(), getmaxy());
}

void drawSun() {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(100, 100, 30, 30);
    
    // Sun rays
    line(100, 50, 100, 150);
    line(50, 100, 150, 100);
    line(75, 75, 125, 125);
    line(75, 125, 125, 75);
}

void drawGrass() {
    // Grass details
    setcolor(GREEN);
    for(int x = 0; x < getmaxx(); x += 20) {
        line(x, getmaxy()/2 + 60, x + 10, getmaxy()/2 + 40);
    }
    
    // Path
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(getmaxx()/2 - 40, getmaxy()/2 + 50, getmaxx()/2 + 40, getmaxy());
}

// Add this function after drawGrass() and before main()
void drawRocketAt(int baseX, int baseY) {
    
    
    // Main rocket body (rectangle)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(baseX - 30, baseY - 200, baseX + 30, baseY);
    
    // Rocket cone (triangle)
    int cone[8] = {baseX - 40, baseY - 200, 
                  baseX, baseY - 250, 
                  baseX + 40, baseY - 200, 
                  baseX - 40, baseY - 200};
    setfillstyle(SOLID_FILL, RED);
    fillpoly(4, cone);
    
     // Inverted trapezium base (small side at bottom)
    int base[8] = {baseX - 30, baseY,        // Top left
                  baseX - 50, baseY + 50,   // Bottom left
                  baseX + 50, baseY + 50,   // Bottom right
                  baseX + 30, baseY};       // Top right
    setfillstyle(SOLID_FILL, RED);
    fillpoly(4, base);
    
    // Wings (triangles)
    setfillstyle(SOLID_FILL, RED);
    // Left wing
    int leftWing[6] = {baseX - 30, baseY - 100,
                      baseX - 80, baseY - 50,
                      baseX - 30, baseY - 50};
    fillpoly(3, leftWing);
    // Right wing
    int rightWing[6] = {baseX + 30, baseY - 100,
                       baseX + 80, baseY - 50,
                       baseX + 30, baseY - 50};
    fillpoly(3, rightWing);
    
    // Indian flag on body
    int flagYstart = baseY - 180;
    // Saffron (BROWN)
    setfillstyle(SOLID_FILL, BROWN);
    bar(baseX - 15, flagYstart, baseX + 15, flagYstart + 20);
    // White
    setfillstyle(SOLID_FILL, WHITE);
    bar(baseX - 15, flagYstart + 20, baseX + 15, flagYstart + 40);
    // Green
    setfillstyle(SOLID_FILL, GREEN);
    bar(baseX - 15, flagYstart + 40, baseX + 15, flagYstart + 60);
    // Ashoka Chakra
    setcolor(BLUE);
    circle(baseX, flagYstart + 30, 8);
    for(int angle = 0; angle < 360; angle += 30) {
        double rad = angle * 3.1416/180;
        line(baseX, flagYstart + 30,
             baseX + 10*cos(rad),
             flagYstart + 30 + 10*sin(rad));
    }
    
    // ISRO text
    // Vertical ISRO text
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(baseX - 8, baseY - 120, (char*)"I");
    outtextxy(baseX - 8, baseY - 100, (char*)"S");
    outtextxy(baseX - 8, baseY - 80, (char*)"R");
    outtextxy(baseX - 8, baseY - 60, (char*)"O");
}

void drawDetailedAstronaut(int x, int y, int frame, bool inRocket) {
    // Colors
    int bodyColor = WHITE;
    int helmetColor = BLUE;
    int visorColor = DARKGRAY;
    int faceColor = WHITE;

    // 1. Enhanced Helmet (dark blue with reflection)
    setfillstyle(SOLID_FILL, helmetColor);
    setcolor(LIGHTGRAY);  // Crucial - sets outline color
    fillellipse(x, y-50, 30, 30);  // Larger helmet
    
    // Helmet reflection effect
    setcolor(LIGHTBLUE);
    arc(x+10, y-60, 30, 150, 15);
    
    // 2. Improved Visor (dark gray with frame)
    setfillstyle(SOLID_FILL, visorColor);
    fillellipse(x, y-45, 20, 12);  // Wider visor
    setcolor(BLACK);
    ellipse(x, y-45, 0, 360, 20, 12);  // Visor outline
    

    // 3. High-Quality Face
    setfillstyle(SOLID_FILL, faceColor);
    fillellipse(x, y-50, 15, 15);  // Face base
    
       // Expressive Eyes
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x-8, y-55, 4, 4);  // Left eye white
    fillellipse(x+8, y-55, 4, 4);  // Right eye white
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x-8, y-55, 2, 2);  // Left pupil
    fillellipse(x+8, y-55, 2, 2);  // Right pupil
    
    // Smiling Mouth
    setcolor(RED);
    for(int r=6; r<=8; r++)  // Draw multiple arcs
    	arc(x, y-47, 240, 300, r);

    // 4. Body (thicker lines)
    setcolor(bodyColor);
    setlinestyle(SOLID_LINE, 0, 3);
    line(x, y-30, x+2, y+20);  // Body line

    // 5. Legs (walking animation)
    line(x, y+20, x-15+10*(frame%3), y+50);  // Left leg 
    line(x, y+20, x+15-10*(frame%3), y+50);  // Right leg

	// Waving arm parameters
    int shoulderX = x;
    int shoulderY = y - 10;
    int upperArmLength = 30;
    int lowerArmLength = 25;
    int handSize = 5;

    // Calculate waving motion (left-to-right)
    float waveAngle = frame * 0.2f;  // Slower wave speed
    int waveOffset = (int)(15 * sin(waveAngle));  // 15px wave width
    
    // Elbow position (fixed bend)
    int elbowX = shoulderX - upperArmLength;
    int elbowY = shoulderY - 10;  // Slight upward bend
    
    // Hand position (waves left-to-right)
    int handX = elbowX + waveOffset;  // Moves horizontally
    int handY = elbowY - lowerArmLength;
    
    // Draw arm segments
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, 3);
    
    // Upper arm (shoulder to elbow)
    line(shoulderX, shoulderY, elbowX, elbowY);
    
    // Lower arm (elbow to hand)
    line(elbowX, elbowY, handX, handY);
    
     // Hand (circle)
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(handX, handY, handSize, handSize);

    // Other arm (static)
    line(shoulderX, shoulderY, shoulderX + 30, shoulderY + 10);
    fillellipse(shoulderX + 30, shoulderY + 10, handSize, handSize);

    // 7. Oxygen tank
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x+25, y, 8, 5);
}

void animateAstronaut() {
    int rocketX = getmaxx()/2;
    int rocketY = getmaxy() - 100;
    
    // Draw background once
    drawBackground();
    
    // Save background where astronaut will be
    void *buffer = malloc(imagesize(0, 0, getmaxx(), getmaxy()));
    getimage(0, 0, getmaxx(), getmaxy(), buffer);
    
   
    // MODIFIED ANIMATION LOOP
    for(int frame=0; frame<240; frame++) {
        // Calculate position
        int astroX = 50 + frame*4;
        int astroY = getmaxy() - 100 + 8*sin(frame*0.3);
        bool inRocket = (astroX > rocketX - 40);
        
        // Restore background
        putimage(0, 0, buffer, COPY_PUT);
        
        // Draw waving crowd (NEW)
        drawWavingCrowd(frame);  // Pass current frame for synchronization
        
        // Draw astronaut
        drawDetailedAstronaut(astroX, astroY, frame, inRocket);
        
        if(astroX > rocketX + 60) break;
        
        delay(100);
        if(kbhit()) break;
    }
    
    free(buffer);
    // Final scene
    cleardevice();
    drawBackground();
    drawWavingCrowd(0);
}

void drawWavingCrowd(int frameCount) {
    int baseY = getmaxy();  // Exact bottom of screen
    int startX = getmaxx() - 200;  // Right side start position
    
    // Draw 7 stick figures in one row
    for(int i = 0; i < 7; i++) {
        int x = startX + i * 30;  // 30px spacing
        
        // Body (sticks right at screen bottom)
        setcolor(BLACK);
        line(x, baseY - 40, x+2, baseY);
        
        // Head
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(x, baseY - 50, 13, 13);
        
        
        // Extremely slow wave parameters - MODIFY THIS SECTION:
        float randomPhase = (rand() % 628) / 100.0f;
        float randomSpeed = 0.01f + (rand() % 3)/100.0f; // 0.01-0.04 (super slow)
        
        // Keep these multipliers small too for slow motion:
        int waveX = x - 20 + (int)(10 * sin(randomPhase + frameCount*randomSpeed)); // Reduced from 15 to 10
        int waveY = baseY - 35 + (int)(3 * sin(randomPhase + frameCount*(randomSpeed+0.02f))); // Reduced from 5 to 3
		
		// Waving arm
        line(x, baseY - 30, waveX, waveY);
        fillellipse(waveX, waveY, 3, 3);
        
        // Static arm
        line(x, baseY - 30, x + 15, baseY - 25);
    }
}

//scene 2

//2. Rocket flying off in the sky
void drawFlyingRocket(int frame) {
    // Sky background
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), getmaxy());

    // Calculate rocket position (moving upward)
    int rocketX = getmaxx()/2;
    int rocketY = getmaxy() - 100 - frame*2; // Moves up 2px per frame

    // Draw smoke effect
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    for(int i=0; i<5; i++) {
        int smokeX = rocketX - 20 + rand()%40;
        int smokeY = rocketY + 50 + frame + rand()%20;
        int smokeSize = 5 + rand()%10;
        fillellipse(smokeX, smokeY, smokeSize, smokeSize);
    }

    // Draw the rocket with all original details
    drawRocketAt(rocketX, rocketY); // Now using your full-featured rocket
}

void flyingScene() {
    for(int frame=0; frame<300; frame++) {
        cleardevice();
        drawFlyingRocket(frame);
        delay(50);
        
        if(kbhit()) break;
        if(getmaxy() - 100 - frame*2 < -200) break; // Wait until rocket leaves screen
    }
}


//scene 3


// 3. Space Scene with Smaller Rocket
void drawSpaceBackground() {
    // Black space
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, getmaxx(), getmaxy());
    
    // Stars
    setcolor(WHITE);
    for(int i=0; i<200; i++) {
        putpixel(rand()%getmaxx(), rand()%getmaxy(), WHITE);
    }
}

void drawSmallRocketAt(int x, int y, float scale = 0.6f) {
    // Scale all dimensions by the scale factor
    int bodyWidth = (int)(30 * scale);
    int bodyHeight = (int)(200 * scale);
    int coneWidth = (int)(40 * scale);
    int coneHeight = (int)(50 * scale);
    
    // Main rocket body
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x - bodyWidth, y - bodyHeight, x + bodyWidth, y);
    
    // Rocket cone
    setfillstyle(SOLID_FILL, RED);
    int cone[8] = {x - coneWidth, y - bodyHeight, 
                  x, y - bodyHeight - coneHeight, 
                  x + coneWidth, y - bodyHeight, 
                  x - coneWidth, y - bodyHeight};
    fillpoly(4, cone);
    
    // Base (inverted trapezium)
    int base[8] = {x - bodyWidth, y,
                  x - bodyWidth - (int)(20*scale), y + (int)(50*scale),
                  x + bodyWidth + (int)(20*scale), y + (int)(50*scale),
                  x + bodyWidth, y};
    setfillstyle(SOLID_FILL, RED);
    fillpoly(4, base);
    
    // Wings
    setfillstyle(SOLID_FILL, RED);
    int wingLength = (int)(50 * scale);
    int leftWing[6] = {x - bodyWidth, y - (int)(100*scale),
                      x - bodyWidth - wingLength, y - (int)(50*scale),
                      x - bodyWidth, y - (int)(50*scale)};
    int rightWing[6] = {x + bodyWidth, y - (int)(100*scale),
                       x + bodyWidth + wingLength, y - (int)(50*scale),
                       x + bodyWidth, y - (int)(50*scale)};
    fillpoly(3, leftWing);
    fillpoly(3, rightWing);
    
    // Indian flag (scaled down)
    int flagHeight = (int)(60 * scale);
    int flagYstart = y - (int)(180 * scale);
    setfillstyle(SOLID_FILL, BROWN);
    bar(x - (int)(15*scale), flagYstart, x + (int)(15*scale), flagYstart + (int)(20*scale));
    setfillstyle(SOLID_FILL, WHITE);
    bar(x - (int)(15*scale), flagYstart + (int)(20*scale), x + (int)(15*scale), flagYstart + (int)(40*scale));
    setfillstyle(SOLID_FILL, GREEN);
    bar(x - (int)(15*scale), flagYstart + (int)(40*scale), x + (int)(15*scale), flagYstart + flagHeight);
    
    // Ashoka Chakra
    setcolor(BLUE);
    circle(x, flagYstart + (int)(30*scale), (int)(8*scale));
    for(int angle = 0; angle < 360; angle += 30) {
        double rad = angle * 3.1416/180;
        line(x, flagYstart + (int)(30*scale),
             x + (int)(10*scale*cos(rad)),
             flagYstart + (int)(30*scale) + (int)(10*scale*sin(rad)));
    }
    
    // ISRO text (scaled down)
    settextstyle(DEFAULT_FONT, HORIZ_DIR, (int)(2*scale));
    setcolor(WHITE);
    outtextxy(x - (int)(8*scale), y - (int)(120*scale), (char*)"I");
    outtextxy(x - (int)(8*scale), y - (int)(100*scale), (char*)"S");
    outtextxy(x - (int)(8*scale), y - (int)(80*scale), (char*)"R");
    outtextxy(x - (int)(8*scale), y - (int)(60*scale), (char*)"O");
}

void spaceScene() {
    int frame = 0;
    const int rocketSpeed = 2; // Pixels per frame
    const int totalRocketHeight = 120; // Your rocket's full height
    
    while(true) {
        cleardevice();
        drawSpaceBackground();
        
        // Calculate rocket position (with horizontal drift)
        int rocketX = getmaxx()/2 + (int)(20 * sin(frame*0.05));
        int rocketY = getmaxy() - frame * rocketSpeed;
        
        // Draw rocket (entire sprite, clipping will handle visibility)
        drawSmallRocketAt(rocketX, rocketY);
        
        // Draw engine glow
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(rocketX, rocketY + (int)(50*0.6), (int)(15*0.6), (int)(25*0.6));
        
        delay(30);
        
        // Exit when rocket completely leaves screen
        if(rocketY < -totalRocketHeight) break;
        if(kbhit()) break;
        
        frame++;
    }
}


//scene 4

//4. solar system scene
void createSpaceBackground() {
    // 1. Draw black background
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, getmaxx(), getmaxy());
    
    // 2. Draw random stars
    setcolor(WHITE);
    for(int i = 0; i < 500; i++) {
        int x = rand() % getmaxx();
        int y = rand() % getmaxy();
        putpixel(x, y, WHITE);
        
        // Add some brighter stars (25% of stars)
        if(i % 4 == 0) {
            putpixel(x+1, y, WHITE);
            putpixel(x, y+1, WHITE);
        }
    }
    
    // 3. Save to buffer
    spaceBackground = malloc(imagesize(0, 0, getmaxx(), getmaxy()));
    getimage(0, 0, getmaxx(), getmaxy(), spaceBackground);
}


void drawSpaceScene() {
    // Always restore background first (flicker-free)
    putimage(0, 0, spaceBackground, COPY_PUT);
}


void drawQuarterSolarSystem() {
    // Use existing space background
    // 1. First draw your existing background
    drawSpaceScene(); // Uses your saved starfield
    //putimage(0, 0, spaceBackground, COPY_PUT);

    
    // Quarter sun - NOW VISIBLE
    int sunRadius = 228;
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    sector(0,0, 270, 180, sunRadius, sunRadius); // Touches (0,0) exactly
    // Draw as a full circle but positioned so only quarter shows
    //fillellipse(sunRadius, sunRadius, sunRadius, sunRadius);
    
      
    // Orbit center is now the sun's center (sunRadius, sunRadius)
    int centerX = sunRadius;
    int centerY = sunRadius;
    int orbitScale = 150;

    // Planets (20% larger than original but with compressed orbits)
    drawPlanet(centerX + orbitScale*0.3*cos(mercuryAngle*3.14/180), 
               centerY + orbitScale*0.2*sin(mercuryAngle*3.14/180),  
               6, BROWN); // Mercury 

    drawPlanet(centerX + orbitScale*0.5*cos(venusAngle*3.14/180),
               centerY + orbitScale*0.35*sin(venusAngle*3.14/180),
               8, YELLOW); // Venus 

    drawEarthwithSmallestRocket(centerX + orbitScale*0.7*cos(earthAngle*3.14/180),
          centerY + orbitScale*0.5*sin(earthAngle*3.14/180),
          9); //earth

    drawPlanet(centerX + orbitScale*cos(marsAngle*3.14/180),
               centerY + orbitScale*0.7*sin(marsAngle*3.14/180),
               5, RED); // Mars 

    drawPlanet(centerX + orbitScale*1.5*cos(jupiterAngle*3.14/180),
               centerY + orbitScale*1.1*sin(jupiterAngle*3.14/180),
               16, LIGHTBLUE); // Jupiter 

    drawPlanetWithRing(centerX + orbitScale*2.0*cos(saturnAngle*3.14/180),
                      centerY + orbitScale*1.5*sin(saturnAngle*3.14/180),
                      14, YELLOW); // Saturn 

    drawPlanet(centerX + orbitScale*2.4*cos(uranusAngle*3.14/180),
               centerY + orbitScale*1.8*sin(uranusAngle*3.14/180),
               12, CYAN); // Uranus 

    drawPlanet(centerX + orbitScale*2.7*cos(neptuneAngle*3.14/180),
               centerY + orbitScale*2.0*sin(neptuneAngle*3.14/180),
               10, BLUE); // Neptune
}

void drawEarthwithSmallestRocket(int x, int y, int size) {
    // Earth's base (blue)
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x, y, size, size);

    // Green land masses
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    
    // Draw continent-like shapes (simplified)
    sector(x - size/3, y - size/4, 30, 180, size/4, size/5);
    sector(x + size/5, y + size/6, 200, 350, size/5, size/6);
    
    // White clouds
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - size/4, y + size/5, size/8, size/8);
    fillellipse(x + size/3, y - size/6, size/6, size/6);
    
    // Tiny orbiting rocket (red triangle)
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, RED);
    
    int rocketDist = size + 10; // Orbit distance from Earth's center
    int rocketX = x + rocketDist * cos(rocketAngle * 3.14/180);
    int rocketY = y + rocketDist * sin(rocketAngle * 3.14/180);
    
    // Draw triangle pointing away from Earth
    int pts[6] = {
        rocketX, rocketY,
        rocketX + 5 * cos((rocketAngle+120)*3.14/180),
        rocketY + 5 * sin((rocketAngle+120)*3.14/180),
        rocketX + 5 * cos((rocketAngle-120)*3.14/180),
        rocketY + 5 * sin((rocketAngle-120)*3.14/180)
    };
    fillpoly(3, pts);
}

void drawPlanet(int x, int y, int size, int color) {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(x, y, size, size);
}

void drawPlanetWithRing(int x, int y, int size, int color) {
    drawPlanet(x, y, size, color);
    setcolor(LIGHTGRAY);
    ellipse(x, y, 0, 360, size+8, size/3); // Horizontal ring
    ellipse(x, y, 0, 360, size+6, size/2); // Thicker part
}

//animate the solar system

void animateSolarSystem() {
	
    clock_t startTime = clock(); // Get initial time
    const double duration = 30.0; // 30 seconds duration
    double elapsedSeconds = 0.0;

    while (elapsedSeconds < duration) {
        cleardevice();
        drawQuarterSolarSystem();
        
        // Update angles (very small increments)
        mercuryAngle += mercurySpeed;
        venusAngle += venusSpeed;
        earthAngle += earthSpeed;
        
        rocketAngle += rocketOrbitSpeed;
        
        marsAngle += marsSpeed;
        jupiterAngle += jupiterSpeed;
        saturnAngle += saturnSpeed;
        uranusAngle += uranusSpeed;
        neptuneAngle += neptuneSpeed;
        
        
        // Calculate elapsed time
        elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        
        
        delay(30); // Control animation speed
    }
}


//scene 5. rocket orbiting earth





void drawStaticEarthScene() {
    // Clear screen and draw space background
    cleardevice();
    drawSpaceScene(); // Your existing function
    
    // Earth parameters (50% smaller radius)
    int centerX = getmaxx()/2;
    int centerY = getmaxy()/2;
    const int EARTH_RADIUS = 125; // Reduced from 250 (50% smaller)
    const int DETAIL_SCALE = 2;    // Keeps internal details original size
    
    // 1. Draw Earth's base (ocean) - scaled down
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, COLOR(30, 70, 200));
    fillellipse(centerX, centerY, EARTH_RADIUS, EARTH_RADIUS);
    
    // 2. Add continent shapes (original size)
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, COLOR(50, 180, 50));
    
    // Scaled continent polygon (70% of original size)
    int continent[8] = {
        centerX - (int)(125 * 0.7), centerY - (int)(62 * 0.7),  // -50% then -30%
        centerX - (int)(83 * 0.7), centerY,
        centerX, centerY + (int)(50 * 0.7),
        centerX + (int)(62 * 0.7), centerY - (int)(41 * 0.7)
    };
    fillpoly(4, continent);
    
    // 3. Add static cloud cover (original size)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(centerX-250/3, centerY+250/5, 25, 15);  // Original coordinates
    fillellipse(centerX+250/4, centerY-250/3, 30, 12);  // Original coordinates

}

void drawRotatedRocketAt(int x, int y, float scale = 0.6f) {
    // Scale all dimensions by the scale factor
    int bodyWidth = (int)(30 * scale);
    int bodyHeight = (int)(200 * scale);
    int coneWidth = (int)(40 * scale);
    int coneHeight = (int)(50 * scale);
    
    // Main rocket body (rotated 90 degrees)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y - bodyWidth, x + bodyHeight, y + bodyWidth);
    
    // Rocket cone (now on the right side)
    setfillstyle(SOLID_FILL, RED);
    int cone[8] = {x + bodyHeight, y - coneWidth,
                  x + bodyHeight + coneHeight, y,
                  x + bodyHeight, y + coneWidth,
                  x + bodyHeight, y - coneWidth};
    fillpoly(4, cone);
    
    // Base (now on the left side)
    int base[8] = {x, y - bodyWidth,
                  x - (int)(50*scale), y - bodyWidth - (int)(20*scale),
                  x - (int)(50*scale), y + bodyWidth + (int)(20*scale),
                  x, y + bodyWidth};
    setfillstyle(SOLID_FILL, RED);
    fillpoly(4, base);
    
    // Wings (now top and bottom)
    setfillstyle(SOLID_FILL, RED);
    int wingLength = (int)(50 * scale);
    int topWing[6] = {x + (int)(100*scale), y - bodyWidth,
                     x + (int)(50*scale), y - bodyWidth - wingLength,
                     x + (int)(50*scale), y - bodyWidth};
    int bottomWing[6] = {x + (int)(100*scale), y + bodyWidth,
                        x + (int)(50*scale), y + bodyWidth + wingLength,
                        x + (int)(50*scale), y + bodyWidth};
    fillpoly(3, topWing);
    fillpoly(3, bottomWing);
    
	// Indian flag (on right side of body)
	int flagWidth = (int)(20 * scale);  // Increased width (was 10)
	int flagHeight = (int)(40 * scale); // Reduced height (was 60)
	// Positioned on right side of body, 10px from cone base
	int flagXstart = x + bodyHeight - (int)(30 * scale); 
	int flagYstart = y - flagHeight/2;  // Vertically centered
	
	// Flag bands (vertical stripes)
	setfillstyle(SOLID_FILL, BROWN); // Saffron (top)
	bar(flagXstart, flagYstart, 
	    flagXstart + flagWidth, flagYstart + flagHeight/3);
	
	setfillstyle(SOLID_FILL, WHITE);  // White (middle)
	bar(flagXstart, flagYstart + flagHeight/3, 
	    flagXstart + flagWidth, flagYstart + 2*flagHeight/3);
	
	setfillstyle(SOLID_FILL, GREEN);  // Green (bottom)
	bar(flagXstart, flagYstart + 2*flagHeight/3, 
	    flagXstart + flagWidth, flagYstart + flagHeight);
	
	// Ashoka Chakra (properly sized)
	setcolor(BLUE);
	circle(flagXstart + flagWidth/2, 
	       flagYstart + flagHeight/2, 
	       (int)(flagWidth/3)); // Proportional to flag width
	
	// ISRO text (centered in body, compact)
	settextstyle(SMALL_FONT, HORIZ_DIR, 5); // Most compact font
	setcolor(WHITE);
	char* isroText = (char*)"ISRO";
	int textWidth = textwidth(isroText);
	int textHeight = textheight(isroText);
	
	// Center calculation using body dimensions
	int textX = x + bodyHeight/2 - textWidth/2;
	int textY = y - textHeight/2; // Perfect vertical center
	
	// Ensure text stays within body width
	if (textWidth > bodyHeight) {
	    settextstyle(SMALL_FONT, HORIZ_DIR, 1);
	    textWidth = textwidth(isroText); // Recalculate with smaller font
	    textX = x + bodyHeight/2 - textWidth/2;
	}

outtextxy(textX, textY, isroText);
}

void animateOrbitingRocket() {
    const int EARTH_RADIUS = 125;
    const int ORBIT_RADIUS = EARTH_RADIUS + 100;
    const int centerX = getmaxx()/2;
    const int centerY = getmaxy()/2;
    const float ROCKET_SCALE = 0.4f;
    const int TOTAL_FRAMES = 360;
    const float ANGLE_INCREMENT = 2 * M_PI / TOTAL_FRAMES;
    
    float angle = 0;
    
    // Create fillsettingstype struct to store original fill settings
    fillsettingstype originalFill;
    
    for (int frame = 0; frame < 3* TOTAL_FRAMES; frame++) {
        int rocketX = centerX + ORBIT_RADIUS * cos(angle);
        int rocketY = centerY + ORBIT_RADIUS * sin(angle);
        
        cleardevice();
        drawStaticEarthScene();
        
        // Save original settings
        int originalColor = getcolor();
        getfillsettings(&originalFill);  // Correct way to get fill settings
        
        // Draw rocket
        drawRotatedRocketAt(rocketX, rocketY, ROCKET_SCALE);
        
        // Restore original settings
        setcolor(originalColor);
        setfillstyle(originalFill.pattern, originalFill.color);
        
        delay(20);
        angle += ANGLE_INCREMENT;
        
        if (kbhit()) break;
    }
}



//scene 6.


//spacewalk
// Helper function for rotation (graphics.h compatible)
void rotatePoint(int cx, int cy, int* x, int* y, float cosa, float sina) {
    int dx = *x - cx;
    int dy = *y - cy;
    *x = cx + dx*cosa - dy*sina;
    *y = cy + dx*sina + dy*cosa;
}

void drawSpaceAstronaut(int x, int y, int frame) {
    // 1. Helmet (static)
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x, y-50, 30, 30);
    
    // Helmet reflection
    setcolor(LIGHTBLUE);
    arc(x+10, y-60, 30, 150, 15);

    // 2. Visor (static)
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillellipse(x, y-45, 20, 12);
    setcolor(BLACK);
    ellipse(x, y-45, 0, 360, 20, 12);

    // 3. Face (static)
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y-50, 15, 15);
    
    // Eyes
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x-8, y-55, 4, 4);
    fillellipse(x+8, y-55, 4, 4);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x-8, y-55, 2, 2);
    fillellipse(x+8, y-55, 2, 2);
    
 	const int DARK_WHITE = 15;  // Light gray (darker than pure white)
 	
    // Classic mouth (as requested)
    setcolor(RED);
    for(int r=6; r<=8; r++)  // Multiple arcs for thickness
        arc(x, y-47, 240, 300, r);

    // 4. Body (static)
    setcolor(DARK_WHITE);
    setlinestyle(SOLID_LINE, 0, 3);
    line(x, y-30, x, y+20);

    // 5. Limbs with subtle movement
    int armSwing = 5 * sin(frame * 0.1f);
    int legBend = 3 * cos(frame * 0.08f);
    
    // Arms
    line(x, y-15, x-20 + armSwing, y-25);
    line(x, y-15, x+20 - armSwing, y-25);
    
    
    // Hands (darkened circles)
    setfillstyle(SOLID_FILL, DARK_WHITE);
    fillellipse(x-20 + armSwing, y-25, 3, 3);
    fillellipse(x+20 - armSwing, y-25, 3, 3);
    
 	// Legs (darkened)
    
    line(x, y+20, x-15 + legBend, y+50);
    line(x, y+20, x+15 - legBend, y+50);

//    // 6. Oxygen tank (static)
//    setcolor(BLUE);
//    setfillstyle(SOLID_FILL, BLUE);
//    fillellipse(x+25, y, 8, 5);
}

void spaceWalkScene() {
    int frame = 0;
    int rocketX = 50, rocketY = getmaxy()/2;
    float rocketScale = 0.7f;
    
    // Astronaut start position (right of rocket)
    float astroX = rocketX + 250;
    float astroY = rocketY;
    const float MAX_DRIFT_X = 230.0f; // Maximum horizontal drift from start
    const float MAX_DRIFT_Y = 150.0f;  // Maximum vertical drift from start
    const int DURATION = 1000;         // ~20 seconds at delay(40)

    // Tether points
    int coneX = rocketX + (int)(200*rocketScale) + 30;
    int coneY = rocketY;

    // Drift pattern parameters
    float driftX = 0, driftY = 0;
    float phase1 = 0, phase2 = M_PI/2; // Different phases for X/Y movement

    for (; frame < DURATION; frame++) {
        cleardevice();
        drawSpaceScene();
        drawRotatedRocketAt(rocketX, rocketY, rocketScale);

        // Calculate smooth drifting pattern (bounded ellipsoid)
        phase1 += 0.015f;
        phase2 += 0.012f;
        
        driftX = MAX_DRIFT_X * sin(phase1); 
        driftY = MAX_DRIFT_Y * sin(phase2);
        
        // Apply drift to astronaut position
        float currentX = rocketX + 250 + driftX;
        float currentY = rocketY + driftY;

        // Wavy tether (with tension physics)
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, 2);
        int waistX = currentX - 15;
        int waistY = currentY + 30;
        
        // Tether reacts to movement speed
        float tension = sqrt(driftX*driftX + driftY*driftY) / 50.0f;
        int midX = (coneX + waistX)/2 + (int)(15 * sin(frame*0.05f))* tension;
        int midY = (coneY + waistY)/2 + (int)(10 * cos(frame*0.07f)) * tension;
        
        line(coneX, coneY, midX, midY);
        line(midX, midY, waistX, waistY);

        // Draw astronaut
        drawSpaceAstronaut((int)currentX, (int)currentY, frame);
        
        delay(40);
    }
}



//scene 7.


void drawInvertedRocketAt(int x, int y, float scale = 0.6f) {
    // Scale all dimensions
    int bodyWidth = (int)(30 * scale);
    int bodyHeight = (int)(200 * scale);
    int coneWidth = (int)(40 * scale);
    int coneHeight = (int)(50 * scale);
    
    // Main rocket body (inverted)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x - bodyWidth, y, x + bodyWidth, y + bodyHeight);
    
    // Rocket base (now at top - inverted)
    setfillstyle(SOLID_FILL, RED);
    int base[8] = {x - bodyWidth, y,
                  x - bodyWidth - (int)(20*scale), y - (int)(50*scale),
                  x + bodyWidth + (int)(20*scale), y - (int)(50*scale),
                  x + bodyWidth, y};
    fillpoly(4, base);
    
    // Engine cone (now at bottom)
    int cone[8] = {x - coneWidth, y + bodyHeight,
                  x, y + bodyHeight + coneHeight,
                  x + coneWidth, y + bodyHeight,
                  x - coneWidth, y + bodyHeight};
    fillpoly(4, cone);
    
    
    
    // Wings (adjusted for inverted position)
    setfillstyle(SOLID_FILL, RED);
    int wingLength = (int)(50 * scale);
    int leftWing[6] = {x - bodyWidth, y + (int)(100*scale),
                      x - bodyWidth - wingLength, y + (int)(50*scale),
                      x - bodyWidth, y + (int)(50*scale)};
    int rightWing[6] = {x + bodyWidth, y + (int)(100*scale),
                       x + bodyWidth + wingLength, y + (int)(50*scale),
                       x + bodyWidth, y + (int)(50*scale)};
    fillpoly(3, leftWing);
    fillpoly(3, rightWing);
    
       
    // Calculate center positions
    int bodyCenterY = y + bodyHeight/2;
    int textCenterX = x - (int)(8*scale);
 
    // ISRO text (centered in body)
    settextstyle(DEFAULT_FONT, HORIZ_DIR, (int)(2*scale));
    setcolor(WHITE);
    outtextxy(textCenterX, bodyCenterY - (int)(60*scale), (char*)"I");
    outtextxy(textCenterX, bodyCenterY - (int)(40*scale), (char*)"S");
    outtextxy(textCenterX, bodyCenterY - (int)(20*scale), (char*)"R");
    outtextxy(textCenterX, bodyCenterY, (char*)"O");
    
    // Indian flag (below ISRO text)
    int flagHeight = (int)(60 * scale);
    int flagYstart = bodyCenterY + (int)(30*scale); // Below text
    setfillstyle(SOLID_FILL, BROWN);
    bar(x - (int)(15*scale), flagYstart, x + (int)(15*scale), flagYstart + (int)(20*scale));
    setfillstyle(SOLID_FILL, WHITE);
    bar(x - (int)(15*scale), flagYstart + (int)(20*scale), x + (int)(15*scale), flagYstart + (int)(40*scale));
    setfillstyle(SOLID_FILL, GREEN);
    bar(x - (int)(15*scale), flagYstart + (int)(40*scale), x + (int)(15*scale), flagYstart + flagHeight);
    
    // Ashoka Chakra
    setcolor(BLUE);
    circle(x, flagYstart + (int)(30*scale), (int)(8*scale));
    for(int angle = 0; angle < 360; angle += 30) {
        double rad = angle * 3.1416/180;
        line(x, flagYstart + (int)(30*scale),
             x + (int)(10*scale*cos(rad)),
             flagYstart + (int)(30*scale) + (int)(10*scale*sin(rad)));
}
}

void returningToEarthScene() {
    int frame = 0;
    const int rocketSpeed = 3;
    const int totalRocketHeight = (int)(200 * 0.6f);
    const float scale = 0.6f;
    
    while(true) {
        cleardevice();
        drawSpaceBackground();
        
        int rocketX = getmaxx()/2 + (int)(30 * sin(frame*0.03));
        int rocketY = frame * rocketSpeed - totalRocketHeight;
        
        drawInvertedRocketAt(rocketX, rocketY);
         
     // Engine flame (half on trapezium, half above)
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        int trapeziumTop = rocketY - (int)(50*scale); // Top of trapezium
        int flameHeight = (int)(40*scale);
        int flameY = trapeziumTop - flameHeight/2; // Center flame on edge
        fillellipse(rocketX, flameY, (int)(20*scale), flameHeight);
        
//        // Flame effect (gradient would be better but using what's available)
//        setcolor(LIGHTRED);
//        setfillstyle(SOLID_FILL, LIGHTRED);
//        fillellipse(rocketX, flameY - flameHeight/4, (int)(15*scale), flameHeight/2);
        
//        // Atmospheric effect
//        if(rocketY > getmaxy() - 200) {
//            setcolor(LIGHTRED);
//            setfillstyle(SOLID_FILL, LIGHTRED);
//            sector(rocketX, getmaxy(), 0, 180, 
//                 (getmaxy() - rocketY)*2, (getmaxy() - rocketY)/3);
//        }
        
        delay(30);
        
        if(rocketY > getmaxy() + totalRocketHeight) break;
        if(kbhit()) break;
        
        frame++;
    }
}


//scene 8


//Rocket returning in earth's atmosphere
void drawReturningRocket(int frame) {
    // Earth atmosphere (using available colors)
//    setfillstyle(SOLID_FILL, LIGHTBLUE);
//    bar(0, 0, getmaxx(), getmaxy()/3);         // Upper atmosphere
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), getmaxy()); // Lower atmosphere

//    // Draw earth surface (bottom of screen)
//    setfillstyle(SOLID_FILL, GREEN);
//    bar(0, getmaxy()-50, getmaxx(), getmaxy());

    // Calculate rocket position (descending)
    int rocketX = getmaxx()/2 + (int)(20 * sin(frame*0.05)); // Slight sway
    int rocketY = 100 + frame*3; // Moves down 3px per frame

    // Draw smoke effect (above trapezium)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    for(int i=0; i<8; i++) {
        int smokeX = rocketX - 30 + rand()%60;
        int smokeY = rocketY - 80 - frame/2 + rand()%40;
        int smokeSize = 8 + rand()%15;
        fillellipse(smokeX, smokeY, smokeSize, smokeSize);
    }

    // Draw inverted rocket
    drawInvertedRocketAt(rocketX, rocketY);

//    // Retro rockets flame (from trapezium)
//    setcolor(YELLOW);
//    setfillstyle(SOLID_FILL, YELLOW);
//    int flameY = rocketY - (int)(50*0.6); // Top of trapezium
//    fillellipse(rocketX, flameY - 20, 25, 40); // Half above trapezium

//    // Add clouds in lower atmosphere
//    if(frame > 150) { // Only when rocket is lower
//        setcolor(WHITE);
//        setfillstyle(SOLID_FILL, WHITE);
//        for(int i=0; i<3; i++) {
//            int cloudX = rand()%getmaxx();
//            int cloudY = getmaxy()-100 + rand()%50;
//            fillellipse(cloudX, cloudY, 30, 15);
//        }
//    }
}

void earthReturnScene() {
    for(int frame=0; frame<250; frame++) {
        cleardevice();
        drawReturningRocket(frame);
        
        // Add stars in upper atmosphere (using available colors)
        if(frame < 100) {
            setcolor(WHITE);
            for(int i=0; i<5; i++) {
                putpixel(rand()%getmaxx(), rand()%(getmaxy()/3), WHITE);
            }
        }
        
        delay(40);
        
        if(kbhit()) break;
        if(100 + frame*3 > getmaxy() + 200) break;
    }
}


//scene 9.

//void *background = NULL;
//mission accomplished
void drawFinalScene() {
    // 1. First draw everything to an off-screen buffer
    void *buffer = malloc(imagesize(0, 0, getmaxx(), getmaxy()));
    setactivepage(1); // Draw to hidden page
    
    // Draw static elements using your existing function
    drawBackground(); 
    int rocketX = getmaxx()/2;
    int rocketY = getmaxy()/2 + 100;
    //drawRocketAt(rocketX, rocketY);
    drawStaticAstronaut(rocketX - 100, rocketY + 50);
    
    // Save this static background
    getimage(0, 0, getmaxx(), getmaxy(), buffer);
    
    // 2. Animation loop using page flipping
    setvisualpage(0);
    for(int frame = 0; frame < 150; frame++) {
        setactivepage(frame % 2); // Alternate between pages 0 and 1
        
        // Restore static background
        putimage(0, 0, buffer, COPY_PUT);
        
        // Draw animated elements
        drawClappingCrowd(frame);
        
        if(frame > 100) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setcolor(WHITE);
            setbkcolor(BLUE);
            outtextxy(getmaxx()/2 - 150, 50, (char*)"MISSION ACCOMPLISHED!");
        }
        
        setvisualpage(frame % 2); // Show the page we just drew
        delay(40);
        if(kbhit()) break;
    }
    
    // 3. Clean up
    free(buffer);
    setvisualpage(0);
    setactivepage(0);
}

void drawStaticAstronaut(int x, int y) {
    // Helmet
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x, y-50, 30, 30);
    setcolor(LIGHTBLUE);
    arc(x+10, y-60, 30, 150, 15);
    
    // Visor
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillellipse(x, y-45, 20, 12);
    setcolor(BLACK);
    ellipse(x, y-45, 0, 360, 20, 12);
    
    // Face
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y-50, 15, 15);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x-8, y-55, 4, 4);
    fillellipse(x+8, y-55, 4, 4);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x-8, y-55, 2, 2);
    fillellipse(x+8, y-55, 2, 2);
    
    // Smile
    setcolor(RED);
    for(int r=6; r<=8; r++)
        arc(x, y-47, 240, 300, r);
    
    // Body
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, 3);
    line(x, y-30, x, y+20); // Body
    
    // Arms (static)
    line(x, y-10, x-25, y-20); // Left arm
    line(x, y-10, x+25, y-20); // Right arm
    
    // Legs (static standing position)
    line(x, y+20, x-15, y+50); // Left leg
    line(x, y+20, x+15, y+50); // Right leg
    
}

void drawClappingCrowd(int frame) {
    int baseY = getmaxy(); // Bottom of screen
    int startX = 0; // Left side start position
    
    // Draw 10 stick figures
    for(int i = 0; i < 10; i++) {
        int x = startX + i * 70; // Wider spacing
        
        // Body (static)
        setcolor(BLACK);
        line(x, baseY - 40, x, baseY);
        
        // Head (static)
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(x, baseY - 50, 10, 10);
        
        // Clapping animation
        float clapPhase = frame * 0.2f + (i * 0.3f); // Offset each person
        int clapPos = (int)(10 * sin(clapPhase)); // Hand position (-10 to 10)
        
        // Hands apart position (when sin > 0)
        if(clapPos > 0) {
            // Left hand
            line(x, baseY - 30, x - 20 - clapPos, baseY - 30);
            fillellipse(x - 20 - clapPos, baseY - 30, 3, 3);
            // Right hand
            line(x, baseY - 30, x + 20 + clapPos, baseY - 30);
            fillellipse(x + 20 + clapPos, baseY - 30, 3, 3);
        }
        // Hands together position (when sin <= 0)
        else {
            // Both hands meet at center
            line(x, baseY - 30, x - 10, baseY - 30);
            fillellipse(x - 10, baseY - 30, 3, 3);
            line(x, baseY - 30, x + 10, baseY - 30);
            fillellipse(x + 10, baseY - 30, 3, 3);
        }
        
//        // Cheering effect when hands meet
//        if(clapPos <= 0 && frame % 10 < 5) {
//            setcolor(YELLOW);
//            fillellipse(x, baseY - 60, 5, 5); // "Sparkle" effect
//        }
    }
}
