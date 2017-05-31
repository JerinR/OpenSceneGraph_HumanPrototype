#ifndef _OSG_SHAPE_
#define _OSG_SHAPE_

#include <osg/Group>
#include <osg/Geode>
#include <osg/ShapeDrawable>

#include <osg/PositionAttitudeTransform>

using namespace osg;

class ExampleClass : public Group
{
public:
	ExampleClass();
	~ExampleClass(){};
	// set position of the node
	void setPosition(Vec3 pos){transform->setPosition(pos);};
	// set orientation of the node 
	void setAttitude(Quat q){transform->setAttitude(q);};

	// call this function for each frame to update the status of the node
	void update();
	// add more functions
private:
	osg::ref_ptr<PositionAttitudeTransform> transform;
};
#endif