#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");

}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	// Remove all tilesets


	map_file.reset();

	return true;
}

bool j1Map::LoadMapStruct()
{
	pugi::xml_node map_node = map_file.child("map");

	map_info.version = map_node.attribute("version").as_float();
	map_info.height = map_node.attribute("height").as_uint();
	map_info.width = map_node.attribute("width").as_uint();
	map_info.tileheight = map_node.attribute("tileheight").as_uint();
	map_info.tilewidth = map_node.attribute("tilewidth").as_uint();

	switch (map_node.attribute("orientation").as_uint)
	{
		case ORTHOGONAL map_info.orientation = ORTHOGONAL;
	}
	if (map_node.attribute("renderorder").as_string == "right-down")
	{
		map_info.renderorder = RIGHT_DOWN;
	}

		
	
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		LoadMapStruct();
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	// TODO 5: LOG all the data loaded
	// iterate all tilesets and LOG everything

	map_loaded = ret;

	return ret;
}

