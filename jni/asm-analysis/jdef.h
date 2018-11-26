#ifndef _ASM_ANALYSIS_CORE_H
#define _ASM_ANALYSIS_CORE_H

#include "basedef.cpp"
#include "utils.h"
#include "jdef-structure.h"



ASM_BEGIN_NAMESPACE


namespace jdef {
	
	
	
	
	
	namespace _types {
		// 	ref->[0x10? array|object]	[0x8? ref|prim]	data		: 0x0
		// 	prim->[x9:4b, 0x10~]
		//	[0x8?local|generics]						ptr			: 0x1
		// 	generics->[0x10~c2:method|field|class]
		// 		class->[0x40~:nexact|unknown|exact(real|templete)]
		// 												annotated	: 0x2
		// 												annotation	: 0x3
		// 												expr		: 0x4 ~ 0x7(3b)
		
		// _(underslash) with abstract classes
		constexpr flag_t _jdata = 0x0;
			constexpr flag_t _jref = _jdata | 0x8;
				constexpr flag_t jobject = _jref;
				constexpr flag_t jarray = _jref | 0x10;
				constexpr flag_t jnull = _jref | 0x20;
			constexpr flag_t _jprimitive = _jdata;
				constexpr flag_t jvoid = _jprimitive;
				constexpr flag_t jboolean = _jprimitive | (0x1 << 4);
				constexpr flag_t jbyte = _jprimitive | (0x2 << 4);
				constexpr flag_t jshort = _jprimitive | (0x3 << 4);
				constexpr flag_t jchar = _jprimitive | (0x4 << 4);
				constexpr flag_t jint = _jprimitive | (0x5 << 4);
				constexpr flag_t jfloat = _jprimitive | (0x6 << 4);
				constexpr flag_t jlong = _jprimitive | (0x7 << 4);
				constexpr flag_t jdouble = _jprimitive | (0x8 << 4);
		constexpr flag_t _jptr = 0x1;
			constexpr flag_t jlocalptr = _jptr;
			constexpr flag_t _jgenerics = _jptr | 0x8;
				constexpr flag_t jmethodptr = _jgenerics;
				constexpr flag_t jfieldptr = _jgenerics | 0x10;
				constexpr flag_t _jclassptr = _jgenerics | 0x20;
					constexpr flag_t jnexactptr = _jclassptr;
					constexpr flag_t junknownptr = _jclassptr | (0x1 << 4);
					constexpr flag_t _jexactptr = _jclassptr | (0x2 << 4);
						constexpr flag_t jrealptr = _jexactptr;
						constexpr flag_t jtemplete = _jexactptr | (0x1 << 6);
		constexpr flag_t _jannotated = 0x2;
			constexpr flag_t jcode = _jannotated;
			constexpr flag_t _jcodes = _jannotated | (0x1 << 3);
				constexpr flag_t jcodeblock = _jcodes;
				constexpr flag_t joptcodeblock = _jcodes | 0x10;
			constexpr flag_t _jdefine = _jannotated | (0x2 << 3);
				constexpr flag_t jclass = _jdefine;
				constexpr flag_t jmethod = _jdefine | (0x1 << 5);
				constexpr flag_t jfield = _jdefine | (0x2 << 5);
				constexpr flag_t jlocal = _jdefine | (0x3 << 5);
		constexpr flag_t jannotation = 0x3;
		constexpr flag_t jexpr = 0x4;
	}
	
	
	// jtype define
	
	class jtype
	{
		public:
		virtual flag_t id() = 0;
		virtual void code(StringBuilder& sb) = 0;
		virtual void str(StringBuilder& sb) {}
	};
	
	
	class jdata : public jtype
	{
		public:
		virtual jclassptr* type() = 0;
	};
	
	
	class jref : public jdata
	{
		public:
	};
	
	
	class jobject : public jref
	{
		public:
		jobject(jclassptr* type, jdata** fields);
		~jobject();
		
		jdata** fields();
		jdata* field(jint index);
		jint fieldCount();
		// helper
		jdata* field(char* name);
		
