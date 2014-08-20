// For conditions of distribution and use, see copyright notice in License.txt

#pragma once

#include "../Base/HashMap.h"

namespace Turso3D
{

class Attribute;
class Serializable;
struct ObjectRef;

/// Stored object ref attribute.
struct TURSO3D_API StoredObjectRef
{
    /// Construct undefined.
    StoredObjectRef() :
        object(0),
        attr(0),
        oldId(0)
    {
    }

    /// Construct with values.
    StoredObjectRef(Serializable* object_, Attribute* attr_, unsigned oldId_) :
        object(object_),
        attr(attr_),
        oldId(oldId_)
    {
    }

    /// %Object that contains the attribute.
    Serializable* object;
    /// Description of the object ref attribute.
    Attribute* attr;
    /// Old id from the serialized data.
    unsigned oldId;
};

/// Helper class for resolving object ref attributes when loading a scene.
class TURSO3D_API ObjectResolver
{
public:
    /// Store an object along with its old id from the serialized data.
    void StoreObject(unsigned oldId, Serializable* object);
    /// Store an object ref attribute that needs to be resolved later.
    void StoreObjectRef(Serializable* object, Attribute* attr, const ObjectRef& value);
    /// Resolve the object ref attributes.
    void Resolve();

private:
    /// Mapping of old id's to objects.
    HashMap<unsigned, Serializable*> objects;
    /// Stored object ref attributes.
    Vector<StoredObjectRef> objectRefs;
};

}
