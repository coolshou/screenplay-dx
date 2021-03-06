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

#include "JSSVGRectElement.h"

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedBoolean.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedString.h"
#include "JSSVGAnimatedTransformList.h"
#include "JSSVGElement.h"
#include "JSSVGMatrix.h"
#include "JSSVGRect.h"
#include "JSSVGStringList.h"
#include "KURL.h"
#include "SVGElement.h"
#include "SVGRectElement.h"
#include "SVGStringList.h"
#include <runtime/Error.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGRectElement);

/* Hash table */

static const HashTableValue JSSVGRectElementTableValues[19] =
{
    { "x", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementX), (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementY), (intptr_t)0 },
    { "width", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementWidth), (intptr_t)0 },
    { "height", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementHeight), (intptr_t)0 },
    { "rx", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementRx), (intptr_t)0 },
    { "ry", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementRy), (intptr_t)0 },
    { "requiredFeatures", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementRequiredFeatures), (intptr_t)0 },
    { "requiredExtensions", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementRequiredExtensions), (intptr_t)0 },
    { "systemLanguage", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementSystemLanguage), (intptr_t)0 },
    { "xmllang", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementXmllang), (intptr_t)setJSSVGRectElementXmllang },
    { "xmlspace", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementXmlspace), (intptr_t)setJSSVGRectElementXmlspace },
    { "externalResourcesRequired", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementExternalResourcesRequired), (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementClassName), (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementStyle), (intptr_t)0 },
    { "transform", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementTransform), (intptr_t)0 },
    { "nearestViewportElement", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementNearestViewportElement), (intptr_t)0 },
    { "farthestViewportElement", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementFarthestViewportElement), (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGRectElementConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGRectElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 8191, JSSVGRectElementTableValues, 0 };
#else
    { 69, 63, JSSVGRectElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGRectElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGRectElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGRectElementConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGRectElementConstructorTableValues, 0 };
#endif

class JSSVGRectElementConstructor : public DOMConstructorObject {
public:
    JSSVGRectElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGRectElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGRectElementPrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGRectElementConstructor::s_info = { "SVGRectElementConstructor", 0, &JSSVGRectElementConstructorTable, 0 };

bool JSSVGRectElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGRectElementConstructor, DOMObject>(exec, &JSSVGRectElementConstructorTable, this, propertyName, slot);
}

bool JSSVGRectElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGRectElementConstructor, DOMObject>(exec, &JSSVGRectElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGRectElementPrototypeTableValues[7] =
{
    { "hasExtension", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGRectElementPrototypeFunctionHasExtension), (intptr_t)1 },
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGRectElementPrototypeFunctionGetPresentationAttribute), (intptr_t)1 },
    { "getBBox", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGRectElementPrototypeFunctionGetBBox), (intptr_t)0 },
    { "getCTM", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGRectElementPrototypeFunctionGetCTM), (intptr_t)0 },
    { "getScreenCTM", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGRectElementPrototypeFunctionGetScreenCTM), (intptr_t)0 },
    { "getTransformToElement", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGRectElementPrototypeFunctionGetTransformToElement), (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGRectElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 2047, JSSVGRectElementPrototypeTableValues, 0 };
#else
    { 17, 15, JSSVGRectElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGRectElementPrototype::s_info = { "SVGRectElementPrototype", 0, &JSSVGRectElementPrototypeTable, 0 };

JSObject* JSSVGRectElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGRectElement>(exec, globalObject);
}

bool JSSVGRectElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGRectElementPrototypeTable, this, propertyName, slot);
}

bool JSSVGRectElementPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSSVGRectElementPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGRectElement::s_info = { "SVGRectElement", &JSSVGElement::s_info, &JSSVGRectElementTable, 0 };

JSSVGRectElement::JSSVGRectElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGRectElement> impl)
    : JSSVGElement(structure, globalObject, impl)
{
}

JSObject* JSSVGRectElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGRectElementPrototype(JSSVGRectElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGRectElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGRectElement, Base>(exec, &JSSVGRectElementTable, this, propertyName, slot);
}

