#include <plasp/pddl/Predicate.h>

#include <algorithm>

#include <plasp/pddl/Context.h>
#include <plasp/pddl/Identifier.h>

namespace plasp
{
namespace pddl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Predicate
//
////////////////////////////////////////////////////////////////////////////////////////////////////

Predicate::Predicate(std::string name)
:	m_isDeclared{false},
	m_name{name}
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Predicate &Predicate::parseDeclaration(utils::Parser &parser, Context &context)
{
	parser.expect<std::string>("(");

	const auto predicateName = parser.parseIdentifier(isIdentifier);

	Predicate predicate(predicateName);

	// Flag predicate as correctly declared in the types section
	predicate.setDeclared();

	parser.skipWhiteSpace();

	// Parse arguments
	while (parser.currentCharacter() != ')')
	{
		predicate.m_arguments.emplace_back(Variable::parse(parser, context));

		parser.skipWhiteSpace();

		// Check if the variable has a type declaration
		if (!parser.advanceIf('-'))
			continue;

		// Parse argument type
		const auto &type = TypePrimitive::parse(parser, context);

		// Set the argument type for all previously flagged arguments
		std::for_each(predicate.m_arguments.begin(), predicate.m_arguments.end(),
			[&](auto &argument)
			{
				if (!argument.isDirty())
					return;

				argument.setType(type);
				argument.setDirty(false);
			});

		parser.skipWhiteSpace();
	}

	parser.expect<std::string>(")");

	const auto predicateArity = predicate.m_arguments.size();
	const PredicateHashMapKey key = {predicateName, predicateArity};

	const auto insertionResult = context.predicates.emplace(std::make_pair(key, std::move(predicate)));

	std::cout << "Emplaced " << insertionResult.first->second.name() << std::endl;

	return insertionResult.first->second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Predicate::setDeclared()
{
	m_isDeclared = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool Predicate::isDeclared() const
{
	return m_isDeclared;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string &Predicate::name() const
{
	return m_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const Variables &Predicate::arguments() const
{
	return m_arguments;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
