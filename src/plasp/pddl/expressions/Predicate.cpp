#include <plasp/pddl/expressions/Predicate.h>

#include <plasp/pddl/Context.h>
#include <plasp/pddl/ExpressionVisitor.h>
#include <plasp/pddl/Identifier.h>
#include <plasp/pddl/expressions/Constant.h>
#include <plasp/pddl/expressions/Reference.h>
#include <plasp/pddl/expressions/Variable.h>

namespace plasp
{
namespace pddl
{
namespace expressions
{

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Predicate
//
////////////////////////////////////////////////////////////////////////////////////////////////////

Predicate::Predicate()
:	m_isDeclared{false}
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

PredicatePointer Predicate::parse(std::string name, utils::Parser &parser,
	Context &context, const Variables &parameters)
{
	auto predicate = std::make_unique<Predicate>(Predicate());

	predicate->m_name = name;

	parser.skipWhiteSpace();

	// Parse arguments
	while (parser.currentCharacter() != ')')
	{
		// Parse variables
		if (parser.currentCharacter() == '?')
		{
			const auto *variable = Variable::parseExisting(parser, parameters);
			auto variableReference = std::make_unique<Reference<Variable>>(variable);
			predicate->m_arguments.emplace_back(std::move(variableReference));
		}
		// Parse constants
		else
		{
			const auto *constant = Constant::parseExisting(parser, context);
			auto constantReference = std::make_unique<Reference<Constant>>(constant);
			predicate->m_arguments.emplace_back(std::move(constantReference));
		}

		parser.skipWhiteSpace();
	}

	// TODO: check that signature matches one of the declared ones

	return predicate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Predicate::accept(plasp::pddl::ExpressionVisitor &expressionVisitor) const
{
	expressionVisitor.visit(*this);
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

const Expressions &Predicate::arguments() const
{
	return m_arguments;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}