#include "TMesh.h"

#include "../ResourceManager/ResourceOBJ.h"

TMesh::TMesh(ResourceMesh *r, ResourceMaterial *m) : TEntity() {
	mesh = r;
	material = m;

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(glm::vec3), &mesh->getVertices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->getNormals().size() * sizeof(glm::vec3), &mesh->getNormals()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->getUVs().size() * sizeof(glm::vec2), &mesh->getUVs()[0], GL_STATIC_DRAW);
	
	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(unsigned short), &mesh->getIndices()[0] , GL_STATIC_DRAW);
}

TMesh::~TMesh() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
}

void TMesh::beginDraw() {    
    TMatrixCache *cache = TMatrixCache::Instance();

	glm::mat4 pM = *cache->getMatrix(OBDEEnums::Matrices::MATRIX_PROJECTION);
	glm::mat4 vM = *cache->getMatrix(OBDEEnums::Matrices::MATRIX_VIEW);
	glm::mat4 mM = cache->getCurrentMatrix();

	// Matrices
	glm::mat4 MV = vM * mM;
	glm::mat4 MVP = pM * vM * mM;
	glUniformMatrix4fv(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_MODEL), 1, GL_FALSE, &mM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_VIEW), 1, GL_FALSE, &vM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_PROJECTION), 1, GL_FALSE, &pM[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_VIEWMODEL), 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_MVP), 1, GL_FALSE, &MVP[0][0]);

	//ToDo: mejorar
	int texturesLoaded = 0;
 	for (std::map<OBDEEnums::TextureTypes, TTexture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
		if (it->first == OBDEEnums::TextureTypes::TEXTURE_AMBIENT) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_AMBIENT), texturesLoaded);
		} else if (it->first == OBDEEnums::TextureTypes::TEXTURE_DIFFUSE) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_DIFFUSE), texturesLoaded);
		} else if (it->first == OBDEEnums::TextureTypes::TEXTURE_SPECULAR) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_SPECULAR), texturesLoaded);
		} else if (it->first == OBDEEnums::TextureTypes::TEXTURE_ALPHA) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_ALPHA), texturesLoaded);
		} else if (it->first == OBDEEnums::TextureTypes::TEXTURE_BUMP) {
			glActiveTexture(GL_TEXTURE0 + texturesLoaded);
			glBindTexture(GL_TEXTURE_2D, it->second->getTextureID());
			glUniform1i(cache->getMatrixID(OBDEEnums::Matrices::MATRIX_TEXTURE_BUMP), texturesLoaded);
		}
		texturesLoaded++;
	}

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		mesh->getIndices().size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void TMesh::endDraw() {

}

void TMesh::setTexture(OBDEEnums::TextureTypes tt, TTexture* t){
	textures[tt] = t;
}

ResourceMesh* TMesh::getMesh(){
	return mesh;
}

ResourceMaterial* TMesh::getMaterial(){
	return material;
}