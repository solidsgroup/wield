#ifndef WIELD_OPTIMIZATION_SOLVECONSTRAINEDLP_H
#define WIELD_OPTIMIZATION_SOLVECONSTRAINEDLP_H

#include <iostream>
#include "math.h"
#include "lp_lib.h"

#include "Utils/wieldEigen.h"

namespace Wield
{
namespace Optimization
{
///
/// \fn    SolveConstrainedLP
/// \brief Solve a constrained linear programming problem
///
/// Solve the following optimization problem:
/// \f[ \underset{\bm{x}}{\operatorname{minimize}} \bm{a}^T\bm{x} \f]
///
double SolveConstrainedLP(VectorXd &x, ///< The optimization variable: \f$ \mathbf{x} \in \mathbb{R}^n \f$
			  VectorXd a,  ///< The coefficients for the objective function: \f$ \mathbf{a}\in(\mathbb{R}^n)^*\f$
			  MatrixXd B,  ///< The matrix of constraints: \f$ B\in\mathbb{R}^{m\times n}\f$
			  VectorXd c)  ///< The rhs of the constraint equations: \f$ \mathbf{c}\in\mathbb{R}^m\f$
{
  
  if (x.size() != a.size()) WIELD_EXCEPTION_NEW("a.size() = " << a.size() << " but x.size() = " << x.size() ); 
  if (a.size() != B.cols()) WIELD_EXCEPTION_NEW("a.size() = " << a.size() << " but B.cols() = " << B.cols() ); 
  if (c.size() != B.rows()) WIELD_EXCEPTION_NEW("c.size() = " << c.size() << " but B.rows() = " << B.rows() ); 
  int n = a.size();
  int m = B.rows();
  
  lprec *lpModel = make_lp(0,n);
  
  set_add_rowmode(lpModel, TRUE);
  double row[n+1]; row[0] = 1;
  for (int i=0; i<m; i++)
    {
      for (int j=0;j<n;j++) row[j+1] = B(i,j); 
      add_constraint(lpModel, row, EQ, c(i));
    }
  set_add_rowmode(lpModel, FALSE);
  
  for (int j=0;j<n;j++) row[j+1] = a(j); 
  set_obj_fn(lpModel, row);

  
  print_lp(lpModel);

  set_verbose(lpModel,IMPORTANT);
  int errorCode = solve(lpModel);
  double w;
  if (!errorCode)
    {
      w = get_objective(lpModel);
      get_variables(lpModel, row);
      for (int j=0;j<n;j++) x(j) = row[j];
      cout << "w = " << w << endl;
      cout << "x = " << x.transpose() << endl;
      cout << (B*x).transpose() << endl;
    }
  else
    w = INFINITY;

  return w;
}
}
}

#endif
