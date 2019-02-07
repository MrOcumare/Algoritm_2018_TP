#include <string>
using namespace std;


#ifndef HUFFMAN_V2_HUFFMAN_H
#define HUFFMAN_V2_HUFFMAN_H

typedef unsigned char byte;

class IInputStream {
    // Возвращает false, если поток закончился
public:
    virtual bool Read(byte& value) = 0;
};

class IOutputStream {
public:
    virtual void Write(byte value) = 0;
};
class COutputStream : public IInputStream {
public:
    explicit COutputStream( string fileName  );

// Возвращает false, если поток закончился
    virtual bool Read( byte& value ) override;

    string outputFileName;
};

class CInputStream : public IInputStream {
public:
    explicit CInputStream( string fileName  );

// Возвращает false, если поток закончился
    virtual bool Read( byte& value ) override;

    string inputFileName;
};


CInputStream::CInputStream(string fileName) : inputFileName( fileName ) {}

bool CInputStream::Read(byte &value) {
    return false;
}

COutputStream::COutputStream( string fileName ) : outputFileName( fileName ) {}

bool COutputStream::Read(byte &value) {
    return false; 
}
#endif //HUFFMAN_V2_HUFFMAN_H