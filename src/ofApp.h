#pragma once

#include <string>
#include "ofMain.h"
#include "ofxSpout2Sender.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

		int static const sq_x = 10; //èÌÇ…ãÙêîÇ…Ç∑ÇÈÇ±Ç∆
		int static const sq_y = 8;

		int static const bg_total = sq_x * sq_y;
		bool bg_no[bg_total + 1];
		int bg_hist[bg_total + 1];

		int static const dp_x = 1920;
		int static const dp_y = 1080;
		ofVec2f dp_w_offset;
		ofVec2f dp_n_space;
		ofVec2f dp_n_offset;
		string dp_num[101] = {"00", "01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};
		bool dp_fin;
		ofTrueTypeFont dp_main_drw;
		ofTrueTypeFont dp_def_drw;
		ofTrueTypeFont dp_fin_drw;
		ofVec3f dp_c1 = ofVec3f(28, 142, 210);
		ofVec3f dp_c2 = ofVec3f(255, 255, 255);
		ofVec3f dp_c3 = ofVec3f(97, 179, 234);


		//Spout
		ofFbo spout_fbo;
		ofxSpout2::Sender spout;

};
