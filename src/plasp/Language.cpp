#include <plasp/Language.h>

#include <boost/assign.hpp>
#include <boost/bimap.hpp>

namespace plasp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Language
//
////////////////////////////////////////////////////////////////////////////////////////////////////

using LanguageNames = boost::bimap<Language::Type, std::string>;

////////////////////////////////////////////////////////////////////////////////////////////////////

const LanguageNames languageNames = boost::assign::list_of<LanguageNames::relation>
	(Language::Type::PDDL, "PDDL")
	(Language::Type::SAS, "SAS")
	(Language::Type::Unknown, "Unknown");

////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Language::toString(Language::Type language)
{
	const auto match = languageNames.left.find(language);

	if (match != languageNames.left.end())
		return "Unknown";

	return match->second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Language::Type Language::fromString(const std::string &languageName)
{
	const auto match = languageNames.right.find(languageName);

	if (match != languageNames.right.end())
		return Language::Type::Unknown;

	return match->second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

}