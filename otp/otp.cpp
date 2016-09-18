#include "otp.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "Expected filename as argumnt" << std::endl;
    return 1;
  }

  std::string message;
  std::ifstream is(argv[1], std::ios::binary);
  if (!is) {
    std::cout << "NO such file" << std::endl;
    return 1;
  }

  std::vector<char> buffer(MESSAGE_LENGTH);
  is.read(&buffer[0], MESSAGE_LENGTH);
  message.assign(buffer.begin(), buffer.end());
  std::cout << "Message length: " + std::to_string(message.size()) << std::endl;

  std::cout << "-------Raw Array-------" << std::endl;
  RawOTPEncryptor *rawEncryptor = new RawOTPEncryptor(message);
  rawEncryptor->encdec();
  rawEncryptor->encdec();
  std::string result = rawEncryptor->getMessage();
  std::cout << "Input text and enc-dec result are ";
  std::cout << ((message == result) ? "equal" : "not equal") << std::endl;

  std::cout << "-------Vector<uint> (int iteration)-------" << std::endl;
  VectorOTPEncryptor *vectorEncryptor = new VectorOTPEncryptor(message);
  vectorEncryptor->encdec();
  vectorEncryptor->encdec();
  result = vectorEncryptor->getMessage();
  std::cout << "Input text and enc-dec result are ";
  std::cout << result.size() << std::endl;
  std::cout << ((message == result) ? "equal" : "not equal") << std::endl;

  return 0;
}
