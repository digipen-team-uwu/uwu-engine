# Sound Interface

The sound interface is a system in [UWU Engine](../../README.md)

The sound interface uses FMOD Core API. It loads sound and music assets from data/sounds.json and store them in a map with sound name as key and the actual sound as value. 

To play a sound you just call the playSound function and provide the sound name and a boolean indicating whether  it's looping or not.
