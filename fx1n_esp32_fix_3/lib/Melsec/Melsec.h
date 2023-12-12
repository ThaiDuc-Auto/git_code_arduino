#ifndef MELSEC_H
#define MELSEC_H
#include <Arduino.h>

#define _serialMon c2

class Melsec
{
private:
    HardwareSerial &_serialPLC;
    int _baudrate = 9600; // set baudrate default

    void CheckSum(uint8_t *result, uint8_t *data, int size);
    String SumCheck(String data);
    int16_t StrToHex(String str);
    //int StrToHex(String str);
    int8_t StrToHex8(String str);
    uint16_t TimeReadContinous(float numOfReadPoint);
    uint16_t TimeWriteContinous(float numOfWritePoint);
    int OctToDec(int val);

    void WriteOutputBit(uint16_t startAdd, bool value);
    void WriteMemoryBit(uint16_t startAdd, bool value);
    void WriteStateBit(uint16_t startAdd, bool value);

public:
    enum Type
    {
        Memory = 1,
        Input = 2,
        Output = 3,
        State = 4,
    };

    Melsec(HardwareSerial &port, int baudrate);
    void init();

    uint8_t ReadByte(uint16_t startAdd, uint8_t type);
    int16_t ReadWord(uint16_t startAdd);
    int32_t ReadDWord(uint16_t startAdd);
    float ReadFloat(uint16_t startAdd);
    bool ReadMemory(uint16_t startAdd);
    bool ReadInput(uint16_t startAdd);
    bool ReadOutput(uint16_t startAdd);
    bool ReadState(uint16_t startAdd);

    void WriteBit(uint8_t type, uint16_t startAdd, bool value);
    void WriteByte(uint8_t type, uint16_t startAdd, uint8_t value);
    void WriteWord(uint16_t startAdd, int16_t value);
    void WriteDWord(uint16_t startAdd, int32_t value);
    void WriteFloat(uint16_t startAdd, float value);
};

union
{
    uint32_t i;
    float f;
} dataF;

#endif