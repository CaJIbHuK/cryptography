#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

const int MESSAGE_LENGTH = 5000;
using uchar = unsigned char;
using DWORD = unsigned int;

template <typename T> class OTPEncryptor {
protected:
  T m;
  std::vector<uchar> key = std::vector<uchar>(MESSAGE_LENGTH);

public:
  OTPEncryptor();
  virtual ~OTPEncryptor(){};
  virtual void encdec() = 0;
  virtual std::string getMessage() = 0;

private:
  void genAndSetKey();
};

class RawOTPEncryptor : OTPEncryptor<uchar *> {
public:
  RawOTPEncryptor(std::string &message);
  virtual ~RawOTPEncryptor(){};
  void encdec() override;
  std::string getMessage() override; // override ensures that method is virtual
};

class VectorOTPEncryptor : OTPEncryptor<std::vector<DWORD>> {
protected:
  using OTPEncryptor::m;
  using OTPEncryptor::key;

public:
  VectorOTPEncryptor(std::string &message);
  virtual ~VectorOTPEncryptor(){};
  void encdec() override;
  std::string getMessage() override;
};

class IteratorOTPEncryptor : public VectorOTPEncryptor {
public:
  IteratorOTPEncryptor(std::string &message) : VectorOTPEncryptor(message){};
  virtual ~IteratorOTPEncryptor(){};
  void encdec() override;
};
