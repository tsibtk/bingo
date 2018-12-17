#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char * argv[]){

	//ofSetupOpenGL(1280, 1000, OF_WINDOW);
	ofSetupOpenGL(1280, 720, OF_WINDOW);


	//ofGLFWWindowSettings settings;
	//settings.setGLVersion(4, 5);
	//settings.setSize(1280, 720);
	//ofCreateWindow(settings);


	ofRunApp(new ofApp());

}
