/*
 * Student Information
 *
 * Name: MD AL AMIN
 * Student Id: 2022521460126
 * Major:software engineering
 * Year: 2024
 *
 * asg2.c
 *
 * Program skeleton of  Assignment 2
 * Virtual Solar System
 *
 */


#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bitmap.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SOLAR_YEAR 360.0f    /* Rotation period of the entire solar system (arbitrary unit) */
#define EARTH_YEAR 4320.0f   /* Earth's revolution period around the Sun */
#define VENUS_YEAR 2880.0f   /* Venus's revolution period around the Sun */
#define MARS_YEAR 8640.0f    /* Mars's revolution period around the Sun */
#define MOON_YEAR 360.0f     /* Moon's revolution period around Earth */
#define MERCURY_YEAR 1440.0f /* Mercury's revolution period around the Sun */
#define JUPITER_YEAR 10800.0f /* Jupiter's revolution period around the Sun */
#define SATURN_YEAR 21600.0f /* Saturn's revolution period around the Sun */
#define URANUS_YEAR 43200.0f /* Uranus's revolution period around the Sun */
#define NEPTUNE_YEAR 86400.0f /* Neptune's revolution period around the Sun */
#define PLUTO_YEAR 129600.0f /* Pluto's revolution period around the Sun */

// Self-rotation periods (in days)
// These represent how long each celestial object takes to rotate once on its axis
#define EARTH_DAY 11.0f      /* Earth's self-rotation period */
#define VENUS_DAY 66.0f      /* Venus's self-rotation period */
#define MARS_DAY 11.0f       /* Mars's self-rotation period */
#define MOON_DAY 27.3f       /* Moon's self-rotation period */
#define MERCURY_DAY 58.6f    /* Mercury's self-rotation period */
#define JUPITER_DAY 9.9f     /* Jupiter's self-rotation period */
#define SATURN_DAY 10.7f     /* Saturn's self-rotation period */
#define URANUS_DAY 17.2f     /* Uranus's self-rotation period */
#define NEPTUNE_DAY 16.1f    /* Neptune's self-rotation period */
#define PLUTO_DAY 153.3f     /* Pluto's self-rotation period */

// Radii of celestial objects (in arbitrary units, proportional to Sun's radius)
#define SUN_RADIUS 0.10f     /* Radius of the Sun */
#define VENUS_RADIUS 0.25f   /* Radius of Venus */
#define EARTH_RADIUS 0.25f   /* Radius of Earth */
#define MOON_RADIUS 0.08f    /* Radius of the Moon */
#define MARS_RADIUS 0.15f    /* Radius of Mars */
#define MERCURY_RADIUS 0.15f /* Radius of Mercury */
#define JUPITER_RADIUS 0.45f /* Radius of Jupiter */
#define SATURN_RADIUS 0.40f  /* Radius of Saturn */
#define URANUS_RADIUS 0.30f  /* Radius of Uranus */
#define NEPTUNE_RADIUS 0.28f /* Radius of Neptune */
#define PLUTO_RADIUS 0.10f   /* Radius of Pluto */

// Orbital distances (in arbitrary units)
// These represent the distance of the celestial body from the Sun (or planet, for moons)
#define VENUS_ORBIT 0.75f    /* Venus's orbital distance from the Sun */
#define EARTH_ORBIT 1.75f    /* Earth's orbital distance from the Sun */
#define MOON_ORBIT 0.35f     /* Moon's orbital distance from Earth */
#define MARS_ORBIT 2.50f     /* Mars's orbital distance from the Sun */
#define MERCURY_ORBIT 0.50f  /* Mercury's orbital distance from the Sun */
#define JUPITER_ORBIT 3.50f  /* Jupiter's orbital distance from the Sun */
#define SATURN_ORBIT 4.50f   /* Saturn's orbital distance from the Sun */
#define URANUS_ORBIT 5.50f   /* Uranus's orbital distance from the Sun */
#define NEPTUNE_ORBIT 6.50f  /* Neptune's orbital distance from the Sun */
#define PLUTO_ORBIT 7.50f    /* Pluto's orbital distance from the Sun */

