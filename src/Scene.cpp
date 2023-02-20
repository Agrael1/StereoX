#include <Scene.h>
#include <Qt3DExtras/Qt3DWindow>
//#include <Qt3DRender/QRenderAspect>
//#include <Qt3DRender/QGeometryRenderer>
//#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DCore/QTransform>
#include <QPropertyAnimation>

#include <TransformController.h>


ver::Scene::Scene(Qt3DExtras::Qt3DWindow& view)
	:material(new Qt3DExtras::QPhongMaterial(&root))
{
    Qt3DCore::QEntity* torusEntity = new Qt3DCore::QEntity(&root);
    Qt3DExtras::QTorusMesh* torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(5);
    torusMesh->setMinorRadius(1);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);

    Qt3DCore::QTransform* torusTransform = new Qt3DCore::QTransform;
    torusTransform->setScale3D(QVector3D(1.5, 1, 0.5));
    torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));

    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(torusTransform);
    torusEntity->addComponent(material);


    Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(&root);
    Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(3);
    sphereMesh->setGenerateTangents(true);

    Qt3DCore::QTransform* sphereTransform = new Qt3DCore::QTransform;
    TransformController* controller = new TransformController(sphereTransform);
    controller->setTarget(sphereTransform);
    controller->setRadius(20.0f);

    QPropertyAnimation* sphereRotateTransformAnimation = new QPropertyAnimation(sphereTransform);
    sphereRotateTransformAnimation->setTargetObject(controller);
    sphereRotateTransformAnimation->setPropertyName("angle");
    sphereRotateTransformAnimation->setStartValue(QVariant::fromValue(0));
    sphereRotateTransformAnimation->setEndValue(QVariant::fromValue(360));
    sphereRotateTransformAnimation->setDuration(10000);
    sphereRotateTransformAnimation->setLoopCount(-1);
    sphereRotateTransformAnimation->start();

    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphereTransform);
    sphereEntity->addComponent(material);

	view.setRootEntity(&root);
}
