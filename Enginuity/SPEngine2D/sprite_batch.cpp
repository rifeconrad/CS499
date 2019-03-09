#include "sprite_batch.h"

#include <algorithm>

namespace SPEngine2D {

	SpriteBatch::SpriteBatch() : vbo(0), vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::init()
	{
		this->createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sort_type /*= GlyphSortType::TEXTURE*/)
	{
		this->sort_type = sort_type;
		this->render_batches.clear();

		for (int i = 0; i < this->glyphs.size(); i++)
			delete this->glyphs[i];

		this->glyphs.clear();
	}

	void SpriteBatch::end()
	{
		this->sortGlyphs();
		this->createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4 & dest_rect, const glm::vec4 & uv_rect, GLuint texture, float depth, const Color & color)
	{
		Glyph* new_glyph = new Glyph();

		new_glyph->texture = texture;
		new_glyph->depth = depth;

		new_glyph->topLeft.color = color;
		new_glyph->topLeft.setPosition(dest_rect.x, dest_rect.y + dest_rect.w);
		new_glyph->topLeft.setUV(uv_rect.x, uv_rect.y + uv_rect.w);

		new_glyph->bottomLeft.color = color;
		new_glyph->bottomLeft.setPosition(dest_rect.x, dest_rect.y);
		new_glyph->bottomLeft.setUV(uv_rect.x, uv_rect.y);

		new_glyph->bottomRight.color = color;
		new_glyph->bottomRight.setPosition(dest_rect.x + dest_rect.z, dest_rect.y);
		new_glyph->bottomRight.setUV(uv_rect.x + uv_rect.z, uv_rect.y);

		new_glyph->topRight.color = color;
		new_glyph->topRight.setPosition(dest_rect.x + dest_rect.z, dest_rect.y + dest_rect.w);
		new_glyph->topRight.setUV(uv_rect.x + uv_rect.z, uv_rect.y + uv_rect.w);

		this->glyphs.push_back(new_glyph);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(this->vao);

		for (int i = 0; i < this->render_batches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, this->render_batches[i].texture);
			glDrawArrays(GL_TRIANGLES, this->render_batches[i].offset, this->render_batches[i].num_vertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		// set size of this vector for six vertices
		vertices.resize(this->glyphs.size() * 6);

		if (this->glyphs.empty())
			return;

		int offset = 0;
		int curr_vertex = 0;
		// emplace_back accepts the object's parameters, creates the objects parameters, AND pushes the object onto the vector automatically!
		this->render_batches.emplace_back(offset, 6, this->glyphs[0]->texture);
		vertices[curr_vertex++] = this->glyphs[0]->topLeft;     // v1
		vertices[curr_vertex++] = this->glyphs[0]->bottomLeft;  // v2
		vertices[curr_vertex++] = this->glyphs[0]->bottomRight; // v3
		vertices[curr_vertex++] = this->glyphs[0]->bottomRight; // v4
		vertices[curr_vertex++] = this->glyphs[0]->topRight;    // v5
		vertices[curr_vertex++] = this->glyphs[0]->topLeft;     // v6
		offset += 6;

		/* v1, v2, and v3 represent the first triangle. v4, v5, and v6 represent the second triangle.
		(v1)(v6)             (v5)             
		     _______________
			|				|
			|				|
			|				|
			|				|
			|				|
			-----------------
		(v2)               (v3)(v4)
		*/

		for (int curr_glyph = 1; curr_glyph < this->glyphs.size(); curr_glyph++)
		{
			// only emplace if the current texture is different than the previous
			if (this->glyphs[curr_glyph]->texture != this->glyphs[curr_glyph - 1]->texture)
				this->render_batches.emplace_back(offset, 6, this->glyphs[0]->texture);
			else
				this->render_batches.back().num_vertices += 6;

			vertices[curr_vertex++] = this->glyphs[curr_glyph]->topLeft;     // v1
			vertices[curr_vertex++] = this->glyphs[curr_glyph]->bottomLeft;  // v2
			vertices[curr_vertex++] = this->glyphs[curr_glyph]->bottomRight; // v3
			vertices[curr_vertex++] = this->glyphs[curr_glyph]->bottomRight; // v4
			vertices[curr_vertex++] = this->glyphs[curr_glyph]->topRight;    // v5
			vertices[curr_vertex++] = this->glyphs[curr_glyph]->topLeft;     // v6
			offset += 6;
		}

		// bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (vao == 0)
			glGenVertexArrays(1, &this->vao);

		// anytime we bind vao (after the initializing) it will enable everything for us, 
		// so we don't have to make all of the expensive calls!
		glBindVertexArray(this->vao);

		if (vbo == 0)
			glGenBuffers(1, &this->vbo);

		//---------------------------------------------------------------------
		// ALL OF THE ENCLOSED CODE IS AUTOMATICALLY DONE WHEN THE VERTEX
		// ARRAY IS BOUND! (AFTER THE INITIALIZATION)
		//---------------------------------------------------------------------

		// anytime we rebind vertex attrib array it will automatically bind this buffer!
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		// we only want one attribute array right now (position), later we can add more for lighting, etc.
		// 0 indicates the 0th position of the attribute array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// this is the position attribute pointer!
		// tell opengl where our vertex data is in the vertex buffer ID
		// 0 - 0th position of array
		// 2 - (stands for x and y coordinate)
		// GL_FLOAT - tells it we will be using float
		// GL_FALSE - says we don't want to normalize
		// 0 - stride - size of the vertex struct
		// offsetof(...) - byte offset of struct (since position is at the beginning of the struct, this will return 0) 
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// this is the color attribute pointer
		// 1 - color is the second index in our shader
		// 4 - the number of bytes involved
		// GL_UNSIGNED_BYTES - the data type is unsigned bytes
		// GL_TRUE - we want to normalize (for color, it converts our 0-255 to between 0 and 1)
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		// UV attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//---------------------------------------------------------------------
		// ALL OF THE ENCLOSED CODE IS AUTOMATICALLY UNDONE WHEN THE VERTEX
		// ARRAY IS UNBOUND! (WHEN glBindVertexArray is passed 0)
		//---------------------------------------------------------------------

		// disables all enables and unbinds the vertex buffer!
		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (this->sort_type)
		{
		case GlyphSortType::BACK_TO_FRONT:
			// sorts the data, but if two of the objects are equal, then their position 
			// for each will remain the same
			std::stable_sort(this->glyphs.begin(), this->glyphs.end(), this->compareFrontToBack);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			// sorts the data, but if two of the objects are equal, then their position 
			// for each will remain the same
			std::stable_sort(this->glyphs.begin(), this->glyphs.end(), this->compareFrontToBack);
			break; 
		case GlyphSortType::TEXTURE:
			// sorts the data, but if two of the objects are equal, then their position 
			// for each will remain the same
			std::stable_sort(this->glyphs.begin(), this->glyphs.end(), this->compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}

}