#pragma once 

#include "Renderer/Renderer.h" 

#include "Renderer/VertexBuffer.h" 

#include "Math/MathUtils.h" 

#include <assimp/Importer.hpp> 

#include <assimp/scene.h> 

#include <assimp/postprocess.h> 

namespace neu{

	class Model : public Resource{

	public:
		
		struct vertex_t{

			glm::vec3 position;
			
			glm::vec2 texcoord;
		
		};

	public:
		
		bool Create(std::string filename, ...) override;

	private:
		
		void ProcessNode(aiNode* node, const aiScene* scene);
		
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:
		
		VertexBuffer m_vertexBuffer;

	};

}
