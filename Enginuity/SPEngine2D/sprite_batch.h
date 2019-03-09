#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include <vector>

#include "vertex.h"

namespace SPEngine2D {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};
	
	struct Glyph
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint offset, GLuint num_vertices, GLuint texture) : offset(offset), num_vertices(num_vertices), texture(texture) {}
		GLuint offset;
		GLuint num_vertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sort_type = GlyphSortType::TEXTURE);
		void end();

		// dest_rect represents: 2 position coordinates and 2 destination coordinates.
		void draw(const glm::vec4& dest_rect, const glm::vec4& uv_rect, GLuint texture, float depth, const Color& color);
		void renderBatch();

	private:
		void createRenderBatches();

		// a vertex array is an array of vertices that will be rendered to the screen
		// instead of creating multiple vertices, binding, rendering, unbinding, etc.,
		// we can add them all to a vertex array and this can ALL be done in one call!
		void createVertexArray();

		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		// vertex buffer
		GLuint vbo;

		// vertex array
		GLuint vao;

		GlyphSortType sort_type;

		std::vector<Glyph*> glyphs;
		std::vector<RenderBatch> render_batches;
	};

}