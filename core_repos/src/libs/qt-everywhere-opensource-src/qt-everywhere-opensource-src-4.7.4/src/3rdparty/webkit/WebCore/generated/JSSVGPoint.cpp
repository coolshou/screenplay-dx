/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(SVG)

#include "JSSVGPoint.h"

#include "JSSVGMatrix.h"
#include "JSSVGPoint.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPoint);

/* Hash table */

static const HashTableValue JSSVGPointTableValues[4] =
{
    { "x", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGPointX), (intptr_t)setJSSVGPointX },
    { "y", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGPointY), (intptr_t)setJSSVGPointY },
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGPointConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPointTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGPointTableValues, 0 };
#else
    { 9, 7, JSSVGPointTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGPointConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPointConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPointConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGPointConstructorTableValues, 0 };
#endif

class JSSVGPointConstructor : public DOMConstructorObject {
public:
    JSSVGPointConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGPointConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGPointPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSSVGPointConstructor::s_info = { "SVGPointConstructor", 0, &JSSVGPointConstructorTable, 0 };

bool JSSVGPointConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPointConstructor, DOMObject>(exec, &JSSVGPointConstructorTable, this, propertyName, slot);
}

bool JSSVGPointConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPointConstructor, DOMObject>(exec, &JSSVGPointConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGPointPrototypeTableValues[2] =
{
    { "matrixTransform", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointPrototypeFunctionMatrixTransform), (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPointPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPointPrototypeTableValues, 0 };
#else
    { 2, 1, JSSVGPointPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPointPrototype::s_info = { "SVGPointPrototype", 0, &JSSVGPointPrototypeTable, 0 };

JSObject* JSSVGPointPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPoint>(exec, globalObject);
}

bool JSSVGPointPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGPointPrototypeTable, this, propertyName, slot);
}

bool JSSVGPointPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSSVGPointPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGPoint::s_info = { "SVGPoint", 0, &JSSVGPointTable, 0 };

JSSVGPoint::JSSVGPoint(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<JSSVGPODTypeWrapper<FloatPoint> > impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSSVGPoint::~JSSVGPoint()
{
    forgetDOMObject(this, impl());
    JSSVGContextCache::forgetWrapper(this);
}

JSObject* JSSVGPoint::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPointPrototype(JSSVGPointPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGPoint::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPoint, Base>(exec, &JSSVGPointTable, this, propertyName, slot);
}

bool JSSVGPoint::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPoint, Base>(exec, &JSSVGPointTable, this, propertyName, descriptor);
}

JSValue jsSVGPointX(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGPoint* castedThis = static_cast<JSSVGPoint*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    FloatPoint imp(*castedThis->impl());
    JSValue result =  jsNumber(exec, imp.x());
    return result;
}

JSValue jsSVGPointY(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGPoint* castedThis = static_cast<JSSVGPoint*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    FloatPoint imp(*castedThis->impl());
    JSValue result =  jsNumber(exec, imp.y());
    return result;
}

JSValue jsSVGPointConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGPoint* domObject = static_cast<JSSVGPoint*>(asObject(slotBase));
    return JSSVGPoint::getConstructor(exec, domObject->globalObject());
}
void JSSVGPoint::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPoint, Base>(exec, propertyName, value, &JSSVGPointTable, this, slot);
}

void setJSSVGPointX(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPoint* castedThisObj = static_cast<JSSVGPoint*>(thisObject);
    JSSVGPODTypeWrapper<FloatPoint> * imp = static_cast<JSSVGPODTypeWrapper<FloatPoint> *>(castedThisObj->impl());
    FloatPoint podImp(*imp);
    podImp.setX(value.toFloat(exec));
    imp->commitChange(podImp, castedThisObj);
}

void setJSSVGPointY(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPoint* castedThisObj = static_cast<JSSVGPoint*>(thisObject);
    JSSVGPODTypeWrapper<FloatPoint> * imp = static_cast<JSSVGPODTypeWrapper<FloatPoint> *>(castedThisObj->impl());
    FloatPoint podImp(*imp);
    podImp.setY(value.toFloat(exec));
    imp->commitChange(podImp, castedThisObj);
}

JSValue JSSVGPoint::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGPointConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsSVGPointPrototypeFunctionMatrixTransform(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGPoint::s_info))
        return throwError(exec, TypeError);
    JSSVGPoint* castedThisObj = static_cast<JSSVGPoint*>(asObject(thisValue));
    JSSVGPODTypeWrapper<FloatPoint> * imp = static_cast<JSSVGPODTypeWrapper<FloatPoint> *>(castedThisObj->impl());
    FloatPoint podImp(*imp);
    AffineTransform matrix = toSVGMatrix(args.at(0));


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<FloatPoint>::create(podImp.matrixTransform(matrix)).get(), 0 /* no context on purpose */);
    imp->commitChange(podImp, castedThisObj);
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, JSSVGPODTypeWrapper<FloatPoint>* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGPoint, JSSVGPODTypeWrapper<FloatPoint> >(exec, globalObject, object, context);
}
FloatPoint toSVGPoint(JSC::JSValue value)
{
    return value.inherits(&JSSVGPoint::s_info) ? (FloatPoint) *static_cast<JSSVGPoint*>(asObject(value))->impl() : FloatPoint();
}

}

#endif // ENABLE(SVG)
