#pragma once

#include <Eigen/Dense>
#include <vector>

namespace OpenANN
{

/**
 * @class CompressionMatrixFactory
 *
 * Creates several types of matrices for compression.
 *
 * A compression matrix \f$ \Phi \f$ can either be used to compress a data
 * vector or the parameters of a Learner.
 */
class CompressionMatrixFactory
{
public:
  bool compress;
  enum Transformation
  {
    DCT, GAUSSIAN, SPARSE_RANDOM, AVERAGE, EDGE
  } transformation;
  int inputDim;
  int paramDim;

  CompressionMatrixFactory();
  CompressionMatrixFactory(int inputDim, int paramDim,
                           Transformation transformation = DCT);
  void createCompressionMatrix(Eigen::MatrixXd& cm);

private:
  void fillCompressionMatrix(Eigen::MatrixXd& cm);
};

}
