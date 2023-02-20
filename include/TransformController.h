#pragma once
#include <QObject>
#include <QMatrix4x4>


namespace Qt3DCore {
    class QTransform;
}

namespace ver
{
	class TransformController : public QObject
	{
        Q_OBJECT
            Q_PROPERTY(Qt3DCore::QTransform* target READ target WRITE setTarget NOTIFY targetChanged)
            Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
            Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)

    public:
        TransformController(QObject* parent = nullptr)
            : QObject(parent)
            , m_radius(1.0f)
            , m_angle(0.0f)
        {

        }

        void setTarget(Qt3DCore::QTransform* target)
        {
            if (m_target != target) {
                m_target = target;
                emit targetChanged();
            }
        }
        Qt3DCore::QTransform* target() const
        {
            return m_target;
        }

        void setRadius(float radius)
        {
            if (!qFuzzyCompare(radius, m_radius)) {
                m_radius = radius;
                updateMatrix();
                emit radiusChanged();
            }
        }
        float radius() const
        {
            return m_radius;
        }

        void setAngle(float angle)
        {
            if (!qFuzzyCompare(angle, m_angle)) {
                m_angle = angle;
                updateMatrix();
                emit angleChanged();
            }
        }
        float angle() const
        {
            return m_angle;
        }

    signals:
        void targetChanged();
        void radiusChanged();
        void angleChanged();

    protected:
        void updateMatrix();

    private:
        Qt3DCore::QTransform* m_target;
        QMatrix4x4 m_matrix;
        float m_radius;
        float m_angle;
	};
}