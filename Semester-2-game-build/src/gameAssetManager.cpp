#include "gameAssetManager.h"

/**
* Creates a GameAssetManager to load the correct shaders based on the
* ApplicationMode.
*/

GameAssetManager::GameAssetManager() {
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("shaders/vertex.vs", "shaders/fragment.fs");
}

/**
* Deletes the programID, the pointer to the shaders
*/
GameAssetManager::~GameAssetManager() {
	glDeleteProgram(programID);
}

/**
* Adds a GameAsset to the scene graph.
*/
void GameAssetManager::AddAsset(std::shared_ptr<GameAsset> the_asset) {
	draw_list.push_back(the_asset);
}

/**
* Draws each GameAsset in the scene graph.
*/
void GameAssetManager::Draw() {
	for(auto ga: draw_list) {
		ga->Draw(programID, player);
	} 
}

/**
* Changes the vec3 of an asset, transitioning it
*/
void GameAssetManager::Move(int num, glm::vec3 pos) {
    draw_list.at(num)->NewPosition(pos);
}

/**
* Checks if two objects are colliding
*/
bool GameAssetManager::Collision(int n1, const shared_ptr<Bounding> b) {
    return draw_list.at(n1)->Collides(b);
}

/**
* Empties the draw vector, allowing for the next levels cubes to load
*/
void GameAssetManager::Clear() {
	draw_list.clear();
}

/**
* Follows an algorithm which makes the diamond shy away from the player, causing
* it to retreat in the opposite direction of the player.
*@bug some of the diamonds do not work as intended, some will flee as intended others will not
*/
void GameAssetManager::Intelligence(int cubes, int diamonds) {
	bool move = false;
	glm::vec3 p = player.GetPos();
	for(int i = diamonds; i != 0; i--)
	{
		// Add one to diamonds for the door asset
		int n1 = Size()-i;
		glm::vec3 d = draw_list.at(n1)->GetPos();
	
		if(p.x >= d.x - 3 && p.x <= d.x && p.z >= d.z - 3 && p.z <= d.z)
		{
			for(int y = 0; y < cubes; y++) 
			{
// This loop makes sure that the diamond is colliding with a cube, before moving
				move = Collision(y, draw_list.at(n1)->GetBox());
				if(move == true)
					y = cubes;
			}		
			if(move == true)
	 		{
				d.x = p.x + 2.0;
				d.z = p.z + 2.0;
				Move(n1,d);
			}
		}
		else if(p.x <= d.x + 3 && p.x >= d.x && p.z <= d.z + 3 && p.z >= d.z)
		{
			for(int y = 0; y < cubes; y++) 
			{
// This loop makes sure that the diamond is colliding with a cube, before moving
				move = Collision(y, draw_list.at(n1)->GetBox());
				if(move == true)
					y = cubes;
			}	
			if(move == true)
	 		{
				d.x = p.x - 2.0;
				d.z = p.z - 2.0;
				Move(n1,d);
			}
		}
	 }
}

/**
* Removes an asset from the list
*/
void GameAssetManager::Remove(int num) {
    draw_list.erase(draw_list.begin() + num); // Removes an object from vector
}

/**
* Returns the size of the vector
*/
int GameAssetManager::Size()  {
	return (draw_list.size()-1);
}

/**
* Reads in the shaders, to produce a ProgramID which points to the linked location
*/
GLuint GameAssetManager::LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
	
	/// Read the Vertex Shader code from the file
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	/// Read the Fragment Shader code from the file
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	/// Compile Vertex Shader
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	/// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	/// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