// Tilt of celestial objects (in degrees)
// These represent the axial tilt of each celestial object relative to its orbit
#define MERCURY_TILT 0.034f  /* Mercury's axial tilt */
#define VENUS_TILT 177.3f    /* Venus's axial tilt (almost flipped) */
#define EARTH_TILT 23.44f    /* Earth's axial tilt */
#define MARS_TILT 25.19f     /* Mars's axial tilt */
#define JUPITER_TILT 3.13f   /* Jupiter's axial tilt */
#define SATURN_TILT 26.73f   /* Saturn's axial tilt */
#define URANUS_TILT 97.77f   /* Uranus's axial tilt (almost perpendicular) */
#define NEPTUNE_TILT 28.32f  /* Neptune's axial tilt */
#define PLUTO_TILT 122.53f   /* Pluto's axial tilt */

#define MAX_STAR 10000
#define TRUE 1
#define FALSE 0

float cameraDistance = 6.0f;
int lastX = 0, lastY = 0;
bool mouseDown = false;
float timeMultiplier = 1.0f; // Default time multiplier (normal speed)

bool globalRotationEnabled = true;
bool animationEnabled = true;
float globalRotationAngle = 0.0f;

float venusAngle = 0.0f;
float earthAngle = 0.0f;
float moonAngle = 0.0f;
float marsAngle = 0.0f;
float mercuryAngle = 0.0f;
float jupiterAngle = 0.0f;
float saturnAngle = 0.0f;
float uranusAngle = 0.0f;
float neptuneAngle = 0.0f;
float plutoAngle = 0.0f;


float venusRotationAngle = 0.0f;
float earthRotationAngle = 0.0f;
float moonRotationAngle = 0.0f;
float marsRotationAngle = 0.0f;
float mercuryRotationAngle = 0.0f;
float jupiterRotationAngle = 0.0f;
float saturnRotationAngle = 0.0f;
float uranusRotationAngle = 0.0f;
float neptuneRotationAngle = 0.0f;
float plutoRotationAngle = 0.0f;

float cameraX = 0.0f;
float cameraY = 5.0f;
float cameraZ = 10.0f;
float centerX = 0.0f;
float centerY = 0.0f;
float centerZ = 0.0f;

// Add at the top with other global variables
float defaultCameraX = 3.0f;
float defaultCameraY = 5.0f;
float defaultCameraZ = 6.0f;

float angledCameraX = 5.0f;
float angledCameraY = 10.0f;
float angledCameraZ = 10.0f;

bool isAngledView = true; // Start with angled view
bool isInResetState = false;  // Add with other global variables

GLfloat sunEmissive[] = { 1.0f, 1.0f, 0.0f, 1.0f }; // Yellow emissive color

GLuint venusTexture, earthTexture, moonTexture, marsTexture, mercuryTexture, jupiterTexture, saturnTexture, uranusTexture, neptuneTexture, plutoTexture; // Declare texture IDs
typedef struct tmp_star {
    float pos[3];
    float col[4];
} Star;

Star star[MAX_STAR];

float winwidth, winheight;
int _ScreenMode = 3;

void checkOpenGLError(const char* context) {
    GLenum errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error in %s: %d\n", context, errorCode);
    }
}

