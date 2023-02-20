#pragma once
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QEntity>

namespace Qt3DExtras {
	class Qt3DWindow;
}

namespace ver
{
	class Scene
	{
	public:
		Scene(Qt3DExtras::Qt3DWindow& view);
	private:
		Qt3DCore::QEntity root;
		Qt3DExtras::QPhongMaterial* material;
	};
}