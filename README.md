
# Chroma Engine
A 2D Game Engine made with C++, SDL and a custom written OpenGL Renderer.

The Goal is to provide base functionality for Games to build upon.
The Code is structured to be work as modules to create reusability for Projects.

## Documentation
A rough Overview of how the Library works and how to use it
A more detailed Documentation can be found in the docs directory.

### ECS
*What is an Entity-Component-System?*

To represent Entities with different Behaviours and Data in Games one Architecture
to achieve this is an ECS.

Here the *Entity* represents a thing that lives in the World.
In the Chroma Engine an Entity is just a typedef for an Integer ID.

A *Component* is some form of Data which is (often) used in combination with other Components by the *System* to perform an Action or do other stuff with this Data.

In the Chroma Engine each *System* and each *Entity* has a *Signature* which in our Case is just a Bitset that represents the Components an Entity has or a System requires.

*How do you use the ECS in Chroma?*

The Chroma ECS uses 3 different "Manager" which get bundled into one Singleton that is called "ECS.h". Before explaining how to use it I will explain its Structure.

Each Manager has a single Responsibility and is not meant to be used directly but rather in through the ECS Singleton. The Managers Tasks are as following:

#### Entity Manager
- Manages the Entity Lifetime as well as their Signature
- Provides information about the Amount of Entities in the current Scene
- Provides information about the Signature of each Entity
    - The Signatures are stored in an Array where the Index corresponds to the Entity ID

#### Component Manager
- Manages Component Registration as well as their Lifetime on the Entity.
- Provides information about the Components, their Type and what Entity they belong to.
- Provides and uses a custom data Structure called the *ComponentArray* to store Component Pointer in an Array that is packed(Has no invalid Data caused by Entity Destruction or Component Removal).

#### System Manager
- Manages System Registration as well as their Signature
- Updates all Systems intern Entity Set when an Entity Signature changes

#### ECS
- Combines all 3 aforementioned Manager and provide all ECS related functionalities.
- SHOULD be used when working with the ECS instead of using Managers by themselve!!!
- Is a Singleton
- Manages Manager Lifetime
## Authors

- [@leonschultz](https://github.com/ProdByTENSHI)

## Acknowledgements

- [SDL 2 Library](https://www.libsdl.org/)