float satelliteAngle = 0.0f;  // Angle of the satellite around Earth
#define SATELLITE_ORBIT 0.30f  // Orbit radius of the satellite
#define SATELLITE_SPEED 15.0f  // Orbital speed of the satellite
#define SATELLITE_RADIUS 0.05f // Size of the satellite
// Update the scene's animations based on the time elapsed
void updateSatellite(float deltaTime);
void renderSatellite() {
    glPushMatrix();
    glRotatef(satelliteAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(2.0f, 0.0f, 0.0f);
    glutSolidSphere(0.1f, 20, 20);
    glPopMatrix();
}


void updateSatellite(float deltaTime) {
    satelliteAngle = fmod(satelliteAngle + deltaTime * SATELLITE_SPEED, 360.0f);


}
float cometAngle = 0.0f;
#define COMET_SPEED 5.0f
#define COMET_RADIUS 0.08f
#define COMET_ORBIT 5.0f

void drawComet() {
    glPushMatrix();
    glRotatef(cometAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(COMET_ORBIT, 0.0f, 0.0f);

    // Draw the comet
    glColor3f(1.0f, 0.8f, 0.2f); // Comet color
    glutSolidSphere(COMET_RADIUS, 10, 10);

    // Draw the comet's trail
    glBegin(GL_LINES);
    for (float i = 0.0f; i < 10.0f; i += 0.5f) {
        glColor4f(1.0f, 0.5f, 0.0f, 1.0f - i / 10.0f); // Gradual fade
        glVertex3f(COMET_ORBIT - i, 0.0f, 0.0f);
        glVertex3f(COMET_ORBIT - i - 0.2f, 0.0f, 0.0f);
    }
    glEnd();
    glPopMatrix();
}

void updateComet(float deltaTime) {
    cometAngle = fmod(cometAngle + deltaTime * COMET_SPEED, 360.0f);
}

// Function to load a BMP file and capture its data
GLubyte* TextureLoadBitmap(const char* filename, int* w, int* h) {
    FILE* fp;
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;

    // Open the BMP file
    if (fopen_s(&fp, filename, "rb") != 0) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return NULL;
    }

    // Read the BMP file header
    if (fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
        fprintf(stderr, "Error reading file header\n");
        fclose(fp);
        return NULL;
    }

    // Check if the file is a valid BMP ('BM' signature)
    if (bfh.bfType != 0x4D42) {
        fprintf(stderr, "File is not a BMP: %s\n", filename);
        fclose(fp);
        return NULL;
    }

    // Read the BMP info header
    if (fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        fprintf(stderr, "Error reading info header\n");
        fclose(fp);
        return NULL;
    }

    // Check if the BMP is 24-bit (supported format)
    if (bih.biBitCount != 24) {
        fprintf(stderr, "Only 24-bit BMPs are supported: %s\n", filename);
        fclose(fp);
        return NULL;
    }

    // Calculate row size, accounting for padding to align rows to 4 bytes
    int rowSize = ((bih.biWidth * 3 + 3) & ~3);
    int imageSize = rowSize * bih.biHeight;

    // Allocate memory for the BMP image data
    GLubyte* imageData = (GLubyte*)malloc(imageSize);
    if (imageData == NULL) {
        fprintf(stderr, "Failed to allocate memory for image data\n");
        fclose(fp);
        return NULL;
    }

    // Move file pointer to the start of image data
    fseek(fp, bfh.bfOffBits, SEEK_SET);

    // Read the image data into memory
    if (fread(imageData, 1, imageSize, fp) != imageSize) {
        fprintf(stderr, "Error reading image data\n");
        free(imageData);
        fclose(fp);
        return NULL;
    }

    // Store image dimensions
    *w = bih.biWidth;
    *h = bih.biHeight;

    // Close the file and return the loaded image data
    fclose(fp);
    return imageData;
}

// Function to load a texture from a BMP file and return its OpenGL texture ID
GLuint LoadTexture(const char* filename) {
    int width, height;
    GLuint textureID = 0;

    // Load the BMP image data
    GLubyte* imageData = TextureLoadBitmap(filename, &width, &height);
    if (imageData == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", filename);
        return 0;
    }

    // Debug log for successful loading
    fprintf(stderr, "Loaded image %s: width=%d, height=%d\n", filename, width, height);

    // Generate a unique OpenGL texture ID
    glGenTextures(1, &textureID);
    if (textureID == 0) {
        fprintf(stderr, "Failed to generate texture ID for %s\n", filename);
        free(imageData);
        return 0;
    }

    // Bind the texture to configure it
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkOpenGLError("After binding texture");

    // Set texture parameters for filtering and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Smooth scaling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Smooth scaling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // Repeat vertically
    checkOpenGLError("After setting texture parameters");

    // Allocate memory to convert BMP from BGR to RGB
    GLubyte* convertedData = (GLubyte*)malloc(width * height * 3);
    if (convertedData == NULL) {
        fprintf(stderr, "Failed to allocate memory for converted image data\n");
        free(imageData);
        glDeleteTextures(1, &textureID);
        return 0;
    }

    // Convert BMP color format from BGR to RGB
    for (int i = 0; i < width * height; i++) {
        int srcIdx = i * 3;
        int destIdx = i * 3;
        convertedData[destIdx] = imageData[srcIdx + 2];     // R
        convertedData[destIdx + 1] = imageData[srcIdx + 1]; // G
        convertedData[destIdx + 2] = imageData[srcIdx];     // B
    }

    // Load the texture into OpenGL
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Ensure alignment is 1 byte
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, convertedData);

    // Check for OpenGL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        fprintf(stderr, "Error loading texture %s: %d\n", filename, err);
        free(imageData);
        free(convertedData);
        glDeleteTextures(1, &textureID);
        return 0;
    }

    // Clean up temporary buffers
    free(imageData);
    free(convertedData);

    return textureID;
}

