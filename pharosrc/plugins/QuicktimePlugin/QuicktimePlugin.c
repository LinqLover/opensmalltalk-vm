/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker.oscog-eem.1950 uuid: b4089b49-1494-49d2-8966-57cba5c92194
   from
	QuicktimePlugin VMMaker.oscog-eem.1950 uuid: b4089b49-1494-49d2-8966-57cba5c92194
 */
static char __buildInfo[] = "QuicktimePlugin VMMaker.oscog-eem.1950 uuid: b4089b49-1494-49d2-8966-57cba5c92194 " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
#include "sqConfig.h"			/* Configuration options */
#include "sqVirtualMachine.h"	/*  The virtual machine proxy definition */
#include "sqPlatformSpecific.h"	/* Platform specific definitions */

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
# undef EXPORT
# define EXPORT(returnType) static returnType
#endif

#include "QuicktimePlugin.h"
#include "sqMemoryAccess.h"


/*** Function Prototypes ***/
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) initialiseModule(void);
EXPORT(sqInt) moduleUnloaded(char *aModuleName);
EXPORT(sqInt) primitiveClearFrameCompletedSemaphore(void);
EXPORT(sqInt) primitiveDestroyHandle(void);
EXPORT(sqInt) primitiveDestroySurface(void);
EXPORT(sqInt) primitiveSetFrameCompletedSemaphore(void);
EXPORT(sqInt) primitiveSetGWorldPtrOntoExistingSurface(void);
EXPORT(sqInt) primitiveSetGWorldPtrOntoSurface(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
static sqInt sqAssert(sqInt aBool);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*failed)(void);
static sqInt (*integerObjectOf)(sqInt value);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static unsigned long (*positiveMachineIntegerValueOf)(sqInt oop);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt failed(void);
extern sqInt integerObjectOf(sqInt value);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern unsigned long positiveMachineIntegerValueOf(sqInt oop);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"QuicktimePlugin VMMaker.oscog-eem.1950 (i)"
#else
	"QuicktimePlugin VMMaker.oscog-eem.1950 (e)"
#endif
;



/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

	/* QuicktimePlugin>>#initialiseModule */
EXPORT(sqInt)
initialiseModule(void)
{
	return sqQuicktimeInitialize();
}


/*	The module with the given name was just unloaded. 
	Make sure we have no dangling references. */

	/* QuicktimePlugin>>#moduleUnloaded: */
EXPORT(sqInt)
moduleUnloaded(char *aModuleName)
{
	if ((strcmp(aModuleName, "QuicktimePlugin")) == 0) {
		sqQuicktimeShutdown();
	}
	return 0;
}

	/* QuicktimePlugin>>#primitiveClearFrameCompletedSemaphore: */
EXPORT(sqInt)
primitiveClearFrameCompletedSemaphore(void)
{
	sqInt data;

	data = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	stQuicktimeClearSemaphore(data);
	return null;
}

	/* QuicktimePlugin>>#primitiveDestroyHandle: */
EXPORT(sqInt)
primitiveDestroyHandle(void)
{
	sqInt data;

	data = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	stQuicktimeDestroy(data);
	return null;
}

	/* QuicktimePlugin>>#primitiveDestroySurface: */
EXPORT(sqInt)
primitiveDestroySurface(void)
{
	sqInt data;

	data = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	stQuicktimeDestroySurface(data);
	return null;
}

	/* QuicktimePlugin>>#primitiveSetFrameCompletedSemaphore:for: */
EXPORT(sqInt)
primitiveSetFrameCompletedSemaphore(void)
{
	sqInt data;
	sqInt semaIndex;

	semaIndex = stackIntegerValue(1);
	data = stackIntegerValue(0);
	if (failed()) {
		return null;
	}
	stQuicktimeSetSemaphorefor(semaIndex, data);
	return null;
}

	/* QuicktimePlugin>>#primitiveSetGWorldPtrOntoExistingSurface:gWorld:width:height:rowBytes:depth:movie: */
