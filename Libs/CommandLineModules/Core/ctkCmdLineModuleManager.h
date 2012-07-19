/*=============================================================================
  
  Library: CTK
  
  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics
    
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  
    http://www.apache.org/licenses/LICENSE-2.0
    
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
  
=============================================================================*/

#ifndef CTKCMDLINEMODULEMANAGER_H
#define CTKCMDLINEMODULEMANAGER_H

#include <ctkCommandLineModulesCoreExport.h>

#include <QStringList>
#include <QString>
#include "ctkCmdLineModuleReference.h"

struct ctkCmdLineModuleFactory;

class ctkCmdLineModule;
class ctkCmdLineModuleManagerPrivate;

/**
 * \ingroup CommandLineModulesCore
 */
class CTK_CMDLINEMODULECORE_EXPORT ctkCmdLineModuleManager : public QObject
{
  Q_OBJECT

public:

  enum ValidationMode {
    /** registerModule() will throw an exception if the XML is invalid */
    STRICT_VALIDATION,
    /** no XML schema validation at all */
    SKIP_VALIDATION,
    /**
     * registerModule() will validate the XML description but proceed with
     * registration on validation error.
     */
    WEAK_VALIDATION
  };

  ctkCmdLineModuleManager(ctkCmdLineModuleFactory* descriptionFactory,
                          ValidationMode = STRICT_VALIDATION);

  ~ctkCmdLineModuleManager();

  void setVerboseOutput(bool verbose);
  bool verboseOutput() const;

  ctkCmdLineModuleReference registerModule(const QString& location);
  void unregisterModule(const ctkCmdLineModuleReference& moduleRef);

  ctkCmdLineModuleReference moduleReference(const QString& location) const;
  QList<ctkCmdLineModuleReference> moduleReferences() const;

  ctkCmdLineModule* createModule(const ctkCmdLineModuleReference& moduleRef);

  QList<ctkCmdLineModule*> modules(const ctkCmdLineModuleReference& moduleRef) const;

Q_SIGNALS:

  void moduleAdded(const ctkCmdLineModuleReference);
  void moduleRemoved(const ctkCmdLineModuleReference);

private:

  QScopedPointer<ctkCmdLineModuleManagerPrivate> d;

  Q_DISABLE_COPY(ctkCmdLineModuleManager)

};

#endif // CTKCMDLINEMODULEMANAGER_H