void updateScene(float deltaTime) {
    // Scale deltaTime by the global time multiplier
    deltaTime *= timeMultiplier;

    if (animationEnabled) {
        // Update angles for planets and moons
        mercuryAngle = fmod(mercuryAngle + deltaTime * 3.15f, 360.0f); // Mercury orbital speed
        venusAngle = fmod(venusAngle + deltaTime * 1.62f, 360.0f);     // Venus orbital speed
        earthAngle = fmod(earthAngle + deltaTime, 360.0f);             // Earth orbital speed
        moonAngle = fmod(moonAngle + deltaTime * 11.0f, 360.0f);       // Moon orbital speed



        // Update rotation angles
        mercuryRotationAngle = fmod(mercuryRotationAngle + deltaTime * 5.0f, 360.0f); // Mercury rotation
        earthRotationAngle = fmod(earthRotationAngle + deltaTime * 14.0f, 360.0f);   // Earth rotation
        jupiterRotationAngle = fmod(jupiterRotationAngle + deltaTime * 2.5f, 360.0f); // Jupiter rotation

        // Update global rotation if enabled
        if (globalRotationEnabled) {
            globalRotationAngle = fmod(globalRotationAngle + deltaTime * 5.0f, 360.0f); // Global rotation
        }
    }

    // Request a redraw of the scene
    glutPostRedisplay();
}

// Apply axial tilt to a planet
void applyPlanetTilt(float angle) {
    glRotatef(angle, 1.0f, 0.0f, 0.0f); // Rotate the planet along the X-axis to simulate tilt
}

void reset() {
    // Reset all orbital angles
    mercuryAngle = venusAngle = earthAngle = moonAngle = marsAngle = 0.0f;
    jupiterAngle = saturnAngle = uranusAngle = neptuneAngle = plutoAngle = 0.0f;

    // Reset all rotation angles
    mercuryRotationAngle = venusRotationAngle = earthRotationAngle = moonRotationAngle = 0.0f;
    marsRotationAngle = jupiterRotationAngle = saturnRotationAngle = 0.0f;
    uranusRotationAngle = neptuneRotationAngle = plutoRotationAngle = 0.0f;

    // Reset global rotation
    globalRotationAngle = 0.0f;

    // Reset camera position to defaults
    cameraX = defaultCameraX;
    cameraY = defaultCameraY;
    cameraZ = defaultCameraZ;

    // Reset camera target to the origin
    centerX = centerY = centerZ = 0.0f;

    // Request an immediate redraw of the scene
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '=':  // Zoom in
        cameraX *= 0.9f;
        cameraY *= 0.9f;
        cameraZ *= 0.9f;
        break;
    case '-':  // Zoom out
        cameraX *= 1.1f;
        cameraY *= 1.1f;
        cameraZ *= 1.1f;
        break;
    case 'w':  // Tilt up
        cameraY += 0.5f;
        break;
    case 's':  // Tilt down
        cameraY -= 0.5f;
        break;
    case 'a':  // Rotate left
        cameraX -= 0.5f;
        break;
    case 'd':  // Rotate right
        cameraX += 0.5f;
        break;
    case '+':  // Increase time multiplier (speed up)
        timeMultiplier *= 1.1f;
        fprintf(stdout, "Time multiplier increased: %.2fx\n", timeMultiplier);
        break;
    case '_':  // Decrease time multiplier (slow down)
        timeMultiplier /= 1.1f;
        fprintf(stdout, "Time multiplier decreased: %.2fx\n", timeMultiplier);
        break;
    case 'g':  // Toggle global rotation
    case 'G':
        globalRotationEnabled = !globalRotationEnabled;
        fprintf(stdout, "Global rotation %s.\n", globalRotationEnabled ? "enabled" : "disabled");
        break;
    case 't':  // Toggle animation
    case 'T':
        animationEnabled = !animationEnabled;
        fprintf(stdout, "Animation %s.\n", animationEnabled ? "enabled" : "disabled");
        break;
    case 'r':  // Reset the scene
    case 'R':
        reset();
        fprintf(stdout, "Scene reset.\n");
        break;
    default:
        fprintf(stdout, "Key '%c' not bound to any action.\n", key);
        break;
    }

    glutPostRedisplay(); // Request a redraw of the scene
}


