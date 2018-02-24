#include "LodBehaviour.hpp"

#include "../Scenes/Scenes.hpp"
#include "../Events/Events.hpp"
#include "../Events/EventTime.hpp"
#include "../Maths/Maths.hpp"
#include "../Meshes/Mesh.hpp"
#include "Terrains.hpp"
#include "MeshTerrain.hpp"

namespace Flounder
{
	LodBehaviour::LodBehaviour() :
		Behaviour(true),
		m_modelLods(std::vector<Model *> ()),
		m_currentLod(-1)
	{
		for (int i = 0; i < static_cast<int>(TerrainRender::SQUARE_SIZES.size()); i++)
		{
			m_modelLods.push_back(nullptr);
		}
	}

	LodBehaviour::~LodBehaviour()
	{
		for (auto model : m_modelLods)
		{
			delete model;
		}
	}

	void LodBehaviour::Update()
	{
		Vector3 cameraPosition = Vector3(*Scenes::Get()->GetCamera()->GetPosition());
		cameraPosition.m_y = 0.0f;
		Vector3 chunkPosition = Vector3(*GetGameObject()->GetTransform()->m_position);
		chunkPosition.m_y = Terrains::Get()->GetHeight(cameraPosition.m_x, cameraPosition.m_z);
		const float distance = Vector3::GetDistance(chunkPosition, cameraPosition);

		// lnreg{ (90.5, 0), (181, 1), (362, 2) } = int(-6.500 + 1.443 * log(x) / log(2.718)) + 1
		// float lodf = floor(-6.5f + 1.443f * log(distance) / log(2.718f)) + 1.0f;
		float lod = std::floor(0.0090595f * distance - 1.22865f) + 1.0f;
		lod = Maths::Clamp(lod, 0.0f, static_cast<float>(TerrainRender::SQUARE_SIZES.size() - 1));
		int lodi = static_cast<int>(lod);

		if (lodi != m_currentLod)
		{
			if (m_modelLods[lodi] == nullptr)
			{
				CreateLod(lodi);
			}

			auto mesh = GetGameObject()->GetComponent<Mesh>();

			if (mesh != nullptr)
			{
				mesh->SetModel(m_modelLods[lod]);
			}

			m_currentLod = lodi;
		}
	}

	void LodBehaviour::OnEnable()
	{
	}

	void LodBehaviour::OnDisable()
	{
	}

	void LodBehaviour::CreateLod(const int &lod)
	{
		if (m_modelLods[lod] != nullptr)
		{
			return;
		}

#if FLOUNDER_VERBOSE
		const auto debugStart = Engine::Get()->GetTimeMs();
#endif
		const float squareSize = TerrainRender::SQUARE_SIZES[lod];
		const float textureScale = TerrainRender::TEXTURE_SCALES[lod];
		const int vertexCount = CalculateVertexCount(TerrainRender::SIDE_LENGTH, squareSize);
		m_modelLods[lod] = new MeshTerrain(static_cast<float>(TerrainRender::SIDE_LENGTH), 1.028f * squareSize, vertexCount, textureScale, GetGameObject()->GetTransform()->m_position);
#if FLOUNDER_VERBOSE
		const auto debugEnd = Engine::Get()->GetTimeMs();

		if (debugEnd - debugStart > 22.0f)
		{
			printf("Terrain LOD %i took %fms to build\n", lod, debugEnd - debugStart);
		}
#endif
	}

	int LodBehaviour::CalculateVertexCount(const int &terrainLength, const float &squareSize)
	{
		return static_cast<int>((2.0 * terrainLength) / static_cast<float>(squareSize)) + 1;
	}
}