# Collider

The collider component is a component of [uwu Engine](../../README.md).

There are four different kinds of colliders
- Point
- Line
- Circle
- Polygon
- Rectangle (Polygon)

The collision system is implemented with Separating Axis Theorem which supports collision detections in between any convex shape.

Collision detection returns a collision manifold which includes the two entity ids that are colliding, the collision angle and depth. With will be sent and handled by collision resolution and according behavioral resolution.