		bool isPrimitiveWrapper();
		jprimitive* asPrimitive();
		
		bool isInstanceof(jclass* obj); // = obj instanceof [thisClass]
		
		// inherited from jdata
		override jclassptr* type();
		
		// inherited from jtype
		override inline flag_t id() {
			 return _types::jobject;
		}
		
		override void code(StringBuilder& sb) unsupported;
		override void str(StringBuilder& sb) unsupported;
		
		private:
		jclassptr* mType;
		jdata** mFields;
	};
	
	
	class jarray : public jref
	{
		public:
		jdata* list();
		jdata** list(jint index);
		jint count();
		
		jclassptr** componentType();
		
		// inherited from jdata
		override jclassptr& type();
		
		// inherited from jtype
		override flag_t id() {
			return _types::jarray;
		}
		override void code(StringBuilder& sb);
		override void str(StringBuilder& sb);
		
		
		private:
		jclassptr& mType;
		jdata*& mArray;
	};
	
	
	const class {
		// inherited from jdata
		override jclassptr& type() {
			return ;
		}
		
		// inherited from jtype
		override flag_t id() {
			return _types::jnull;
		}
		override void code(StringBuilder& sb) {
			sb.append("null");
		}
		
		override void str(StringBuilder& sb) {
			sb.append("null");
		}
	} jnull;
	
	
	class jprimitive : public jdata
	{
		
	};
	
	
	/*		// const jref jnull;
			
			// primitive types. int, short, byte, ...
			class jprimitive; // abs
			
				//class jboolean;
				//class j
		
		// Points the specific class, method, field, or variable.
		class jptr; // abs
			
			// Points jlocal.
			// [location: jcodelocation] -> [type: jclassptr] [name: char*]
			class jlocalPtr;
		
			// all pointers which has generic types.
			// Class<T>, <T> ret method(..), Type<T> field
			class jgenerics; // abs
			
				// Points some class.
				// [name: char*]<[generics..: jclassptr*]>
				class jclassptr; // abs
					
					// Points some exact jlclass.
					class jexactptr;
					
						// Points real jclass.
						class jrealptr;
						
						// templete type.
						// jclassptr fromClass
						class jtemplete;
					
					// Knows some information about class,
					// but it is not exact
					class jnexactptr;
					
					// Not know any information about type
					class junknownptr;
				
				// Points jmethod.
				// [fromClass: jclassptr] -> [ret: jclassptr] [name: char*]([args: jclassptr*]);
				class jmethodptr;
				
				// Points jfield.
				// [fromClass: jclassptr] -> [type: jclassptr] [name: char*];
				class jfieldptr;
			
		// All things which are annotated.
		// Data: annotations
		class jannotated; // abs
		
			// A code which can be seperated by ';', or end of
			// jcodeblock, class, or etc.
			class jcode;
			
			// Code list.
			class jcodes;  // abs
				
				// A code block which is surrounded by {}.
				// Used in method.
				class jcodeblock;
				
				// A code block.
				// Different from jcodeblock, can be surrounded by {}
				// or not surrounded.
				// Used in control flow: for, while, do .. while or etc.
				class joptcodeblock;
			
			// Some declarations on the code.
			// This also has modifier.
			class jdefine;
					
				// Class declaration.
				// MD -> | [class, enum, interface, abstract class]
				// Data: extends, implements, methods(containing <cinit>), fields,
				// 		 extends/implements generic types, jclassptr(core data), 
				// 		 member classes
				class jclass;
				
				// Method declaration.
				// Data: parent, jmethodptr(core data), jcodeblock
				class jmethod;
				
				// Field declaration.
				// Data: parent, jfieldptr, initValue
				class jfield;
				
				// Local variable declaration.
				// Data: jlocalptr(core data), initValue;
				class jlocal;
			
			class jpackage;
		
		// end jannotated
		
		// A single annotation data.
		// = @Annotation(name = value, ..)
		class jannotation;
		
		// A code with specific value.
		class jexpr;
		
	*/
}

ASM_END_NAMESPACE


#endif
