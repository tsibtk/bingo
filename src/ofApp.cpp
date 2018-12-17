#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//デフォルト設定
	ofSetFrameRate(30);
	ofBackground(127);
	ofSetCircleResolution(32);
	ofSetWindowTitle("Bingo Manager");
	
	ofTrueTypeFontSettings dp_main_stg("product.ttf", 475);
	dp_main_stg.antialiased = true;
	dp_main_stg.dpi = 72;
	dp_main_stg.direction = OF_TTF_LEFT_TO_RIGHT;
	dp_main_drw.load(dp_main_stg);

	ofTrueTypeFontSettings dp_def_stg("product.ttf", 70);
	dp_def_stg.antialiased = true;
	dp_def_stg.dpi = 72;
	dp_def_stg.direction = OF_TTF_LEFT_TO_RIGHT;
	dp_def_drw.load(dp_def_stg);

	ofTrueTypeFontSettings dp_fin_stg("product.ttf", 550);
	dp_fin_stg.antialiased = true;
	dp_fin_stg.dpi = 72;
	dp_fin_stg.direction = OF_TTF_LEFT_TO_RIGHT;
	dp_fin_drw.load(dp_fin_stg);

	//FINISH, 全文字の中央揃え、Historyの文字に関しては位置未汎用化

}

//--------------------------------------------------------------
void ofApp::update(){

	dp_w_offset = ofVec2f(100);
	dp_n_space = ofVec2f(((dp_x - (dp_w_offset.x * 2)) / ((sq_x * 4) - 1) * 3), ((dp_y - (dp_w_offset.y * 2)) / (((sq_y + (sq_x / 2)) * 4) - 1) * 3));
	dp_n_offset = ofVec2f(((dp_x - (dp_w_offset.x * 2)) / ((sq_x * 4) - 1) * 1), ((dp_y - (dp_w_offset.y * 2)) / (((sq_y + (sq_x / 2)) * 4) - 1) * 1));

}

