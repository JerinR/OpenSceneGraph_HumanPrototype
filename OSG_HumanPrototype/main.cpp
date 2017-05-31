/* Project-I*/
/*Extend your project based on this program*/

#include <osg/LOD>//Level-of-detail nodes
#include <osg/PolygonMode>//setting polygon modes
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgUtil/Simplifier>

int main( int argc, char** argv )
{
	osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable;
	shape1->setShape( new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 40.0f) );
	shape1->setColor( osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) );

	osg::ref_ptr<osg::Geode> model1 = new osg::Geode;
	model1->addDrawable( shape1.get() );

	osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
	pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
	model1->getOrCreateStateSet()->setAttribute( pm.get() );
    
  	///////////////level of detail////////////////////////////////


	osg::ref_ptr<osg::Node> model2L3 = osgDB::readNodeFile( "cessnafire.osg" );//change your model here
	osg::ref_ptr<osg::Node> model2L2 = dynamic_cast<osg::Node*>(model2L3->clone(osg::CopyOp::DEEP_COPY_ALL) );
	osg::ref_ptr<osg::Node> model2L1 = dynamic_cast<osg::Node*>(model2L3->clone(osg::CopyOp::DEEP_COPY_ALL) );

	osgUtil::Simplifier simplifier;
	simplifier.setSampleRatio( 0.5 );
	model2L2->accept( simplifier );
	simplifier.setSampleRatio( 0.1 );
	model2L1->accept( simplifier );

	osg::ref_ptr<osg::LOD> model2LOD = new osg::LOD;
	model2LOD->addChild( model2L1.get(), 200.0f, FLT_MAX );
	model2LOD->addChild( model2L2.get(), 50.0f, 200.0f );
	model2LOD->addChild( model2L3.get(), 0.0f, 50.0f );

	/////////////////////////transformation///////////////////////
    osg::ref_ptr<osg::MatrixTransform> transformation2 = new osg::MatrixTransform;
    transformation2->setMatrix( osg::Matrix::translate(0.0f, 0.0f, 5.0f) );//change the transformation of model2
    transformation2->addChild( model2LOD.get() );

	osg::ref_ptr<osg::Node> model3 = osgDB::readNodeFile("robot.osg");
	osg::ref_ptr<osg::MatrixTransform> transformation3 = new osg::MatrixTransform;
	transformation3->setMatrix( osg::Matrix::translate(0.0f, 0.0f, -15.0f));//change the transformation of model3
	transformation3->addChild( model3.get());
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( model1.get() );
    root->addChild( transformation2.get() );
	root->addChild( transformation3.get() );
    
	////////////////viewer/////////////////////////////
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}


