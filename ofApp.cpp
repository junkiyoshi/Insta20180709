#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofNoFill();
	ofSetColor(239);
	ofSetLineWidth(2);

	this->font_size = 100;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<char> charactors = { 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L',
		'M', 'N', 'O', 'P', 'Q', 'R',
		'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', '!' };
	int sample_count = 180;
	for (int charactor_index = 0; charactor_index < charactors.size(); charactor_index++) {

		ofPath path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		ofPoint location = ofPoint(charactor_index % 6 * this->font_size * 1.2 + this->font_size * 0.7, charactor_index / 6 * this->font_size * 1.4 + this->font_size * 0.7);
		ofPushMatrix();
		ofTranslate(location);

		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index == 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			ofBeginShape();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x - this->font_size * 0.5, vertices[vertices_index].y + this->font_size * 0.5, vertices[vertices_index].z);
				ofPoint noise_point = location + point;
				int noise_value = ofMap(ofNoise(noise_point.x * 0.001, noise_point.y * 0.001, ofGetFrameNum() * 0.008), 0, 1, 0.2, 1.2) * 10;

				ofVertex(point * noise_value * 0.1);
			}
			ofEndShape(true);
		}

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}