// Example Project_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "windows.h"
#include <osg/ref_ptr>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgGA/GUIEventHandler>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgGA/GUIActionAdapter>
#include <osg/Material>
#include <osg/PolygonMode>

osg::ref_ptr<osg::PositionAttitudeTransform> transformation(osg::Vec3 basepos, osg::Vec3 pos, osg::Vec3 scale, float degree);
void changeClr(boolean flag);
osg::ref_ptr<osg::MatrixTransform> head;
osg::ref_ptr<osg::MatrixTransform> leftShoulder;
osg::ref_ptr<osg::MatrixTransform> rightShoulder;
osg::ref_ptr<osg::MatrixTransform> leftElbow;
osg::ref_ptr<osg::MatrixTransform> rightElbow;
osg::ref_ptr<osg::MatrixTransform> leftKnee;
osg::ref_ptr<osg::MatrixTransform> righKnee;
osg::ref_ptr<osg::MatrixTransform> leftHip;
osg::ref_ptr<osg::MatrixTransform> rightHip;
osg::ref_ptr<osg::MatrixTransform> body;
osg::ref_ptr<osg::MatrixTransform> middleBody;
osg::ref_ptr<osg::PositionAttitudeTransform> selected;
osgViewer::Viewer viewer;

osg::Vec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);
osg::Vec4 white(1.0f, 1.0f, 1.0f, 1.0f);


int angle_1[10] = { 0 };
int angle_2[10] = { 0 };
int angle_3[10] = { 0 };
int key = -1;

class ModelController : public osgGA::GUIEventHandler {
public: ModelController(osg::MatrixTransform* node) : _model(node){}
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	protected:    osg::ref_ptr<osg::MatrixTransform> _model;
};

osg::ref_ptr<ModelController> ctrler;

