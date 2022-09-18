#include <gazebo/gazebo.hh>

namespace gazebo
{
	class GreetUserPlugin : public WorldPlugin
	{
		public: GreetUserPlugin() : WorldPlugin()
		{
			printf("Welcome to Aditya's World\n");	
		}
		public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf){}
	};
	GZ_REGISTER_WORLD_PLUGIN(GreetUserPlugin)
}
