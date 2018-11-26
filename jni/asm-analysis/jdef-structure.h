
/**
 * The ASM Analysis module classes structure.
 * This contains jdef, which declares all things in java, like
 * class type, local variables, and etc.
 */


#ifndef _ASM_ANALYSIS_CORE_STRUCTURE
#define _ASM_ANALYSIS_CORE_STRUCTURE


#include "basedef.cpp"


ASM_BEGIN_NAMESPACE

namespace jdef {
	// The root class of the jtype structure.
	class jtype; // abs
		
		// The base interface of all data types.
		class jdata; // abs
		
			// all reference types.
			class jref; // abs
			
				// object. Java: Object(* extends java/lang/Object or all interfaces)
				class jobject;
				
				// array. [TYPE
				class jarray;
				
				// const jref jnull;
			
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
					class jexactptr; // abs
					
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
			class jdefine; // abs
					
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
			
			// containing informations about its classes
			class jpackage;
		
		// end jannotated
		
		// A single annotation data.
		// = @Annotation(name = value, ..)
		class jannotation;
		
		// A code with specific value.
		class jexpr;
		
	
	// end jtype
}


ASM_END_NAMESPACE



#endif
