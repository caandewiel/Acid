#pragma once

#include <BulletCollision/CollisionShapes/btConeShape.h>
#include "Collider.hpp"
#include "Maths/Vector3.hpp"

namespace acid
{
	class ACID_EXPORT ColliderCone :
		public Collider
	{
	private:
		btConeShape *m_shape;
		float m_radius;
		float m_height;
	public:
		ColliderCone(const float &radius = 1.0f, const float &height = 1.0f);

		~ColliderCone();

		void Start() override;

		void Update() override;

		void Load(LoadedValue *value) override;

		void Write(LoadedValue *destination) override;

		std::string GetName() const override { return "ColliderCone"; };

		btCollisionShape *GetCollisionShape() const override;

		float GetRadius() const { return m_radius; }

		void SetRadius(const float &radius) { m_radius = radius; }

		float GetHeight() const { return m_height; }

		void SetHeight(const float &height) { m_height = height; }
	};
}