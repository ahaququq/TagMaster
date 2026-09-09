# TagMaster
# An advanced Object Oriented data moddeling system

`class` is a definition of simple objects, like items, blocks, entities, weapons, armour, biomes, etc. A class consists of a set of fields and attributes, which can have assigned default values, or be left for assignment during object construction. If a class does not leave out any property values, it can be used as an object (If all properties have values, construction can be ommited).

`property` can be named (field) or unnamed (attribute), and stores information about the object it's a part of. Named properties can be defined in classes, and store information related to their name (`position` stores a position), while unnamed properties store information related to their type (`BurnTime` stores the time something would burn), sometimes just the existance of it can be the information (`SurvivesExplosion` will survive explosions).
Properties have a type (class for named, attribute for unnamed), which defines what they need to store, and can accept subclasses of that type - `Item` property can accept `ToolItem`s and other `Item` subclasses.

`field` is a named property, like `name`, `position`, `age`, etc. Fields are meant for attributes specific to that class and it's subclasses.

`attribute` (tag) is an unnamed property - definition of an appendable object attribute, like fireproof, floatsInWater, turnedByLightningInto(). An Attribute class can have exactly the same properties as a regurlar class, and some extras. 
Attributes can be limited to a set of class hierarchies (`DisappearsInWater` can be limited to subclasses of `Item`).
Amount of definitions of an attribute can also be chosen:
 * Single subclass - There can be only one tag from the class hierarchy, if there is one tag on the object that implements the limiting class, any attempt to add more will cause an error.
 * Single class - There can be only one tag constructed directly from the limiting class, but there can be others from subclasses.
 * Multiple - There can be more than one tag of that type


### No AI has been used in creating this document