EXPORT(sqInt)
primitiveSetGWorldPtrOntoExistingSurface(void)
{
	sqInt bitMapPtr;
	char *buffer;
	sqInt depth;
	sqInt height;
	long movie;
	sqInt moviePtr;
	sqInt rowBytes;
	sqInt surfaceID;
	sqInt width;

	surfaceID = stackIntegerValue(6);
	bitMapPtr = stackValue(5);
	width = stackIntegerValue(4);
	height = stackIntegerValue(3);
	rowBytes = stackIntegerValue(2);
	depth = stackIntegerValue(1);
	moviePtr = stackValue(0);
	if (failed()) {
		return null;
	}
	buffer = ((char *) (positiveMachineIntegerValueOf(bitMapPtr)));
	movie = ((long) (positiveMachineIntegerValueOf(moviePtr)));
	stQuicktimeSetToExistingSurfacegworldwidthheightrowBytesdepthmovie(surfaceID, buffer, width, height, rowBytes, depth, movie);
	if (failed()) {
		return null;
	}
	pop(7);
	return null;
}

	/* QuicktimePlugin>>#primitiveSetGWorldPtrOntoSurface:width:height:rowBytes:depth:movie: */
EXPORT(sqInt)
primitiveSetGWorldPtrOntoSurface(void)
{
	sqInt bitMapPtr;
	char *buffer;
	sqInt depth;
	sqInt height;
	long movie;
	sqInt moviePtr;
	sqInt results;
	sqInt rowBytes;
	sqInt width;
	sqInt _return_value;

	bitMapPtr = stackValue(5);
	width = stackIntegerValue(4);
	height = stackIntegerValue(3);
	rowBytes = stackIntegerValue(2);
	depth = stackIntegerValue(1);
	moviePtr = stackValue(0);
	if (failed()) {
		return null;
	}
	buffer = ((char *) (positiveMachineIntegerValueOf(bitMapPtr)));
	movie = ((long) (positiveMachineIntegerValueOf(moviePtr)));
	results = stQuicktimeSetSurfacewidthheightrowBytesdepthmovie(buffer, width, height, rowBytes, depth, movie);
	if (failed()) {
		return null;
	}
	_return_value = integerObjectOf(results);
	if (failed()) {
		return null;
	}
	popthenPush(7, _return_value);
	return null;
}


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {

#if !defined(SQUEAK_BUILTIN_PLUGIN)
		failed = interpreterProxy->failed;
		integerObjectOf = interpreterProxy->integerObjectOf;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		positiveMachineIntegerValueOf = interpreterProxy->positiveMachineIntegerValueOf;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}

	/* SmartSyntaxInterpreterPlugin>>#sqAssert: */
static sqInt
sqAssert(sqInt aBool)
{
	/* missing DebugCode */;
	return aBool;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "QuicktimePlugin";
void* QuicktimePlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "initialiseModule", (void*)initialiseModule},
	{(void*)_m, "moduleUnloaded", (void*)moduleUnloaded},
	{(void*)_m, "primitiveClearFrameCompletedSemaphore\000\000", (void*)primitiveClearFrameCompletedSemaphore},
	{(void*)_m, "primitiveDestroyHandle\000\000", (void*)primitiveDestroyHandle},
	{(void*)_m, "primitiveDestroySurface\000\000", (void*)primitiveDestroySurface},
	{(void*)_m, "primitiveSetFrameCompletedSemaphore\000\000", (void*)primitiveSetFrameCompletedSemaphore},
	{(void*)_m, "primitiveSetGWorldPtrOntoExistingSurface\000\000", (void*)primitiveSetGWorldPtrOntoExistingSurface},
	{(void*)_m, "primitiveSetGWorldPtrOntoSurface\000\000", (void*)primitiveSetGWorldPtrOntoSurface},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveClearFrameCompletedSemaphoreAccessorDepth = 0;
signed char primitiveDestroyHandleAccessorDepth = 0;
signed char primitiveDestroySurfaceAccessorDepth = 0;
signed char primitiveSetFrameCompletedSemaphoreAccessorDepth = 0;
signed char primitiveSetGWorldPtrOntoExistingSurfaceAccessorDepth = 0;
signed char primitiveSetGWorldPtrOntoSurfaceAccessorDepth = 0;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
