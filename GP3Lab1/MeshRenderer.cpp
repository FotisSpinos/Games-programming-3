#include "MeshRenderer.h"
#include "pch.h"
#include "Entity.h"
#include "Common.h"
#include "Application.h"
#include "Camera.h"
#include "LightingEnvironment.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture)
{
	m_mesh = mesh;
	m_program = program;
	m_texture = texture;
}


MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture)
{
	m_model = model;
	m_program = program;
	m_texture = texture;

	for (Mesh* mesh : m_model->GetMeshes())
	{
		mesh->Bind();

		if (m_texture) 
			m_texture->Bind();

		GL_ATTEMPT(glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
	}
}

void MeshRenderer::OnUpdate(float deltaTime)
{
	Transform *test = m_entity->GetTransform();
}

void MeshRenderer::OnRender()
{
	m_program->Use();

	//set uniforms here!
	glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();

	// Model view projection matrix
	glm::mat4 mvp = Application::GetInstance()->GetCamera()->Get() * model;

	//Add model attribute
	GLuint loc = glGetUniformLocation(m_program->Get(), "model");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(model));


	loc = glGetUniformLocation(m_program->Get(), "MVP");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(mvp));

	glm::vec3 oColor = glm::vec3(1.0f, 1.0f, 1.0f);
	loc = glGetUniformLocation(m_program->Get(), "objectColor");
	glUniform3f(loc, oColor.x, oColor.y, oColor.z);
	
	// Add Texture here
	loc = glGetUniformLocation(m_program->Get(), "usingTexture");
	glUniform1i(loc, 0);	//change value to use different texture

	// Add camera position
	loc = glGetUniformLocation(m_program->Get(), "cameraPos");
	glm::vec3 cameraPos = Application::GetInstance()->GetCamera()->GetParentTransform()->GetPosition();
	glUniform3f(loc, cameraPos.x, cameraPos.y, cameraPos.z);

	// Pass game correction to shader
	float gammaCorrection = 1.0f / 2.2f;
	loc = glGetUniformLocation(m_program->Get(), "gammaCorrection");
	glUniform1f(loc, gammaCorrection);

	// Pass point lights parameters
	LightingEnvironment::GetInstance()->PassPointLightsToShader(m_program);


	// A model is assosciated with loading data from files. This is not required when render a mesh
	// Provide support for rendering meshes and models 
	if (m_model != nullptr)
	{
		for (Mesh* currentMesh : m_model->GetMeshes())
		{
			currentMesh->Bind();
			GL_ATTEMPT(glDrawElements(GL_TRIANGLES, currentMesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
		}
	}
	if (m_mesh != nullptr)
	{
		m_mesh->Bind();
		GL_ATTEMPT(glDrawElements(GL_TRIANGLES, m_mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
	}
}