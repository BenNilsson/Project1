#include "SceneLevel1.h"

#include <glm/glm.hpp>

#include "Constants.h"

#include <iostream>

// Point light positions
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

// Point light colors
glm::vec3 pointLightColors[] = {
glm::vec3(0.8f, 0.8f, 0.8f),
glm::vec3(0.8f, 0.8f, 0.8f),
glm::vec3(0.8f, 0.8f, 0.8f),
glm::vec3(0.8f, 0.8f, 0.8f)
};



void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

SceneLevel1::SceneLevel1(GLFWwindow* window) : Scene("level1", window)
{
	// Shaders
	lightingShader = new Shader("Shaders/multiple_lights.vs", "Shaders/multiple_lights.fs");
	modelShader = new Shader("Shaders/model.vs", "Shaders/model.fs");

	lightingShader->use();
	lightingShader->setInt("material.diffuse", 0);
	lightingShader->setInt("material.specular", 1);

	// Configure Shader
	ConfigureLightShader();

	// Game Objects
	penguin = new Penguin((char*)"Objects/Penguinv2/Penguin.obj", Transform(glm::vec3(0.5f, -1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f)), lightingShader);

	ak47 = new GameObject((char*)"Objects/ak47/ak_47.obj", Transform(glm::vec3(1.3f, -0.15f, 1.0f), glm::vec3(0.50f), glm::vec3(1.0f)), lightingShader);
}

SceneLevel1::~SceneLevel1()
{
}

void SceneLevel1::Update(float deltaTime)
{
	// Set Lighting Shader's Colors
	lightingShader->use();
	lightingShader->setVec3("viewPos", Camera::GetInstance()->Position);
	lightingShader->setFloat("material.shininess", 32.0f);

	// View/Projection Transforms
	glm::mat4 projection = glm::perspective(glm::radians(Camera::GetInstance()->Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = Camera::GetInstance()->GetViewMatrix();
	lightingShader->setMat4("projection", projection);
	lightingShader->setMat4("view", view);

	// World Transform
	glm::mat4 model = glm::mat4(1.0f);
	lightingShader->setMat4("model", model);
}

void SceneLevel1::Render()
{
	ak47->Render();
	penguin->Render();
}



void SceneLevel1::HandleInputs(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Camera::GetInstance()->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Camera::GetInstance()->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Camera::GetInstance()->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Camera::GetInstance()->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		Camera::GetInstance()->ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Camera::GetInstance()->ProcessKeyboard(UP, deltaTime);
}



void SceneLevel1::ConfigureLightShader()
{
	// directional light
	lightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	lightingShader->setVec3("dirLight.ambient", 0.3f, 0.24f, 0.14f);
	lightingShader->setVec3("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
	lightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	lightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
	lightingShader->setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);
	lightingShader->setVec3("pointLights[0].diffuse", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	lightingShader->setVec3("pointLights[0].specular", pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	lightingShader->setFloat("pointLights[0].constant", 1.0f);
	lightingShader->setFloat("pointLights[0].linear", 0.09);
	lightingShader->setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	lightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
	lightingShader->setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1, pointLightColors[1].y * 0.1, pointLightColors[1].z * 0.1);
	lightingShader->setVec3("pointLights[1].diffuse", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	lightingShader->setVec3("pointLights[1].specular", pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	lightingShader->setFloat("pointLights[1].constant", 1.0f);
	lightingShader->setFloat("pointLights[1].linear", 0.09);
	lightingShader->setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	lightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
	lightingShader->setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1, pointLightColors[2].y * 0.1, pointLightColors[2].z * 0.1);
	lightingShader->setVec3("pointLights[2].diffuse", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	lightingShader->setVec3("pointLights[2].specular", pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	lightingShader->setFloat("pointLights[2].constant", 1.0f);
	lightingShader->setFloat("pointLights[2].linear", 0.09);
	lightingShader->setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	lightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
	lightingShader->setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
	lightingShader->setVec3("pointLights[3].diffuse", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	lightingShader->setVec3("pointLights[3].specular", pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	lightingShader->setFloat("pointLights[3].constant", 1.0f);
	lightingShader->setFloat("pointLights[3].linear", 0.09);
	lightingShader->setFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	lightingShader->setVec3("spotLight.position", Camera::GetInstance()->Position);
	lightingShader->setVec3("spotLight.direction", Camera::GetInstance()->Front);
	lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	lightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	lightingShader->setFloat("spotLight.constant", 1.0f);
	lightingShader->setFloat("spotLight.linear", 0.09);
	lightingShader->setFloat("spotLight.quadratic", 0.032);
	lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	lightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}
