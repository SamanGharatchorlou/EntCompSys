#include "pch.h"
#include "XMLParser.h"

#include "rapidxml_print.hpp"


void XMLParser::parseXML(const BasicString& filePath)
{
	bool doesExits = fs::exists(filePath.c_str());

	ASSERT(fs::exists(filePath.c_str()), "File path '%s' does not exist, cannot parse xml file\n", filePath.c_str());

	file = new rapidxml::file<>(filePath.c_str());
	xmlFile.parse<rapidxml::parse_no_data_nodes>(file->data());

#if DEBUG_MODE
	path = filePath;
#endif
}

void XMLParser::saveToFile(std::ofstream& file)
{
	DebugPrint(Log, "Saveing xml to file %s\n", xmlFile.value());
	file << xmlFile;
}


XMLParser::~XMLParser()
{
	delete file;
}


XMLNode XMLParser::rootNode() const
{
	return XMLNode(xmlFile.first_node());
}


XMLNode XMLParser::rootChild(const BasicString& label) const
{
#if DEBUG_MODE
	XMLNode child = rootNode().child(label);
	if (child.isEmpty())
		DebugPrint(Log, "Parser at path '%s' has no child node labeled '%s'\n", path.c_str(), label.c_str());
	return child;
#endif

	return XMLNode(xmlFile.first_node()->first_node(label.c_str()));
}
