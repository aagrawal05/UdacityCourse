Localization:
The robot uses the AMCL algorithm to estimate its pose by simulating a number of randomly generated particles and assiging weigths to each particle based on their likelihood and eliminating infeasible particles. Eventually the majority of higher weighted particles should converge on the Robot's real pose.

Mapping:
For mapping, the robot uses a SLAM algorithm (more specifically the GraphSLAM algorithm explored previsouly) to simulateously traverse and store it's environment. It does so by taking reading with its attached lidar sensor and forming a graph of constraints between all of the possible landmarks. By resolving this graph we can form the map as well as the robots relative position inside the map.

Navigation:
In order to calculate a trajectory on the map, the robot finds a path using Djikstra's graph search algorithm to efficiently compute the discretized map. It does so by recursively traversing the map tree assuming each traversal/step to get to the target node has a uniform time cost. It employs a greedy algorithm that chooses the fastest looking node to explore at every step and finds a set of state transistions that allows the robot to move from it's initial pose to the target one.


Home Service Robot:
In order to approach this task, I decided to allow communication between the `home_service_goal_node` and the `home_service_marker_node` to check when the goals have been met. To do so, the `home_service_goal_node` publishes a `state_update` topic that the `home_service_marker_node` subseqeuntly subscribes to. The topic itself only serves as to allow for the two nodes to converse when the state of the `home_service_goal_node` updates. As such the message type used is `std_msgs::Empty` as there is no information that needs to be published. The message is sent twice from the `home_service_goal_node`: Once, before waiting the 5 seconds to simulate picking up the object, to signal the deletion of the `pickup` marker and again after the 5 seconds to request the publishing of the `delivery` marker. The `home_service_marker_node` updates a state variable that starts at 0 and increments each time the message is recieved and changes the marker data being published to delete/add the marker respectively (when state is 1 to once that means that pickup has begun and thus the pickup marker should be deleted, and when state is 2 pickup is ended and we should post the new `delivery` marker)

Another approach that is perhaps more efficient could be to use ros parameter that shares the state as a variable between the two in topic.
