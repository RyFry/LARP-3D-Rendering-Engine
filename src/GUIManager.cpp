#include "GUIManager.hpp"

GUIManager::GUIManager()
{
	this->_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
}