bool JSSVGRectElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGRectElement, Base>(exec, &JSSVGRectElementTable, this, propertyName, descriptor);
}

JSValue jsSVGRectElementX(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->xAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementY(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->yAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementWidth(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->widthAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementHeight(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->heightAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementRx(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->rxAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementRy(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->ryAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementRequiredFeatures(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->requiredFeatures()), imp);
    return result;
}

JSValue jsSVGRectElementRequiredExtensions(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->requiredExtensions()), imp);
    return result;
}

JSValue jsSVGRectElementSystemLanguage(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->systemLanguage()), imp);
    return result;
}

JSValue jsSVGRectElementXmllang(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->xmllang());
    return result;
}

JSValue jsSVGRectElementXmlspace(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->xmlspace());
    return result;
}

JSValue jsSVGRectElementExternalResourcesRequired(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedBoolean> obj = imp->externalResourcesRequiredAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementClassName(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementStyle(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->style()));
    return result;
}

JSValue jsSVGRectElementTransform(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    RefPtr<SVGAnimatedTransformList> obj = imp->transformAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGRectElementNearestViewportElement(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->nearestViewportElement()));
    return result;
}

JSValue jsSVGRectElementFarthestViewportElement(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* castedThis = static_cast<JSSVGRectElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->farthestViewportElement()));
    return result;
}

JSValue jsSVGRectElementConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGRectElement* domObject = static_cast<JSSVGRectElement*>(asObject(slotBase));
    return JSSVGRectElement::getConstructor(exec, domObject->globalObject());
}
void JSSVGRectElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGRectElement, Base>(exec, propertyName, value, &JSSVGRectElementTable, this, slot);
}

void setJSSVGRectElementXmllang(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(thisObject);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());
    imp->setXmllang(value.toString(exec));
}

void setJSSVGRectElementXmlspace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(thisObject);
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());
    imp->setXmlspace(value.toString(exec));
}

JSValue JSSVGRectElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGRectElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsSVGRectElementPrototypeFunctionHasExtension(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGRectElement::s_info))
        return throwError(exec, TypeError);
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(asObject(thisValue));
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());
    const UString& extension = args.at(0).toString(exec);


    JSC::JSValue result = jsBoolean(imp->hasExtension(extension));
    return result;
}

JSValue JSC_HOST_CALL jsSVGRectElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGRectElement::s_info))
        return throwError(exec, TypeError);
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(asObject(thisValue));
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}

JSValue JSC_HOST_CALL jsSVGRectElementPrototypeFunctionGetBBox(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGRectElement::s_info))
        return throwError(exec, TypeError);
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(asObject(thisValue));
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<FloatRect>::create(imp->getBBox()).get(), 0 /* no context on purpose */);
    return result;
}

JSValue JSC_HOST_CALL jsSVGRectElementPrototypeFunctionGetCTM(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGRectElement::s_info))
        return throwError(exec, TypeError);
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(asObject(thisValue));
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<AffineTransform>::create(imp->getCTM()).get(), 0 /* no context on purpose */);
    return result;
}

JSValue JSC_HOST_CALL jsSVGRectElementPrototypeFunctionGetScreenCTM(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGRectElement::s_info))
        return throwError(exec, TypeError);
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(asObject(thisValue));
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<AffineTransform>::create(imp->getScreenCTM()).get(), 0 /* no context on purpose */);
    return result;
}

JSValue JSC_HOST_CALL jsSVGRectElementPrototypeFunctionGetTransformToElement(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGRectElement::s_info))
        return throwError(exec, TypeError);
    JSSVGRectElement* castedThisObj = static_cast<JSSVGRectElement*>(asObject(thisValue));
    SVGRectElement* imp = static_cast<SVGRectElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    SVGElement* element = toSVGElement(args.at(0));


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<AffineTransform>::create(imp->getTransformToElement(element, ec)).get(), 0 /* no context on purpose */);
    setDOMException(exec, ec);
    return result;
}


}

#endif // ENABLE(SVG)
