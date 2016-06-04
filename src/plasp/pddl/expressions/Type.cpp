#include <plasp/pddl/expressions/Type.h>

#include <plasp/pddl/Context.h>
#include <plasp/pddl/expressions/Reference.h>

namespace plasp
{
namespace pddl
{
namespace expressions
{

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Type
//
////////////////////////////////////////////////////////////////////////////////////////////////////

ExpressionPointer parseExistingPrimitiveType(utils::Parser &parser, Context &context,
	const Variables &parameters)
{
	auto primitiveType = PrimitiveType::parseExisting(parser, context);

	return std::make_unique<Reference<PrimitiveType>>(primitiveType);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}