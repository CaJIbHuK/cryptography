#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

const size_t MESSAGE_LENGTH = 5000;

template <typename T> class OTPEncryptor {
protected:
  T m;
  std::vector<char> key = std::vector<char>(MESSAGE_LENGTH);

public:
  OTPEncryptor();
  virtual ~OTPEncryptor(){};
  virtual void encdec() = 0;
  virtual std::string &getMessage();

private:
  void genAndSetKey();
};

class RawOTPEncryptor : OTPEncryptor<char *> {
public:
  RawOTPEncryptor(const std::string &message);
  virtual ~RawOTPEncryptor(){};
  void encdec() override;
  std::string &getMessage() override; // ensures that method is virtual
};

class VectorOTPEncryptor : OTPEncryptor<std::vector<char>> {
protected:
  using OTPEncryptor::m;
  using OTPEncryptor::key;

public:
  VectorOTPEncryptor(const std::string &message);
  virtual ~VectorOTPEncryptor(){};
  void encdec() override;
  std::string &getMessage() override; // ensures that method is virtual
};

class IteratorOTPEncryptor : VectorOTPEncryptor {
public:
  IteratorOTPEncryptor(const std::string &message);
  ~IteratorOTPEncryptor();
  void encdec() override;
};
