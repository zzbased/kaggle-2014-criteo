#pragma GCC diagnostic ignored "-Wunused-result"

#ifndef _COMMON_H_
#define _COMMON_H_

#define flag { printf("\nLINE: %d\n", __LINE__); fflush(stdout); }

#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include <pmmintrin.h>

struct Node
{
    Node() : i(0), v(0) {}
    Node(uint32_t const i, float const v) : i(i), v(v) {}
    uint32_t i;
    float v;
};

struct Problem
{
    Problem() : nr_instance(0), nr_field(0), nr_sparse_field(0) {}
    Problem(uint32_t const nr_instance, uint32_t const nr_field)
        : nr_instance(nr_instance), nr_field(nr_field), nr_sparse_field(0),
          X(nr_field, std::vector<Node>(nr_instance)),
          Z(nr_field, std::vector<Node>(nr_instance)),
          Y(nr_instance) {}
    uint32_t const nr_instance, nr_field;   // for dense
    uint32_t nr_sparse_field;   // for sparse
    std::vector<std::vector<Node>> X, Z;    // X的row是feature，column是instance
    std::vector<uint32_t> SI, SJ;   // SJ:存储所有instance的feature
    std::vector<uint64_t> SIP, SJP; // SIP:SI-feature之间的分隔position; SJP:存储instance之间的分隔position;
    std::vector<float> Y;
    // dense特征就是用一个大矩阵，按照row,column存储，自然的存储方式。
    // sparse特征是用vector存储，并且加一个position vector指出分隔点。

    void Print() const {
        std::cerr << "nr_instance:" << nr_instance
                  << ",nr_field:" << nr_field
                  << ",nr_sparse_field:" << nr_sparse_field
                  << std::endl;
        std::cerr << "X matrix:\n";
        PrintMatrix(X);
        std::cerr << "Z matrix:\n";
        PrintMatrix(Z);
        std::cerr << "Y vector:\n";
        PrintVector(Y);
        std::cerr << "SI vector:\n";
        PrintVector(SI);
        std::cerr << "SJ vector:\n";
        PrintVector(SJ);
        std::cerr << "SIP vector:\n";
        PrintVector(SIP);
        std::cerr << "SJP vector:\n";
        PrintVector(SJP);
    }
    template<typename T>
    void PrintVector(const std::vector<T>& X) const {
        std::cerr << X.size() << std::endl;
        for (size_t i = 0; i < X.size(); ++i) {
            std::cerr << X[i] << " ";
        }
        std::cerr << std::endl;
    }
    void PrintMatrix(const std::vector<std::vector<Node>>& X) const {
        std::cerr << X.size() << std::endl;
        for (size_t i = 0; i < X.size(); ++i) {
            for (size_t j = 0; j < X[i].size(); ++j) {
                std::cerr << X[i][j].i << ":" << X[i][j].v << " ";
            }
            std::cerr << std::endl;
        }
    }
};

inline std::vector<float>
construct_instance(Problem const &prob, uint32_t const i)
{
    uint32_t const nr_field = prob.nr_field;
    uint32_t const nr_sparse_field = prob.nr_sparse_field;
    std::vector<uint32_t> const &SJ = prob.SJ;
    std::vector<uint64_t> const &SJP = prob.SJP;

    std::vector<float> x(nr_field+nr_sparse_field, 0);
    for(uint32_t j = 0; j < prob.nr_field; ++j)
        x[j] = prob.Z[j][i].v;
    for(uint64_t p = SJP[i]; p < SJP[i+1]; ++p)
        x[SJ[p]+nr_field] = 1;

    return x;
}

Problem read_data(std::string const &dense_path,
    std::string const &sparse_path);

FILE *open_c_file(std::string const &path, std::string const &mode);

std::vector<std::string>
argv_to_args(int const argc, char const * const * const argv);

#endif // _COMMON_H_
