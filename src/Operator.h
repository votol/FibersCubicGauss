#ifndef __Operator_h_
#define __Operator_h_
#include "OperatorInterface.h"
#include "sparse.hpp"
#include "cuComplex.h"
#include <cusparse_v2.h>

class OperatorBase:public IOperator
{
	int DIM;
	CSRMatrix<cuDoubleComplex> device_matrix;
	cuDoubleComplex* device_vec_const;
	cuDoubleComplex* device_vec_exp;
	double* device_parameters;

	cusparseHandle_t handle;
	cusparseMatDescr_t descr;
	std::vector<cuDoubleComplex> tmp_vec;
	int GetDim(const std::vector<double>&);
	void make_matrix(sparse_matrix<cuDoubleComplex>&, const std::vector<double>& params);
	void make_vectors(std::vector<cuDoubleComplex>& cons, std::vector<cuDoubleComplex>& ex,
			const std::vector<double>& parameters);
public:
	OperatorBase(const std::vector<double>&);
	virtual ~OperatorBase();
	virtual void apply(cuDoubleComplex*, const cuDoubleComplex*,
				const std::vector<double>&) override;
};

#endif /*__Operator_h_*/
