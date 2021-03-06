#include "ActivationFunctionsTestCase.h"
#include <OpenANN/ActivationFunctions.h>

void ActivationFunctionsTestCase::run()
{
  RUN(ActivationFunctionsTestCase, softmax);
  RUN(ActivationFunctionsTestCase, logistic);
  RUN(ActivationFunctionsTestCase, normaltanh);
  RUN(ActivationFunctionsTestCase, linear);
  RUN(ActivationFunctionsTestCase, rectifier);
}

void ActivationFunctionsTestCase::softmax()
{
  const int N = 1000;
  Eigen::MatrixXd a = Eigen::VectorXd::Random(N).transpose();
  OpenANN::softmax(a);
  ASSERT_EQUALS_DELTA(1.0, a.sum(), 1e-3);
  ASSERT_WITHIN(a.minCoeff(), 0.0, 1.0);
  ASSERT_WITHIN(a.maxCoeff(), 0.0, 1.0);
}

void ActivationFunctionsTestCase::logistic()
{
  const int N = 1000;
  Eigen::MatrixXd a = Eigen::VectorXd::Random(N) * 10.0;
  Eigen::MatrixXd z = Eigen::VectorXd::Zero(N);
  OpenANN::logistic(a, z);
  ASSERT_WITHIN(z.minCoeff(), 0.0, 0.2);
  ASSERT_WITHIN(z.maxCoeff(), 0.8, 1.0);

  Eigen::MatrixXd gd = Eigen::VectorXd::Zero(N);
  OpenANN::logisticDerivative(z, gd);
  ASSERT_WITHIN(gd.minCoeff(), 0.0, 1.0);
  ASSERT_WITHIN(gd.maxCoeff(), 0.0, 1.0);
}

void ActivationFunctionsTestCase::normaltanh()
{
  const int N = 1000;
  Eigen::MatrixXd a = Eigen::VectorXd::Random(N) * 10.0;
  Eigen::MatrixXd z = Eigen::VectorXd::Zero(N);
  OpenANN::normaltanh(a, z);
  ASSERT_WITHIN(z.minCoeff(), -1.0, -0.5);
  ASSERT_WITHIN(z.maxCoeff(), 0.5, 1.0);

  Eigen::MatrixXd gd = Eigen::VectorXd::Zero(N);
  OpenANN::normaltanhDerivative(z, gd);
  ASSERT_WITHIN(gd.minCoeff(), 0.0, 1.0);
  ASSERT_WITHIN(gd.maxCoeff(), 0.0, 1.0);
}

void ActivationFunctionsTestCase::linear()
{
  const int N = 1000;
  Eigen::MatrixXd a = Eigen::VectorXd::Random(N) * 10.0;
  Eigen::MatrixXd z = Eigen::VectorXd::Zero(N);
  OpenANN::linear(a, z);
  ASSERT_EQUALS(a.minCoeff(), z.minCoeff());
  ASSERT_EQUALS(a.maxCoeff(), z.maxCoeff());

  Eigen::MatrixXd gd = Eigen::VectorXd::Zero(N);
  Eigen::MatrixXd expected = Eigen::VectorXd::Ones(N);
  OpenANN::linearDerivative(gd);
  ASSERT_EQUALS(gd.sum(), expected.sum());
}

void ActivationFunctionsTestCase::rectifier()
{
  const int N = 1000;
  Eigen::MatrixXd a = Eigen::MatrixXd::Random(1, N) * 10.0;
  Eigen::MatrixXd z = Eigen::MatrixXd::Zero(1, N);
  OpenANN::rectifier(a, z);
  ASSERT_EQUALS(0.0, z.minCoeff());
  ASSERT_EQUALS(a.maxCoeff(), z.maxCoeff());

  Eigen::MatrixXd gd = Eigen::MatrixXd::Zero(1, N);
  Eigen::MatrixXd expected = Eigen::MatrixXd::Ones(1, N);
  for(int i = 0; i < N; i++)
    expected(i) *= (double)(z(i) > 0.0);
  OpenANN::rectifierDerivative(z, gd);
  ASSERT_EQUALS(gd.sum(), expected.sum());
}
