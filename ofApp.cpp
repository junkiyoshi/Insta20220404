#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 60 < 35) {

		this->noise_param += ofMap(ofGetFrameNum() % 60, 0, 35, 0.14, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {


	float radius = 80;
	for (int x = radius * 1.5; x <= ofGetWidth() - radius; x += radius * 3) {

		for (int y = radius * 1.5; y <= ofGetWidth() - radius; y += radius * 3) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int deg = 0; deg < 360; deg += 30) {

				auto base_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				auto noise_value = ofNoise(glm::vec3(base_location * 0.010, this->noise_param) + glm::vec3(x, y, 0));
				auto noise_radius = radius * ofMap(noise_value, 0, 1, 0.15, 1.5);// (noise_value + 1.5);

				this->draw_arrow(base_location, glm::vec2(noise_radius * cos(deg * DEG_TO_RAD), noise_radius * sin(deg * DEG_TO_RAD)), 18, ofColor(255));
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	if (glm::length(distance) > size * 0.1) {

		ofPushMatrix();
		ofTranslate(target);

		ofSetColor(color);
		ofFill();
		ofBeginShape();
		ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
		ofEndShape();

		ofBeginShape();
		ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
		ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
		ofEndShape();

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}