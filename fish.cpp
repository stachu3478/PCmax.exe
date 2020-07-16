#include "fish.h"
namespace Models {

	Fish fish;

	Fish::Fish() {
		buildFish(1,12,12);
	}

	Fish::Fish(float r,float divs1,float divs2) {
		buildSphere(r,divs1,divs2);
	}

	Fish::~Fish() {
	}


		vertices=(float*)internalVertices.data();
		normals=(float*)internalFaceNormals.data();
		vertexNormals=(float*)internalVertexNormals.data();
		texCoords=vertexNormals;
		vertexCount=internalVertices.size();
	}

	void Sphere::drawSolid(bool smooth) {

		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        //glEnableVertexAttribArray(3);


        glVertexAttribPointer(0,4,GL_FLOAT,false,0,vertices);
        if (!smooth) glVertexAttribPointer(1,4,GL_FLOAT,false,0,normals);
        else glVertexAttribPointer(1,4,GL_FLOAT,false,0,vertexNormals);
        glVertexAttribPointer(2,4,GL_FLOAT,false,0,texCoords);
        //glVertexAttribPointer(3,4,GL_FLOAT,false,0,Models::CubeInternal::colors);

        glDrawArrays(GL_TRIANGLES,0,vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        //glDisableVertexAttribArray(3);

	}


}
