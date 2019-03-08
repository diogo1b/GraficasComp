/*
 * Sergio Ruiz.
 *
 * TC3022. Computer Graphics Course.
 * Basic template OpenGL project.
 */

 // Please don't change lines 9-31 (It helps me to grade)
#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

void Material() {
	ofstream materialfile;
	materialfile.open("Shape.mtl");
	materialfile <<"newmtl shape\nKa 0.12 0.12 0.12\nKd 1 0 0\nKs 0.65 0.65 0.65\nNs 75";
	materialfile.close();
}

void Plane(float width, float height, int vDivs, int hDivs) {
	
	//Se crea el archivo
	ofstream myfile;
	//Se abre el archivo
	myfile.open("Plane.obj");

	const float distance_V = height / vDivs;
	const float distance_H = width / hDivs;
	int vertexes = 0;
	int countV = 0;

	//Se importa el material
	myfile << "mtllib Shape.mtl\n\n";

	//Empieza la gemoetría
	myfile << "#GEOMETRY\n\n";

	for (float i = 0; i <= width; i = i + distance_H) {
		for (float j = 0; j <= height; j = j + distance_V)
		{
			vertexes++;

			char str[999];
			char a[999];
			char b[999];
			
			gcvt(i, 5, a);
			gcvt(j, 5, b);

			strcpy(str, "v ");
			strcat(str, a);
			strcat(str, "0 ");
			strcat(str, b);
			strcat(str, "0 0\n");

			myfile << str;
		}
	}

	//Se escribe el numero de vertices en nuestro plano
	myfile << "\n#Number of Vetexes: ";
	myfile << vertexes;
	myfile << "\n";

	//Se establece la normal para el plano
	myfile << "\n#Normal Vector: ";
	myfile << "\nvn 0 1 0\n";

	myfile << "\n#TOPOLOGY\n# f vi/ti/ni vi/ti/ni vi/ti\n";
	// Se utiliza el material creado
	myfile << "\nusemtl shape\n\n";

	// Se escribe la topología
	for (int i = 1; i < vertexes- vDivs; i++) {

		char str[999];
		char v1[999];
		char v2[999];
		char v3[999];
		char v4[999];

		int b = i + vDivs + 2;
		int c = i + 1;
		int d = b - 1;

		itoa(i, v1, 10);
		itoa(b, v2, 10);
		itoa(c, v3, 10);
		itoa(d, v4, 10);

		if (countV < vDivs ) {
			
			strcpy(str, "f ");
			strcat(str, v1);
			strcat(str, "//");
			strcat(str, "1 ");

			strcat(str, v2);
			strcat(str, "//");
			strcat(str, "1 ");

			strcat(str, v3);
			strcat(str, "//");
			strcat(str, "1\n");

			strcat(str, "f ");
			strcat(str, v1);
			strcat(str, "//");
			strcat(str, "1 ");

			strcat(str, v4);
			strcat(str, "//");
			strcat(str, "1 ");

			strcat(str, v2);
			strcat(str, "//");
			strcat(str, "1\n\n");
		}
		else {
			countV = -1;
			strcpy(str, "");
		}
		
		myfile << str;
		countV++;
	}

	myfile.close();

}

int main(int argc, char* argv[])
{
	Material();
	Plane(30.0f,30.0f,5,20);

	return 0;
}
