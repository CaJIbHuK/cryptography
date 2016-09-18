#include "otplib.h"

template <typename T> OTPEncryptor<T>::OTPEncryptor() { genAndSetKey(); }

template <typename T> void OTPEncryptor<T>::genAndSetKey() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uchar> dist(0, 255);
  std::generate(key.begin(), key.end(), [&dist, &gen] { return dist(gen); });
};

RawOTPEncryptor::RawOTPEncryptor(std::string &message) {
  this->m = new uchar[MESSAGE_LENGTH];
  std::copy(message.begin(), message.end(), this->m);
}
void RawOTPEncryptor::encdec() {
  int i = 0;
  for (uchar *ch = m, *k = key.data(); i < MESSAGE_LENGTH; i++, ch++, k++)
    (*ch) ^= (*k);
}

std::string RawOTPEncryptor::getMessage() {
  return std::string(reinterpret_cast<char *>(m), MESSAGE_LENGTH);
}

VectorOTPEncryptor::VectorOTPEncryptor(std::string &message) {

  int length = (MESSAGE_LENGTH + 4 - 1) / 4; // ceiling
  this->m = std::vector<DWORD>(length);
  for (std::string::iterator it = message.begin(); it < message.end();) {
    DWORD v = 0;
    for (uchar i = 0; i < 4 && it < message.end(); i++, it++) {
      v += (*it) << (i * 8);
    }
    this->m.push_back(v);
  }
}

void VectorOTPEncryptor::encdec() {
  std::vector<uchar>::iterator keyIt = key.begin();
  int length = m.size();
  for (int i = 0; i < length; i++) {
    DWORD k = 0;
    for (int c = 0; c < 4 && keyIt < key.end(); c++, keyIt++) {
      k += (*keyIt) << (c * 8);
    }
    m[i] ^= k;
  }
}

std::string VectorOTPEncryptor::getMessage() {
  std::vector<uchar> messageBytes;
  for (std::vector<DWORD>::iterator mIt = m.begin(); mIt < m.end(); mIt++) {
    for (int i = 0; i < 4; i++) {
      messageBytes.push_back((char)((*mIt) >> (i * 8)));
    }
  }
  std::cout << messageBytes.size() << std::endl;
  return std::string(messageBytes.begin(), messageBytes.end());
}
