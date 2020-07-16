
#ifndef FISH_H
#define FISH_H



//Sphere model made out of triangles
//Contains arrays:
//vertices - vertex positions in homogenous coordinates
//normals - vertex normals in homogenous coordinates
//texCoords - texturing coordinates


#include "model.h"
namespace Models {

	using namespace std;
	using namespace glm;

	class Fish: public Model {

		public:
			Fish();
			Fish(float r,float mainDivs,float tubeDivs);
			virtual ~Fish();
			virtual void drawSolid(bool smooth=true);

		private:
			vector<vec4> internalVertices;
			vector<vec4> internalFaceNormals;
			vector<vec4> internalVertexNormals;

			inline float d2r(float deg);
			vec4 generateFishPoint(float r,float alpha,float beta);
			vec4 computeVertexNormal(float alpha,float beta);
			vec4 computeFaceNormal(vector<vec4> &face);
			void generateFishFace(vector<vec4> &vertices, vector<vec4> &vertexNormals, vec4 &faceNormal,float r,float alpha,float beta,float step_alpha,float step_beta);
			void buildFish(float r,float divs1,float divs2);

	};

	extern Fish fish;

}

#endif
