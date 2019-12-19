#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

typedef uint32_t DebugTextureID;

class DebugRenderer
{
public:
	DebugRenderer();
	~DebugRenderer();

    void setWindowHandle(SDL_Window* window);

	void swap() const;
    void clear() const;

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;
    void setColor(glm::vec<4, uint8_t> color) const;

    void drawLine(int x1, int y1, int x2, int y2) const;
    void drawLine(glm::vec2 point1, glm::vec2 point2) const;

	void drawRectangle(int x, int y, int w, int h, bool filled = false) const;
    void drawRectangle(glm::vec2 position, glm::vec2 size, bool filled = false) const;
    void drawRectangle(glm::vec4 rect, bool filled = false) const;
    void drawRectangle(SDL_Rect rect, bool filled = false) const;

	DebugTextureID loadTexture(const char* filename);
	DebugTextureID loadTexture(const std::string& filename);

	void drawTexture(DebugTextureID id, int x, int y, int w, int h) const;
	void drawTexture(DebugTextureID id, glm::vec2 position, glm::vec2 size) const;
	void drawTexture(DebugTextureID id, glm::vec4 rect) const;
	void drawTexture(DebugTextureID id, SDL_Rect rect) const;

private:
    SDL_Renderer* renderer_ = nullptr;
	std::map<DebugTextureID, SDL_Texture*> textures_;
};

