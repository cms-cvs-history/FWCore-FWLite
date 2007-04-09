#ifndef FWCore_FWLite_AutoLibraryLoader_h
#define FWCore_FWLite_AutoLibraryLoader_h
/**\class AutoLibraryLoader
 *
 * ROOT helper class which can automatically load the 
 * proper shared library when ROOT needs a new class dictionary
 *
 * \author Chris Jones, Cornell
 *
 * $Id: AutoLibraryLoader.h,v 1.5 2006/12/16 13:33:29 wmtan Exp $
 *
 */
#include "TObject.h"
class DummyClassToStopCompilerWarning;

class AutoLibraryLoader: public TObject {
  friend class DummyClassToStopCompilerWarning;
public:
  /// interface for TClass generators
  ClassDef(AutoLibraryLoader,2);
  /// enable automatic library loading  
  static void enable();
  
  /// load all known libraries holding dictionaries
  static void loadAll();

private:
  AutoLibraryLoader();
  AutoLibraryLoader(const AutoLibraryLoader&); // stop default
  const AutoLibraryLoader& operator=(const AutoLibraryLoader&); // stop default
};


#endif