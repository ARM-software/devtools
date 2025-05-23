/*
 * Copyright (c) 2020-2025 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CHECKFILES_H
#define CHECKFILES_H

#include "RteModel.h"

struct FileEntry {
  FileEntry(const std::string& name, int lineNo) : m_name(name), m_lineNo(lineNo) {};

  std::string m_name;
  int m_lineNo;
};

class CheckFiles {
public:
  CheckFiles();
  ~CheckFiles();

  enum class FileType {
    Generic,
  };

  void SetPackageName(const std::string& packageName) { m_packageName = packageName; }
  const std::string& GetPackageName() const { return m_packageName; }
  void SetPackagePath(const std::string& packagePath);
  const std::string& GetPackagePath() const;
  bool CheckFile(RteItem* item);
  bool CheckUrls(RteItem* item);
  bool CheckDeprecated(RteItem* item);
  bool CheckDescription(RteItem* item);
  bool CheckFileExists(const std::string& fileName, int lineNo, bool associated = false);
  bool CheckCaseSense(const std::string& fileName, int lineNo);
  bool CheckFileIsInPack(const std::string& fileName, int lineNo);
  bool CheckForSpaces(const std::string& fileName, int lineNo);
  bool FindGetExactFileSystemName(const std::string& path, const std::string& fileNameIn, std::string& fileNameOut);
  bool CheckFileHasVersion(RteItem* item);
  bool CheckFileExtension(RteItem* item);
  bool CheckAsmGccCompilerDependency(RteItem* item);
  bool CheckTemplate(RteItem* item);
  bool CheckCompilerDependency(RteItem* item);
  bool FilterConditions(const std::string& filter, RteCondition* cond, Collection<RteItem*>* exList);
  bool CheckForCondition(RteItem* item, const std::string& parentName, const std::string& condFilter, const std::string& condValue = "");
  const std::string& GetFolder(RteItem* item) const;
  bool GetFileName(RteItem* item, std::string& filename, FileType& fileType) const;
  bool ToUpper(std::string& text);
  std::string GetFullFilename(const std::string& fileName);
  bool GatherIncPathVsAttrConfig(RteItem* item);
  bool CheckAttrConfigFiles();
  bool CheckCSolutionEntries(RteItem* item);
  bool CheckCsolutionLayer(RteItem* item);
  bool CheckCsolutionTemplate(RteItem* item);
  bool CheckForTag(RteItem* item, const std::list<std::string>& searchAttributes);


private:
  std::string m_packagePath;
  std::string m_packageName;
  std::map<std::string, RteItem*> m_includePaths;
  std::map<std::string, RteItem*> m_attrConfigFiles;
};

class CheckFilesVisitor : public RteVisitor
{
public:
  CheckFilesVisitor(const std::string& packagePath, const std::string& packageName);
  ~CheckFilesVisitor();
  virtual VISIT_RESULT Visit(RteItem* item);

  CheckFiles& GetCheckFiles() { return m_checkFiles; }

private:
  CheckFiles m_checkFiles;
};


#endif // CHECKFILES_H
