/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.517 uuid: 14ff7126-70ec-4cc4-9f55-70256e6a3d35
   from
	VMProfileLinuxSupportPlugin VMMaker.oscog-eem.517 uuid: 14ff7126-70ec-4cc4-9f55-70256e6a3d35
 */
static char __buildInfo[] = "VMProfileLinuxSupportPlugin VMMaker.oscog-eem.517 uuid: 14ff7126-70ec-4cc4-9f55-70256e6a3d35 " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <link.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "sqMemoryAccess.h"


/*** Constants ***/
#define PrimErrBadArgument 3
#define PrimErrInappropriate 6
#define PrimErrNoMemory 9
#define PrimErrNotFound 11


/*** Function Prototypes ***/
static sqInt countnummodules(struct dl_phdr_info *info, size_t size, void *ignored);
static VirtualMachine * getInterpreter(void);
EXPORT(const char*) getModuleName(void);
static sqInt halt(void);
static sqInt msg(char *s);
EXPORT(sqInt) primitiveDLSymInLibrary(void);
EXPORT(sqInt) primitiveExecutableModules(void);
EXPORT(sqInt) primitiveInterpretAddress(void);
static sqInt reapmodulenames(struct dl_phdr_info *info, size_t size, void *ignored);
static sqInt reapmodulesymlinks(struct dl_phdr_info *info, size_t size, void *ignored);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static void * (*arrayValueOf)(sqInt oop);
static sqInt (*byteSizeOf)(sqInt oop);
static sqInt (*classArray)(void);
static sqInt (*classString)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*methodReturnValue)(sqInt oop);
static sqInt (*nilObject)(void);
static sqInt (*popRemappableOop)(void);
static sqInt (*positive32BitIntegerFor)(sqInt integerValue);
static sqInt (*primitiveFailFor)(sqInt reasonCode);
static sqInt (*pushRemappableOop)(sqInt oop);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*storePointerofObjectwithValue)(sqInt index, sqInt oop, sqInt valuePointer);
static sqInt (*topRemappableOop)(void);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern void * arrayValueOf(sqInt oop);
extern sqInt byteSizeOf(sqInt oop);
extern sqInt classArray(void);
extern sqInt classString(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
extern sqInt isBytes(sqInt oop);
extern sqInt methodReturnValue(sqInt oop);
extern sqInt nilObject(void);
extern sqInt popRemappableOop(void);
extern sqInt positive32BitIntegerFor(sqInt integerValue);
extern sqInt primitiveFailFor(sqInt reasonCode);
extern sqInt pushRemappableOop(sqInt oop);
extern sqInt stackValue(sqInt offset);
extern sqInt storePointerofObjectwithValue(sqInt index, sqInt oop, sqInt valuePointer);
extern sqInt topRemappableOop(void);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"VMProfileLinuxSupportPlugin VMMaker.oscog-eem.517 (i)"
#else
	"VMProfileLinuxSupportPlugin VMMaker.oscog-eem.517 (e)"
#endif
;
static sqInt numModules;
static sqInt primErr;


static sqInt
countnummodules(struct dl_phdr_info *info, size_t size, void *ignored)
{
	numModules += 1;
	return 0;
}


/*	Note: This is coded so that plugins can be run from Squeak. */

static VirtualMachine *
getInterpreter(void)
{
	return interpreterProxy;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

static sqInt
halt(void)
{
	;
	return 0;
}

static sqInt
msg(char *s)
{
	fprintf(stderr, "\n%s: %s", moduleName, s);
	return 0;
}


/*	Answer the address of the symbol whose name is the first argument
	in the library whose name is the second argument, or nil if none. */

EXPORT(sqInt)
primitiveDLSymInLibrary(void)
{
    void *addr;
    void *lib;
    char *libName;
    sqInt nameObj;
    sqInt ok;
    char *symName;
    sqInt sz;

	nameObj = stackValue(0);
	if (!(isBytes(nameObj))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	sz = byteSizeOf(nameObj);
	libName = malloc(sz + 1);
	strncpy(libName, firstIndexableField(nameObj), sz);
	libName[sz] = 0;
	nameObj = stackValue(1);
	if (!(isBytes(nameObj))) {
		free(libName);
		return primitiveFailFor(PrimErrBadArgument);
	}
	sz = byteSizeOf(nameObj);
	symName = malloc(sz + 1);
	strncpy(symName, firstIndexableField(nameObj), sz);
	symName[sz] = 0;
	lib = dlopen(libName, RTLD_LAZY | RTLD_NODELETE);
	if (!(lib)) {
		free(libName);
		free(symName);
		return primitiveFailFor(PrimErrInappropriate);
	}
	dlerror();
	addr = dlsym(lib, symName);
	ok = (dlerror()) == null;
	free(symName);
	free(libName);
	dlclose(lib);
	if (!ok) {
		return primitiveFailFor(PrimErrNotFound);
	}
	return methodReturnValue(positive32BitIntegerFor(((unsigned long)addr)));
}


/*	Answer an Array of pairs of strings for executable modules (the VM
	executable and loaded libraries).
	The first element in each pair is the filename of the module. The second
	element is either nil or
	the symlink's target, if the filename is a symlink. */

EXPORT(sqInt)
primitiveExecutableModules(void)
{
    sqInt resultObj;

	numModules = 0;
	dl_iterate_phdr(countnummodules,0);

	/* skip the fake linux-gate.so.1 */

	resultObj = instantiateClassindexableSize(classArray(), (numModules - 1) * 2);
	if (resultObj == 0) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	pushRemappableOop(resultObj);
	primErr = (numModules = 0);
	dl_iterate_phdr(reapmodulesymlinks,0);
	resultObj = popRemappableOop();
	if (primErr != 0) {
		return primitiveFailFor(primErr);
	}
	return methodReturnValue(resultObj);
}


/*	Answer the address of the interpret routine. */

EXPORT(sqInt)
primitiveInterpretAddress(void)
{
    extern void interpret();

	
	return methodReturnValue(positive32BitIntegerFor(((unsigned long)interpret)));
}

static sqInt
reapmodulenames(struct dl_phdr_info *info, size_t size, void *ignored)
{
    const char *elfModuleName;
    extern char *GetAttributeString(sqInt);
    sqInt len;
    sqInt moduleNameObj;

	
	elfModuleName = numModules ? info->dlpi_name : GetAttributeString(0);
	if ((elfModuleName == null)
	 || (((len = strlen(elfModuleName))) == 0)) {
		return 0;
	}
	moduleNameObj = instantiateClassindexableSize(classString(), len);
	if (moduleNameObj == 0) {
		primErr = PrimErrNoMemory;
		return 1;
	}
	strncpy(arrayValueOf(moduleNameObj), elfModuleName, len);
	storePointerofObjectwithValue(numModules, topRemappableOop(), moduleNameObj);
	numModules += 1;
	return 0;
}


/*	like reap:module:names:, but follows symlinks */

static sqInt
reapmodulesymlinks(struct dl_phdr_info *info, size_t size, void *ignored)
{
    const char *elfModuleName;
    extern char *GetAttributeString(sqInt);
    sqInt len;
    sqInt moduleNameObj;
    char symLinkBuf[PATH_MAX];

	
	elfModuleName = numModules ? info->dlpi_name : GetAttributeString(0);
	if ((elfModuleName == null)
	 || (((len = strlen(elfModuleName))) == 0)) {
		return 0;
	}
	moduleNameObj = instantiateClassindexableSize(classString(), len);
	if (moduleNameObj == 0) {
		primErr = PrimErrNoMemory;
		return 1;
	}
	strncpy(arrayValueOf(moduleNameObj), elfModuleName, len);
	storePointerofObjectwithValue(numModules, topRemappableOop(), moduleNameObj);
	strcpy(symLinkBuf, elfModuleName);
	if (((len = readlink(elfModuleName, symLinkBuf, PATH_MAX))) > 0) {
		moduleNameObj = instantiateClassindexableSize(classString(), len);
		if (moduleNameObj == 0) {
			primErr = PrimErrNoMemory;
			return 1;
		}
		strncpy(arrayValueOf(moduleNameObj), symLinkBuf, len);
		storePointerofObjectwithValue(numModules + 1, topRemappableOop(), moduleNameObj);
	}
	else {
		storePointerofObjectwithValue(numModules + 1, topRemappableOop(), nilObject());
	}
	numModules += 2;
	return 0;
}


/*	Note: This is coded so that it can be run in Squeak. */

EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
    sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		arrayValueOf = interpreterProxy->arrayValueOf;
		byteSizeOf = interpreterProxy->byteSizeOf;
		classArray = interpreterProxy->classArray;
		classString = interpreterProxy->classString;
		firstIndexableField = interpreterProxy->firstIndexableField;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
		isBytes = interpreterProxy->isBytes;
		methodReturnValue = interpreterProxy->methodReturnValue;
		nilObject = interpreterProxy->nilObject;
		popRemappableOop = interpreterProxy->popRemappableOop;
		positive32BitIntegerFor = interpreterProxy->positive32BitIntegerFor;
		primitiveFailFor = interpreterProxy->primitiveFailFor;
		pushRemappableOop = interpreterProxy->pushRemappableOop;
		stackValue = interpreterProxy->stackValue;
		storePointerofObjectwithValue = interpreterProxy->storePointerofObjectwithValue;
		topRemappableOop = interpreterProxy->topRemappableOop;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* VMProfileLinuxSupportPlugin_exports[][3] = {
	{"VMProfileLinuxSupportPlugin", "getModuleName", (void*)getModuleName},
	{"VMProfileLinuxSupportPlugin", "primitiveDLSymInLibrary", (void*)primitiveDLSymInLibrary},
	{"VMProfileLinuxSupportPlugin", "primitiveExecutableModules", (void*)primitiveExecutableModules},
	{"VMProfileLinuxSupportPlugin", "primitiveInterpretAddress", (void*)primitiveInterpretAddress},
	{"VMProfileLinuxSupportPlugin", "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#endif /* ifdef SQ_BUILTIN_PLUGIN */