bool ModelController::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {

	osg::ref_ptr<osg::ShapeDrawable> shape;
	osg::ref_ptr<osg::PositionAttitudeTransform> shape_2;
	osg::ref_ptr<osg::MatrixTransform> shape_1;
	
	if (!_model) return false;    
	osg::Matrix matrix = _model->getMatrix();
	
	switch (ea.getEventType()) {
	case osgGA::GUIEventAdapter::KEYDOWN:
		switch (ea.getKey()) {
		case 'a': case 'A': 
			if(key==0)
				matrix *= osg::Matrix::translate(osg::Vec3(-1.0, 0.0, 0.0));
			break;
		case 'd': case 'D':
			if(key==0)
				matrix *= osg::Matrix::translate(osg::Vec3(1.0, 0.0, 0.0));
			break;
		case 'w': case 'W':
			if(key==0)
				matrix *= osg::Matrix::translate(osg::Vec3(0.0, 0.0, 1.0));
			break;
		case 's': case 'S': 
			if(key==0)
				matrix *= osg::Matrix::translate(osg::Vec3(0.0, 0.0, -1.0));
			break;
		case '1': 
			key = 1;
			viewer.removeEventHandler(ctrler.get());
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(rightShoulder->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(rightShoulder);
			viewer.addEventHandler(ctrler.get());
			viewer.run();
			break;

		case '2':
			key = 2;
			viewer.removeEventHandler(ctrler.get());
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(leftShoulder->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(leftShoulder);
			viewer.addEventHandler(ctrler.get());
			viewer.run();
			break;

		case '3':
			key = 3;
			viewer.removeEventHandler(ctrler.get());			
			shape = new osg::ShapeDrawable();			
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(rightElbow->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(rightElbow);
			viewer.addEventHandler(ctrler.get());				
			viewer.run();
			break;
		case '4':
			key = 4;
			viewer.removeEventHandler(ctrler.get());
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(leftElbow->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(leftElbow);		
			viewer.addEventHandler(ctrler.get());
			viewer.run();
			break;
		case '5':
			key = 5;
			viewer.removeEventHandler(ctrler.get());
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(righKnee->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(righKnee);			
			viewer.addEventHandler(ctrler.get());
			viewer.run();
			break;
		case '6':
			key = 6;
			viewer.removeEventHandler(ctrler.get());
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(leftKnee->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(leftKnee);
			viewer.addEventHandler(ctrler.get());
			viewer.run();
			break;
		case '7':
			key = 7;
			viewer.removeEventHandler(ctrler.get());
			changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(middleBody->getChild(0));
			changeClr(TRUE);
			ctrler = new ModelController(middleBody);			
			viewer.addEventHandler(ctrler.get());
			viewer.run();
			break;

		case '0':
			key = 0;
			viewer.removeEventHandler(ctrler.get());
			/*changeClr(FALSE);
			selected = dynamic_cast<osg::PositionAttitudeTransform*>(body->getChild(0));
			changeClr(TRUE);*/
			ctrler = new ModelController(body);
			viewer.addEventHandler(ctrler.get());
			viewer.run();

		case osgGA::GUIEventAdapter::KEY_Up:
			switch (key) {
			case 1: if (angle_1[1] < 90) {
				angle_1[1]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.30f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.30f, 0.0f, 0.0f));
			}
					break;
			case 2: if (angle_1[2] < 90) {
				angle_1[2]++;				
				matrix *= osg::Matrix::translate(osg::Vec3(-0.70f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.70f, 0.0f, 0.0f));
			}
					break;
			case 3: if (angle_1[3] < 80) {
				angle_1[3]++;
				matrix *= osg::Matrix::translate(-2.10, 0.0, 1.15);
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(2.10, 0.0, -1.15);
			}
					break;
			case 4: if (angle_1[4] < 80) {
				angle_1[4]++;
				matrix *= osg::Matrix::translate(osg::Vec3(0.10f, 0.0f, 1.35f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(-0.10f, 0.0f, -1.35f));
			}
					break;
			case 5: if (angle_1[5] < 80) {
				angle_1[5]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.70f, 0.0f, 3.5f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.70f, 0.0f, -3.5f));
			}
					break;
			case 6: if (angle_1[6] < 80) {
				angle_1[6]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.30f, 0.0f, 3.5f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.30f, 0.0f, -3.5f));
			}
					break;
			case 7: if (angle_1[7] > 0) {
				angle_1[7]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.70f, 0.0f, 2.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.70f, 0.0f, -2.0f));
			}
					break;

			default:
				break;
			}	
			break;
			
		case osgGA::GUIEventAdapter::KEY_Down:
			switch (key) {
			case 1: if (angle_1[1] > 0) {
				angle_1[1]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.30f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.30f, 0.0f, 0.0f));
			}
					break;
			case 2: if (angle_1[2] > 0) {
				angle_1[2]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.70f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.70f, 0.0f, 0.0f));
			}
					break;
			case 3: if (angle_1[3] > 0) {
				angle_1[3]--;
				matrix *= osg::Matrix::translate(osg::Vec3 (-2.10, 0.0, 1.15));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(2.10, 0.0, -1.15));
			}
			break;
			case 4: if (angle_1[4] > 0) {
				angle_1[4]--;
				matrix *= osg::Matrix::translate(osg::Vec3(0.10f, 0.0f, 1.35f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(-0.10f, 0.0f, -1.35f));
			}
					break;
			case 5: if (angle_1[5] > 0) {
				angle_1[5]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.70f, 0.0f, 3.5f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.70f, 0.0f, -3.5f));
			}
					break;
			case 6: if (angle_1[6] > 0) {
				angle_1[6]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.30f, 0.0f, 3.5f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.30f, 0.0f, -3.5f));
			}
					break;
			case 7: if (angle_1[7] <90) {
				angle_1[7]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.70f, 0.0f, 2.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::X_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.70f, 0.0f, -2.0f));
			}
					break;
			
					
			default:
				break;
			}	
			break;
		case osgGA::GUIEventAdapter::KEY_Left:
			switch (key) {
			case 1: if (angle_2[1] > 0) {
				angle_2[1]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.30f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::Y_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.30f, 0.0f, 0.0f));
			}
					break;
			case 2: if (angle_2[2] <45 ) {
				angle_2[2]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.70f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::Y_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.70f, 0.0f, 0.0f));
			}
					break;
			case 7: if (angle_2[7] > -45) {
				angle_2[7]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.0f, 0.0f, 2.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::Y_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.0f, 0.0f, -2.0f));
			}
					break;

			default:
				break;
			} break;
		case osgGA::GUIEventAdapter::KEY_Right:
			switch (key) {
			case 1: if (angle_2[1] < 45 ) {
				angle_2[1]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.30f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::Y_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.30f, 0.0f, 0.0f));
			}
					break;
			case 2: if (angle_2[2] > 0) {
				angle_2[2]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-0.70f, 0.0f, 0.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::Y_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(0.70f, 0.0f, 0.0f));
			}
					break;
			case 7: if (angle_2[7] <45) {
				angle_2[7]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.0f, 0.0f, 2.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::Y_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.0f, 0.0f, -2.0f));
			}
					break;
			default:
				break;
			} break;
		case osgGA::GUIEventAdapter::KEY_Alt_L:
			switch (key) {
			case 7: if (angle_3[7] > -10) {
				angle_3[7]--;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.0f, 0.0f, 2.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(-1.0f), osg::Z_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.0f, 0.0f, -2.0f));
			}
					break;
			default:
				break;
			}break;

		case osgGA::GUIEventAdapter::KEY_Alt_R:
			switch (key) {
			case 7: if (angle_3[7] <10) {
				angle_3[7]++;
				matrix *= osg::Matrix::translate(osg::Vec3(-1.0f, 0.0f, 2.0f));
				matrix *= osg::Matrix::rotate(osg::inDegrees(1.0f), osg::Z_AXIS);
				matrix *= osg::Matrix::translate(osg::Vec3(1.0f, 0.0f, -2.0f));
			}
					break;
			default:
				break;
			}break;

		case osgGA::GUIEventAdapter::KEY_Escape: exit(0);
			break;
		default:
			break;
		}      
		_model->setMatrix(matrix);
		break;
	default:
		break;
	}    return false;
}



