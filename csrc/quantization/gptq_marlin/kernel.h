
#ifndef MARLIN_NAMESPACE_NAME
  #define MARLIN_NAMESPACE_NAME marlin
#endif

#include "marlin.cuh"
#include "marlin_dtypes.cuh"
#include "core/scalar_type.hpp"

#define MARLIN_KERNEL_PARAMS                                                 \
  const int4 *__restrict__ A, const int4 *__restrict__ B,                    \
      int4 *__restrict__ C, int4 *__restrict__ C_tmp,                        \
      const int4 *__restrict__ scales_ptr, const int4 *__restrict__ zp_ptr,  \
      const int *__restrict__ g_idx, int num_groups, int prob_m, int prob_n, \
      int prob_k, int lda, int *locks, bool use_atomic_add,                  \
      bool use_fp32_reduce, int max_shared_mem

namespace MARLIN_NAMESPACE_NAME {
template <typename scalar_t,  // compute dtype, half or nv_float16
          const vllm::ScalarTypeId w_type_id,  // weight ScalarType id
          const int threads,          // number of threads in a threadblock
          const int thread_m_blocks,  // number of 16x16 blocks in the m
                                      // dimension (batchsize) of the
                                      // threadblock
          const int thread_n_blocks,  // same for n dimension (output)
          const int thread_k_blocks,  // same for k dimension (reduction)
          const bool m_block_size_8,  // whether m_block_size == 8
                                      // only works when thread_m_blocks == 1
          const int stages,  // number of stages for the async global->shared
                             // fetch pipeline
          const int group_blocks,  // number of consecutive 16x16 blocks
                                   // with a separate quantization scale
          const bool is_zp_float   // is zero point of float16 type?
          >
__global__ void Marlin(MARLIN_KERNEL_PARAMS);

}
