#ifndef __PLASP__PDDL__EXPRESSION_H
#define __PLASP__PDDL__EXPRESSION_H

#include <memory>

#include <boost/variant.hpp>

#include <plasp/pddl/Variable.h>
#include <plasp/utils/Parser.h>

namespace plasp
{
namespace pddl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Expression
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class Context;
class ExpressionVisitor;

////////////////////////////////////////////////////////////////////////////////////////////////////

class Expression
{
	public:
		virtual void accept(ExpressionVisitor &expressionVisitor) const = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<Expression> parsePreconditionExpression(utils::Parser &parser, Context &context, const Variables &parameters);
std::unique_ptr<Expression> parseExpression(utils::Parser &parser, Context &context, const Variables &parameters);

std::unique_ptr<Expression> parseEffectExpression(utils::Parser &parser, Context &context, const Variables &parameters);

////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

#endif