void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = true;
            lastX = x;
            lastY = y;
        } else {
            mouseDown = false;
        }
    }
}

// Enhanced mouse control function
void motion(int x, int y) {
    if (mouseDown) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // Rotate with left mouse button
            globalRotationAngle += (x - lastX) * 0.5f;
            cameraY += (y - lastY) * 0.05f;
        }
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {  // Zoom with right mouse button
            float zoomFactor = (y - lastY) * 0.01f;
            cameraX *= (1.0f - zoomFactor);
            cameraY *= (1.0f - zoomFactor);
            cameraZ *= (1.0f - zoomFactor);
        }

        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

void Special(int key, int x, int y) {
    // Implement camera controls here (optional)
    switch (key) {
    case GLUT_KEY_UP:
        cameraY += 0.5f; // Move camera up
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 0.5f; // Move camera down
        break;
    case GLUT_KEY_LEFT:
        cameraX -= 0.5f; // Move camera left
        break;
    case GLUT_KEY_RIGHT:
        cameraX += 0.5f; // Move camera right
        break;
    }
    glutPostRedisplay();
}



void reshape(int w, int h) {
    winwidth = (GLfloat)w;
    winheight = (GLfloat)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}


void drawTexturedSphere(GLdouble radius, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, slices, stacks);
    gluDeleteQuadric(quadric);
}



void drawSatellite() {
    glPushMatrix();
    glRotatef(satelliteAngle, 0.0f, 1.0f, 0.0f); // Rotate along Earth's orbit
    glTranslatef(SATELLITE_ORBIT, 0.0f, 0.0f);  // Translate to orbit radius
    glColor3f(0.8f, 0.8f, 0.8f);                // Color of the satellite
    glutSolidSphere(SATELLITE_RADIUS, 10, 10);  // Draw the satellite
    glPopMatrix();
}



