#ifndef __PDDL_PARSE__DETAIL__NORMALIZATION__ATOMIC_FORMULA_H
#define __PDDL_PARSE__DETAIL__NORMALIZATION__ATOMIC_FORMULA_H

#include <pddlparse/ASTForward.h>
#include <pddlparse/Context.h>
#include <pddlparse/NormalizedASTForward.h>

namespace pddl
{
namespace detail
{

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AtomicFormula
//
////////////////////////////////////////////////////////////////////////////////////////////////////

normalizedAST::AtomicFormula normalize(ast::AtomicFormula &&atomicFormula);

////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

#endif