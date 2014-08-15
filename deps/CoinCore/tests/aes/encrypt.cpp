////////////////////////////////////////////////////////////////////////////////
//
// encrypt.cpp
//
// Copyright (c) 2014 Eric Lombrozo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <aes.h>
#include <hash.h>
#include <random.h>
#include <stdutils/uchar_vector.h>

#include <iostream>

using namespace AES;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "# Usage: " << argv[0] << " <passphrase> <plaintext>" << endl;
        return -1;
    }

    try
    {
        secure_bytes_t passphrase((unsigned char*)argv[1], (unsigned char*)argv[1] + strlen(argv[1]));
        secure_bytes_t key = sha256_2(passphrase);

        secure_bytes_t data((unsigned char*)argv[2], (unsigned char*)argv[2] + strlen(argv[2]));

        uint64_t salt = random_salt();
        bytes_t cipherdata = encrypt(passphrase, data, true, salt);

        cout << "Salt:           " << salt << endl;
        cout << "Hex ciphertext: " << uchar_vector(cipherdata).getHex() << endl;
    }
    catch (const AESException& e)
    {
        cerr << "AES Exception: " << e.what() << endl;
        return e.code();
    }
    catch (const exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return -2;
    }    

    return 0;
}