int main()
{

	osg::ref_ptr<osg::Geode> root = new osg::Geode;

	osg::ref_ptr<osg::PositionAttitudeTransform>  head = 
	//head
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(1.0f, 0.0f, 0.90f), osg::Vec3(0.4f, 0.30f, 0.30f), 90.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> leftArmUp = 
	// left arm up
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.70f, 0.0f, 0.0f), osg::Vec3(0.75f, 0.15f, 0.15f), 120.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> rightArmUp =
	// right arm up
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(1.30f, 0.0f, 0.0f), osg::Vec3(0.75f, 0.15f, 0.15f), 60.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> torso = 
	//torso
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(1.0f, 0.3f, 0.3f), 90.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> leftArmDown = 
	//left arm down
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(-0.10f, 0.0f, -1.35f), osg::Vec3(0.4f, 0.15f, 0.15f), 105.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> rightArmDown =
	// right arm down
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(2.10f, 0.0f, -1.35f), osg::Vec3(0.40f, 0.15f, 0.15f), 75.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> leftLegUp =
	// left leg up
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.70f, 0.0f, -2.0f), osg::Vec3(0.75f, 0.15f, 0.15f), 105.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> rightLegUp =
	// right leg up
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(1.30f, 0.0f, -2.0f), osg::Vec3(0.75f, 0.15f, 0.15f), 75.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> rightLegDown =
	// right leg down
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(1.70f, 0.0f, -3.5f), osg::Vec3(0.75f, 0.15f, 0.15f), 90.0f);

	osg::ref_ptr<osg::PositionAttitudeTransform> leftLegDown =
	// left leg down
	transformation(osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.30f, 0.0f, -3.5f), osg::Vec3(0.75f, 0.15f, 0.15f), 90.0f);

	leftElbow = new osg::MatrixTransform;
	leftElbow->addChild(leftArmDown);

	rightElbow = new osg::MatrixTransform;
	rightElbow->addChild(rightArmDown);

	leftShoulder = new osg::MatrixTransform;
	leftShoulder->addChild(leftArmUp);
	leftShoulder->addChild(leftElbow);

	rightShoulder = new osg::MatrixTransform;
	rightShoulder->addChild(rightArmUp);
	rightShoulder->addChild(rightElbow);

	leftKnee = new osg::MatrixTransform;
	leftKnee->addChild(leftLegDown);

	righKnee = new osg::MatrixTransform;
	righKnee->addChild(rightLegDown);

	leftHip = new osg::MatrixTransform;
	leftHip->addChild(leftLegUp);
	leftHip->addChild(leftKnee);

	rightHip = new osg::MatrixTransform;
	rightHip->addChild(rightLegUp);
	rightHip->addChild(righKnee);

	middleBody = new osg::MatrixTransform;
	middleBody->addChild(head);
	middleBody->addChild(torso);
	middleBody->addChild(leftShoulder);
	middleBody->addChild(rightShoulder);

	body = new osg::MatrixTransform;
	body->addChild(leftHip);
	body->addChild(rightHip);
	body->addChild(middleBody);


	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	mt->setMatrix(osg::Matrix::rotate(osg::inDegrees(0.0f), osg::Vec3(0.0, 1.0, 0.0)));
	mt->addChild(body);
	root->addChild(mt);
	key = 0;
	selected = dynamic_cast<osg::PositionAttitudeTransform*>(middleBody->getChild(0));
	ctrler = new ModelController(mt.get());
	viewer.addEventHandler(ctrler.get());
	viewer.setSceneData(root.get());
	return viewer.run();
}

osg::ref_ptr<osg::PositionAttitudeTransform> transformation(osg::Vec3 basepos, osg::Vec3 pos, osg::Vec3 scale, float degree) {
	osg::ref_ptr<osg::ShapeDrawable> base = new osg::ShapeDrawable;
	base->setShape(new osg::Sphere(basepos,
		1.0f));
	osg::ref_ptr<osg::PositionAttitudeTransform> shape
		= new osg::PositionAttitudeTransform;
	float rollH = osg::inDegrees(degree);
	shape->setPosition(pos);
	shape->setScale(scale);
	shape->setAttitude(osg::Quat(rollH, osg::Vec3(0.0, 1.0, 0.0)));
	shape->addChild(base);
	return shape;
}

void changeClr(boolean flag) {
	osg::ref_ptr < osg::ShapeDrawable > colornode = dynamic_cast<osg::ShapeDrawable*>(selected->getChild(0));
	if (flag)
		colornode->setColor(yellow);
	else
		colornode->setColor(white);
}
