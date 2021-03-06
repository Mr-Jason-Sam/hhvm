/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/compiler/expression/yield_from_expression.h"
#include "hphp/compiler/analysis/function_scope.h"

using namespace HPHP;

///////////////////////////////////////////////////////////////////////////////
// constructors/destructors

YieldFromExpression::YieldFromExpression
(EXPRESSION_CONSTRUCTOR_PARAMETERS,
 ExpressionPtr exp)
  : Expression(EXPRESSION_CONSTRUCTOR_PARAMETER_VALUES(YieldFromExpression)),
    m_exp(exp) {
}

ExpressionPtr YieldFromExpression::clone() {
  YieldFromExpressionPtr exp(new YieldFromExpression(*this));
  Expression::deepCopy(exp);
  exp->m_exp = Clone(m_exp);
  return exp;
}

///////////////////////////////////////////////////////////////////////////////
// parser functions


///////////////////////////////////////////////////////////////////////////////
// static analysis functions

ConstructPtr YieldFromExpression::getNthKid(int n) const {
  switch (n) {
    case 0:
      return m_exp;
    default:
      assert(false);
      break;
  }
  return ConstructPtr();
}

int YieldFromExpression::getKidCount() const {
  return 1;
}

void YieldFromExpression::setNthKid(int n, ConstructPtr cp) {
  switch (n) {
    case 0:
      m_exp = dynamic_pointer_cast<Expression>(cp);
      break;
    default:
      assert(false);
      break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// code generation functions

void YieldFromExpression::outputPHP(CodeGenerator &cg, AnalysisResultPtr ar) {
  cg_printf("yield from ");
  m_exp->outputPHP(cg, ar);
}
