#includes

class Cube {
	public:
	 void draw(vec3 position);
	 virtual void vertexs();
	 virtual void elements();
	 
	 GLfloat vertex_buffer[];
     GLuint element_buffer[];
     GLfloat colour_buffer[];
	private:
	  //Unsure atm if there are any private
};