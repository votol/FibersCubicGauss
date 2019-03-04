#include "Operator.h"
#include <cuda_runtime.h>
#include <iostream>
#include "OperatorKernels.h"
#include "ParameterDefines.h"


int OperatorBase::GetDim(const std::vector<double>& parameters)
{
	return int(width)*int(width)*8;
}
void OperatorBase::make_matrix(sparse_matrix<cuDoubleComplex>& in,
		const std::vector<double>& parameters)
{
	int dim = int(width);
	for(int m = 0; m < dim; ++m)
	{
		for(int n = 0; n < dim; ++n)
		{
			if(m != dim - 1)
			{
				in.SetElement((m+1) * dim +n,m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(dim*dim + (m+1) * dim +n, dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(2*dim*dim + (m+1) * dim +n, 2*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(3*dim*dim + (m+1) * dim +n, 3*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(4*dim*dim + (m+1) * dim +n, 4*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(5*dim*dim + (m+1) * dim +n, 5*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(6*dim*dim + (m+1) * dim +n, 6*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
                in.SetElement(7*dim*dim + (m+1) * dim +n, 7*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
			}
			if(m != 0)
			{
				in.SetElement((m-1) * dim +n,m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(dim*dim + (m-1) * dim +n, dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(2*dim*dim + (m-1) * dim +n, 2*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(3*dim*dim + (m-1) * dim +n, 3*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(4*dim*dim + (m-1) * dim +n, 4*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(5*dim*dim + (m-1) * dim +n, 5*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(6*dim*dim + (m-1) * dim +n, 6*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
                in.SetElement(7*dim*dim + (m-1) * dim +n, 7*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
			}
			if(n != dim - 1)
			{
				in.SetElement(m * dim +n + 1,m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(dim*dim + m * dim +n +1, dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(2*dim*dim + m * dim +n +1, 2*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(3*dim*dim + m * dim +n +1, 3*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(4*dim*dim + m * dim +n +1, 4*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(5*dim*dim + m * dim +n +1, 5*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(6*dim*dim + m * dim +n +1, 6*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
                in.SetElement(7*dim*dim + m * dim +n +1, 7*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
			}
			if(n != 0)
			{
				in.SetElement(m * dim +n - 1,m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(dim*dim + m * dim +n -1, dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(2*dim*dim + m * dim +n -1, 2*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(3*dim*dim + m * dim +n -1, 3*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(4*dim*dim + m * dim +n -1, 4*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
				in.SetElement(5*dim*dim + m * dim +n -1, 5*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
				in.SetElement(6*dim*dim + m * dim +n -1, 6*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,1.0));
                in.SetElement(7*dim*dim + m * dim +n -1, 7*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-1.0));
			}
			if(m == dim/2)
			{
				in.SetElement(3*dim*dim + n * dim +m,m * dim +n,
						make_cuDoubleComplex(0.0,-g));
				in.SetElement(3*dim*dim + m * dim +n, dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,-g));
				in.SetElement(5*dim*dim + m * dim +n, 2*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,g));
				in.SetElement(1*dim*dim + m * dim +n , 3*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,g));
				in.SetElement(1*dim*dim + n * dim +m, 4*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, -g));
				in.SetElement(2*dim*dim + m * dim +n, 5*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, -g));
                in.SetElement(2*dim*dim + n * dim +m, 6*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, -g));
                in.SetElement(5*dim*dim + n * dim +m, 7*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, -g));
			}
			if(n == dim/2)
			{
				in.SetElement(4*dim*dim + m * dim +n,m * dim +n,
						make_cuDoubleComplex(0.0,g));
				in.SetElement(4*dim*dim + n * dim +m, dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,g));
				in.SetElement(6*dim*dim + n * dim +m, 2*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,g));
				in.SetElement(0*dim*dim + n * dim +m , 3*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0,g));
				in.SetElement(0*dim*dim + m * dim +n, 4*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, -g));
				in.SetElement(7*dim*dim + n * dim +m, 5*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, g));
                in.SetElement(7*dim*dim + m * dim +n, 6*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, g));
                in.SetElement(6*dim*dim + m * dim +n, 7*dim*dim + m * dim +n,
						make_cuDoubleComplex(0.0, -g));
			}
			
			in.SetElement(3*dim*dim + m * dim +n, 3*dim*dim + m * dim +n,
					make_cuDoubleComplex(-D, 0.0));
			in.SetElement(4*dim*dim + m * dim +n, 4*dim*dim + m * dim +n,
					make_cuDoubleComplex(-D, 0.0));
			in.SetElement(5*dim*dim + m * dim +n, 5*dim*dim + m * dim +n,
					make_cuDoubleComplex(-D, 0.0));
            in.SetElement(6*dim*dim + m * dim +n, 6*dim*dim + m * dim +n,
					make_cuDoubleComplex(-D, 0.0));
			in.SetElement(7*dim*dim + m * dim +n, 7*dim*dim + m * dim +n,
					make_cuDoubleComplex(-4.0*D, 0.0));
		}
	}
}
void OperatorBase::make_vectors(std::vector<cuDoubleComplex>& cons,
		std::vector<cuDoubleComplex>& ex, const std::vector<double>& parameters)
{
	int dim = int(width);
	for(int m=0; m < dim; ++m)
	{
		for(int n = 0; n < dim; ++n)
		{
			ex[m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			cons[m*dim+n]=make_cuDoubleComplex(0.0,0.0);
            ex[1*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			cons[1*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			if(n==dim/2 && m==dim/2)
			{
				ex[2*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,g);
				cons[2*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			}
			else
			{
				ex[2*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
				cons[2*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			}
			if(n==dim/2 && m==dim/2)
			{
				ex[3*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
				cons[3*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,g);
			}
			else
			{
				ex[3*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
				cons[3*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			}

			if(n==dim/2 && m==dim/2)
			{
				ex[4*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
				cons[4*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,-g);
			}
			else
			{
				ex[4*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
				cons[4*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			}
			ex[5*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			cons[5*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
            ex[6*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			cons[6*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
            if(n==dim/2 && m==dim/2)
			{
				ex[7*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,-g);
				cons[7*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			}
			else
			{
				ex[7*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
				cons[7*dim*dim + m*dim+n]=make_cuDoubleComplex(0.0,0.0);
			}
		}
	}
}

void test_matrix(CSRMatrix<cuDoubleComplex>&  in)
{
	unsigned int row=0;
	for(unsigned int id=0;id<in.len;++id)
	{
		while(id >= in.row_s[row])
			++row;
		std::cout<<row-1<<" "<<in.col[id]<<" "<<in.val[id].x<<" "<<in.val[id].y<<std::endl;
	}
}

OperatorBase::OperatorBase(const std::vector<double>& params)
{
	DIM = GetDim(params);
	sparse_matrix<cuDoubleComplex> matrix(DIM);
	make_matrix(matrix, params);
	CSRMatrix<cuDoubleComplex> host_matrix = matrix.ToCSR();
	//test_matrix(host_matrix);
	device_matrix.dim = host_matrix.dim;
	device_matrix.len = host_matrix.len;
	cudaMalloc((void**)&device_matrix.col,device_matrix.len * sizeof(device_matrix.col[0]));
	cudaMalloc((void**)&device_matrix.row_s,(device_matrix.dim + 1) * sizeof(device_matrix.row_s[0]));
	cudaMalloc((void**)&device_matrix.val,device_matrix.len * sizeof(device_matrix.val[0]));
	cudaMemcpy(device_matrix.col, host_matrix.col,device_matrix.len * sizeof(device_matrix.col[0]),
			cudaMemcpyHostToDevice);
	cudaMemcpy(device_matrix.row_s, host_matrix.row_s,
			(device_matrix.dim + 1) * sizeof(device_matrix.row_s[0]),
			cudaMemcpyHostToDevice);
	cudaMemcpy(device_matrix.val, host_matrix.val,device_matrix.len * sizeof(device_matrix.val[0]),
			cudaMemcpyHostToDevice);
	delete [] host_matrix.col;
	delete [] host_matrix.row_s;
	delete [] host_matrix.val;
	std::vector<cuDoubleComplex> ex(DIM);
	std::vector<cuDoubleComplex> cons(DIM);

	make_vectors(cons,ex,params);
	cudaMalloc((void**)&device_vec_const,DIM * sizeof(device_vec_const[0]));
	cudaMalloc((void**)&device_vec_exp,DIM * sizeof(device_vec_exp[0]));
	cudaMemcpy(device_vec_const, cons.data(),DIM * sizeof(device_vec_const[0]),
				cudaMemcpyHostToDevice);
	cudaMemcpy(device_vec_exp, ex.data(),DIM * sizeof(device_vec_exp[0]),
					cudaMemcpyHostToDevice);

	cudaMalloc((void**)&device_parameters, params.size()* sizeof(device_parameters[0]));

	cusparseCreate(& (handle));
	cusparseCreateMatDescr(& (descr));
	cusparseSetMatType(descr,CUSPARSE_MATRIX_TYPE_GENERAL);
	cusparseSetMatIndexBase(descr,CUSPARSE_INDEX_BASE_ZERO);

	tmp_vec.resize(3*3);
}

OperatorBase::~OperatorBase()
{
	cudaFree(device_matrix.col);
	cudaFree(device_matrix.row_s);
	cudaFree(device_matrix.val);
	cudaFree(device_vec_const);
	cudaFree(device_vec_exp);
	cudaFree(device_parameters);
	cusparseDestroyMatDescr(descr);
	cusparseDestroy(handle);
}

void test_vec(std::vector<cuDoubleComplex>& in)
{
	for(unsigned int m = 0; m<3; m++)
		{
			for(unsigned int n = 0; n<3; n++)
			{
				cuDoubleComplex tmp_val = in[m*3 + n];
				if(tmp_val.x!=0.0 || tmp_val.y !=  0.0)
				{
					std::cout<<m<<" "<<n<<" ";
					if(tmp_val.x!=0.0)
					{
						std::cout<<tmp_val.x;
						if(tmp_val.y>0.0)
							std::cout<<"+";
						if(tmp_val.y!=0.0)
							std::cout<<tmp_val.y<<"i";
					}
					else
					{
						std::cout<<tmp_val.y<<"i";
					}
					std::cout<<std::endl;
				}
			}
		}
	std::cout<<"----------------------------------------------\n";
}

void OperatorBase::apply(cuDoubleComplex* out, const cuDoubleComplex* in,
		const std::vector<double>& params)
{
	cudaMemcpy(device_parameters, params.data(),params.size() * sizeof(device_parameters[0]),
						cudaMemcpyHostToDevice);
	MakeVector(out,device_vec_const,device_vec_exp,device_parameters,DIM);
	cuDoubleComplex alpha =make_cuDoubleComplex(1.0,0.0);
	cusparseZcsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE,
			device_matrix.dim, device_matrix.dim, device_matrix.len, &alpha, descr,
			device_matrix.val,(int*)device_matrix.row_s, (int*)device_matrix.col, in, &alpha, out);
	cudaMemcpy(tmp_vec.data(), out, 3*3 * sizeof(in[0]),
					cudaMemcpyDeviceToHost);

	//test_vec(tmp_vec);
}
