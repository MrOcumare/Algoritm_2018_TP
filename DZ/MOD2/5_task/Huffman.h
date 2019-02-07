
#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char byte;
#define interface struct

interface IInputStream {
	// Возвращает false, если поток закончился
	virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
	virtual void Write(byte value) = 0;
};


// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);

class FInputStream : IInputStream {
public:
    FInputStream(std::string name) : f(name, std::ios::out | std::ios::binary) {}

    virtual bool Read(byte& value) override {
        if (f.eof()) {
            return false;
        }

        return f.get();
    }
    

private:
    std::ifstream f;

};
  
class FOutputStream : IOutputStream {
public:
    FOutputStream(std::string name) : o(name, std::ios::out | std::ios::binary) {}
    virtual void Write(byte value) override {
        o << value;
    }  
    
private: 
     std::ofstream o; 
};

int main()
{
    FInputStream input("1.txt");

    FOutputStream output("output.txt");

    Encode(input, output);
    Decode(output, input);    

}