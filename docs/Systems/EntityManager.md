# Entity Manager

This is a system of [UWU Engine](../../README.md)

This is part of our data oriented ECS engine implementation. The entity manager stores all the entity ID and type information. It also manages the life time of all entities.

All component managers need to communicate with entity manager for indexing into it's corresponding container. The entity manager is also responsible for signaling all component managers when an entity gets destroyed. 