//--------------------------------------------------------------
void ofApp::draw(){

	spout_fbo.allocate(dp_x, dp_y, GL_RGB);
	spout_fbo.begin();

	ofClear(0, 0, 0, 255);

	ofSetColor(dp_c1.x, dp_c1.y, dp_c1.z);
	ofDrawRectangle(0, 0, dp_x, dp_y);

	ofFill();
	ofSetColor(dp_c2.x, dp_c2.y, dp_c2.z);
	ofBeginShape();
	ofVertex(ofPoint(0, dp_y));
	ofVertex(ofPoint(dp_x, dp_y));
	ofVertex(ofPoint(dp_x, (dp_y * 0.9)));
	ofEndShape(true);

	//Main Number
	ofSetColor(dp_c3.x, dp_c3.y, dp_c3.z);
	ofDrawRectangle(dp_w_offset.x, dp_w_offset.y, (dp_n_space.x * (sq_x / 2)) + (dp_n_offset.x * ((sq_x / 2) - 1)), (dp_n_space.y * (sq_x / 2)) + (dp_n_offset.y * ((sq_x / 2) - 1)));
	ofSetColor(dp_c2.x, dp_c2.y, dp_c2.z);
	string txt = dp_num[bg_hist[0]];
	int txt_w = (dp_n_space.x - dp_main_drw.stringWidth(txt)) / 2;
	int txt_h = (dp_n_space.y - dp_main_drw.stringHeight(txt)) / 2;
	dp_main_drw.drawString(dp_num[bg_hist[0]], dp_w_offset.x + 50, dp_w_offset.y + (dp_n_space.y * (sq_x / 2)) + 50);
	
	//History
	ofSetColor(dp_c2.x, dp_c2.y, dp_c2.z);
	string txt2 = dp_num[bg_hist[0]];
	int txt_w2 = (dp_n_space.x - dp_def_drw.stringWidth(txt2)) / 2;
	int txt_h2 = (dp_n_space.y - dp_def_drw.stringHeight(txt2)) / 2;
	dp_def_drw.drawString(">>>>> HISTORY >>>>>", dp_w_offset.x + (dp_n_space.x * (sq_x / 2)) + (dp_n_offset.x * (sq_x / 2)), dp_w_offset.y + (dp_n_space.y * 2) + (dp_n_offset.y * 2) + dp_n_space.y); //位置未汎用化
	for (int i = 1; i <= (sq_x / 2); i++) {
		ofSetColor(dp_c3.x, dp_c3.y, dp_c3.z);
		ofDrawRectangle(dp_w_offset.x + (dp_n_space.x * (4 + i)) + (dp_n_offset.x * (4 + i)), dp_w_offset.y + (dp_n_space.y * 3) + (dp_n_offset.y * 3), dp_n_space.x, dp_n_space.y);
		ofSetColor(dp_c2.x, dp_c2.y, dp_c2.z);
		string txt = dp_num[bg_hist[i]];
		int txt_w = (dp_n_space.x - dp_def_drw.stringWidth(txt)) / 2;
		int txt_h = (dp_n_space.y - dp_def_drw.stringHeight(txt)) / 2;
		dp_def_drw.drawString(dp_num[bg_hist[i]], dp_w_offset.x + (dp_n_space.x * (4 + i)) + (dp_n_offset.x * (4 + i)) + txt_w, dp_w_offset.y + (dp_n_space.y * 3) + (dp_n_offset.y * 3) + dp_n_space.y + txt_h);
	}

	//All Numbers
	for (int iy = 0; iy <= sq_y - 1; iy++) {
		for (int ix = 1; ix <= sq_x; ix++) {
			int ix_ = ix;
			int iy_ = iy;
			if (ix_ == 10) {
				ix_ = 0;
				iy_ = iy_ + 1;
			}
			int inum = ofToInt(ofToString(iy_) + ofToString(ix_));

			if (bg_no[inum] == FALSE) {
				ofSetColor(dp_c3.x, dp_c3.y, dp_c3.z);
			}
			else {
				ofSetColor(dp_c2.x, dp_c2.y, dp_c2.z);
			}
			ofDrawRectangle(dp_w_offset.x + (dp_n_space.x * (ix - 1)) + (dp_n_offset.x * (ix - 1)), dp_w_offset.y + (dp_n_space.y * ((sq_x / 2) + iy)) + (dp_n_offset.y * ((sq_x / 2) + iy)), dp_n_space.x, dp_n_space.y);

			if (bg_no[inum] == FALSE) {
				ofSetColor(dp_c2.x, dp_c2.y, dp_c2.z);
			}
			else {
				ofSetColor(dp_c1.x, dp_c1.y, dp_c1.z);
			}
			string txt = dp_num[inum];
			int txt_w = (dp_n_space.x - dp_def_drw.stringWidth(txt)) / 2;
			int txt_h = (dp_n_space.y - dp_def_drw.stringHeight(txt)) / 2;
			dp_def_drw.drawString(dp_num[inum], dp_w_offset.x + (dp_n_space.x * (ix - 1)) + (dp_n_offset.x * (ix - 1)) + txt_w, dp_w_offset.y + (dp_n_space.y * ((sq_x / 2) + iy)) + (dp_n_offset.y * ((sq_x / 2) + iy)) + dp_n_space.y + txt_h);
		}
	}


	if (dp_fin == TRUE) {
		ofSetColor(255, 0, 0);
		dp_fin_drw.drawString("FINISH!!", 50, 950);
	}
	
	spout_fbo.end();
	spout.sendTexture(spout_fbo.getTexture(), "Bingo");
	spout_fbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	ofSetColor(255);

	for (int i = 1; i <= bg_total; i++) {
		if (bg_no[i] == TRUE) {
			ofDrawBitmapString("NUM " + ofToString(i) + ": TRUE", 150, i * 15);
		}
		else {
			ofDrawBitmapString("NUM " + ofToString(i) + ": FALSE", 150, i * 15);
		}
	}

	for (int i = 0; i <= bg_total; i++) {
		ofDrawBitmapString("HIST " + ofToString(i) + ": " + ofToString(bg_hist[i]), 10, (i + 1) * 15);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key) {
	case 'n':
		if (dp_fin == FALSE) {
			for (int i = bg_total; i >= 0; i--) {
				bg_hist[i + 1] = bg_hist[i];
			}
			for (int i = 1; i <= 9999; i++) {
				if (bg_no[bg_hist[0]] == TRUE) {
					bg_hist[0] = ofRandom(1, bg_total + 1);
				}
				else {
					bg_no[bg_hist[0]] = TRUE;
					break;
				}
			}
		};
		for (int i = 1; i <= bg_total; i++) {
			if (bg_no[i] == FALSE) {
				break;
			};
			if (i == bg_total) {
				dp_fin = TRUE;
			};
		};
	}
}