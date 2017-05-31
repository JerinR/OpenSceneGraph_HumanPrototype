#include "ExampleClass.h"

ExampleClass::ExampleClass()
{
	//make a shape here
	// for example, you can make a unit box 
	ref_ptr<Box> box = new Box(Vec3(0,0,0), 1);
	ref_ptr<ShapeDrawable> drawable = new ShapeDrawable(box);
	ref_ptr<Geode> geo = new Geode;
	geo->addDrawable(drawable);
	transform = new PositionAttitudeTransform;
	transform->addChild(geo);

	Group::addChild(transform);
}

void ExampleClass::update()
{
	// put your source code here
}