void display(void) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position
    gluLookAt(cameraX, cameraY, cameraZ,  // Camera position
        centerX, centerY, centerZ,  // Look-at point
        0.0f, 1.0f, 0.0f);          // Up vector


    if (globalRotationEnabled) {
        globalRotationAngle = fmod(globalRotationAngle, 360.0f); // Keep angle within 0 to 360 degrees
        glRotatef(globalRotationAngle, 0.0f, 1.0f, 0.0f);
    }

    // Set up lighting (Sun as light source)
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Sun position
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

     // Draw the Sun
    glPushMatrix();
        GLfloat sunEmissive[] = { 1.0f, 1.0f, 0.0f, 1.0f }; // Emission for Sun
        glMaterialfv(GL_FRONT, GL_EMISSION, sunEmissive);
        glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for the Sun
        glutSolidSphere(SUN_RADIUS, 50, 50); // Higher detail for Sun
    glPopMatrix();

    GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    // Draw Mercury
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(MERCURY_TILT, 0.0f, 0.0f, 1.0f);
    }
    glRotatef(mercuryAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(MERCURY_ORBIT, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(mercuryRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mercuryTexture);
    drawTexturedSphere(MERCURY_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Venus
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(VENUS_TILT, 0.0f, 0.0f, 1.0f);
    }
    glTranslatef(VENUS_ORBIT * cos(venusAngle), 0.0f, VENUS_ORBIT * sin(venusAngle));
    glRotatef(venusRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, venusTexture);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  // Reset color to white for proper texture
    drawTexturedSphere(VENUS_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Earth (similar to Venus)
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(EARTH_TILT, 0.0f, 0.0f, 1.0f);
    }
    glTranslatef(EARTH_ORBIT * cos(earthAngle), 0.0f, EARTH_ORBIT * sin(earthAngle));
    glRotatef(earthRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, earthTexture);  // Bind Earth texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Reset color to white for proper texture
    drawTexturedSphere(EARTH_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Moon (similar to Earth, but with its own texture)
    glPushMatrix();
    glTranslatef(EARTH_ORBIT * cos(earthAngle) + MOON_ORBIT * cos(moonAngle), 0.0f, EARTH_ORBIT * sin(earthAngle) + MOON_ORBIT * sin(moonAngle));
    glRotatef(moonRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, moonTexture);  // Bind Moon texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Reset color to white for proper texture
    drawTexturedSphere(MOON_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Mars
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(MARS_TILT, 0.0f, 0.0f, 1.0f);
    }
    glTranslatef(MARS_ORBIT * cos(marsAngle), 0.0f, MARS_ORBIT * sin(marsAngle));
    glRotatef(marsRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, marsTexture);  // Bind Mars texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Reset color to white for proper texture
    drawTexturedSphere(MARS_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Jupiter
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(JUPITER_TILT, 0.0f, 0.0f, 1.0f);
    }
    glRotatef(jupiterAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(JUPITER_ORBIT, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(jupiterRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, jupiterTexture);
    drawTexturedSphere(JUPITER_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();

    // Draw Saturn
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(SATURN_TILT, 0.0f, 0.0f, 1.0f);
    }
    glRotatef(saturnAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(SATURN_ORBIT, 0.0f, 0.0f);
    glRotatef(saturnRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, saturnTexture);
    drawTexturedSphere(SATURN_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Uranus
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(URANUS_TILT, 0.0f, 0.0f, 1.0f);
    }
    glRotatef(uranusAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(URANUS_ORBIT, 0.0f, 0.0f);
    glRotatef(uranusRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, uranusTexture);
    drawTexturedSphere(URANUS_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Draw Neptune
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(NEPTUNE_TILT, 0.0f, 0.0f, 1.0f);
    }
    glRotatef(neptuneAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(NEPTUNE_ORBIT, 0.0f, 0.0f);
    glRotatef(neptuneRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, neptuneTexture);
    drawTexturedSphere(NEPTUNE_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    // Draw Pluto
    glPushMatrix();
    if (!isInResetState) {
        glRotatef(PLUTO_TILT, 0.0f, 0.0f, 1.0f);
    }
    glRotatef(plutoAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(PLUTO_ORBIT, 0.0f, 0.0f);
    glRotatef(plutoRotationAngle, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, plutoTexture);
    drawTexturedSphere(PLUTO_RADIUS, 30, 30);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    // Draw stars in the background
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);  // White stars
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_STAR; i++) {
        glVertex3f(star[i].pos[0], star[i].pos[1], star[i].pos[2]);  // Set the star position
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}




void init() {
    //initializing opengl settings
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Black background
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Texture mapping settings
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // Load textures for planets
venusTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/venus.bmp");
earthTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/earth.bmp");
moonTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/moon.bmp");
marsTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/mars.bmp");
mercuryTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/mercury.bmp");

if (!mercuryTexture) {
    fprintf(stderr, "Failed to load Mercury texture\n");
    glColor3f(0.7f, 0.7f, 0.7f);  // Grey color as fall-back
}

jupiterTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/jupiter.bmp");
saturnTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/saturn.bmp");
uranusTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/uranus.bmp");
neptuneTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/neptune.bmp");
plutoTexture = LoadTexture("C:/Users/Alamin/Desktop/graphics final/pro/u/pluto.bmp");

if (!mercuryTexture || !venusTexture || !earthTexture || !moonTexture ||
    !marsTexture || !jupiterTexture || !saturnTexture || !uranusTexture ||
    !neptuneTexture || !plutoTexture) {
    fprintf(stderr, "Error loading one or more textures\n");
    // Handle error - perhaps exit or use default colors
}
    // Generate stars randomly
    const float radius = 5.0f; // Star sphere radius
    for (int i = 0; i < MAX_STAR; i++) {
        // Generate points on a sphere using spherical coordinates
        float theta = (float)rand() / RAND_MAX * 2.0f * M_PI;
        float phi = (float)rand() / RAND_MAX * M_PI;

        // Convert spherical to Cartesian coordinates
        star[i].pos[0] = radius * sin(phi) * cos(theta);
        star[i].pos[1] = radius * sin(phi) * sin(theta);
        star[i].pos[2] = radius * cos(phi);

        // White stars with slight random intensity
        float intensity = 0.5f + ((float)rand() / RAND_MAX) * 0.5f;
        star[i].col[0] = intensity;
        star[i].col[1] = intensity;
        star[i].col[2] = intensity;
        star[i].col[3] = 1.0f;
    }

    // Initialize light source
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Enable lighting and set up light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set material properties for planets
    GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Set up light properties
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Initialize camera position
    cameraX = defaultCameraX;
    cameraY = defaultCameraY;
    cameraZ = defaultCameraZ;
    reset();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void idle() {
    if (!animationEnabled) {
        return; // No updates if animation is disabled
    }

    if (isInResetState) {
        isInResetState = false;  // Clear reset state when animation starts
    }

    // Update orbital angles
    mercuryAngle = fmod(mercuryAngle + 360.0f / MERCURY_YEAR, 360.0f);
    venusAngle = fmod(venusAngle + 360.0f / VENUS_YEAR, 360.0f);
    earthAngle = fmod(earthAngle + 360.0f / EARTH_YEAR, 360.0f);
    moonAngle = fmod(moonAngle + 360.0f / MOON_YEAR, 360.0f);
    marsAngle = fmod(marsAngle + 360.0f / MARS_YEAR, 360.0f);
    jupiterAngle = fmod(jupiterAngle + 360.0f / JUPITER_YEAR, 360.0f);
    saturnAngle = fmod(saturnAngle + 360.0f / SATURN_YEAR, 360.0f);
    uranusAngle = fmod(uranusAngle + 360.0f / URANUS_YEAR, 360.0f);
    neptuneAngle = fmod(neptuneAngle + 360.0f / NEPTUNE_YEAR, 360.0f);
    plutoAngle = fmod(plutoAngle + 360.0f / PLUTO_YEAR, 360.0f);

    // Update rotation angles
    mercuryRotationAngle = fmod(mercuryRotationAngle - 360.0f / MERCURY_DAY, 360.0f);
    venusRotationAngle = fmod(venusRotationAngle - 360.0f / VENUS_DAY, 360.0f);
    earthRotationAngle = fmod(earthRotationAngle - 360.0f / EARTH_DAY, 360.0f);
    moonRotationAngle = fmod(moonRotationAngle - 360.0f / MOON_DAY, 360.0f);
    marsRotationAngle = fmod(marsRotationAngle - 360.0f / MARS_DAY, 360.0f);
    jupiterRotationAngle = fmod(jupiterRotationAngle - 360.0f / JUPITER_DAY, 360.0f);
    saturnRotationAngle = fmod(saturnRotationAngle - 360.0f / SATURN_DAY, 360.0f);
    uranusRotationAngle = fmod(uranusRotationAngle - 360.0f / URANUS_DAY, 360.0f);
    neptuneRotationAngle = fmod(neptuneRotationAngle - 360.0f / NEPTUNE_DAY, 360.0f);
    plutoRotationAngle = fmod(plutoRotationAngle - 360.0f / PLUTO_DAY, 360.0f);

    // Update global rotation angle if enabled
    if (globalRotationEnabled) {
        globalRotationAngle = fmod(globalRotationAngle + 360.0f / SOLAR_YEAR, 360.0f);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Configure display mode
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // Set initial window size and position
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);

    // Create the window
    int window = glutCreateWindow("Assignment 2 Demo Program");
    if (window == 0) {
        fprintf(stderr, "Error: Could not create GLUT window.\n");
        return EXIT_FAILURE; // Exit if window creation fails
    }

    // Register callback functions
    glutReshapeFunc(reshape);         // Handles window resizing
    glutDisplayFunc(display);         // Handles rendering
    glutKeyboardFunc(keyboard);       // Handles standard keyboard input
    glutSpecialFunc(Special);         // Handles special keys input
    glutMouseFunc(mouse);             // Handles mouse input
    glutMotionFunc(motion);           // Handles mouse motion
    glutIdleFunc(idle);               // Animation update function
    drawSatellite();


    // Initialize OpenGL and application settings
    init();

    // Start the main loop
    glutMainLoop();

    // Return success status
    return EXIT_SUCCESS; // This line is unlikely to execute in GLUT
}

