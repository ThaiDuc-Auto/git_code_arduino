#include "Melsec.h"

Melsec::Melsec(HardwareSerial &port, int baudrate) : _serialPLC(port)
{
    _baudrate = baudrate;
}
void Melsec::init()
{
    _serialPLC.begin(_baudrate, SERIAL_7E1);
}

int Melsec::OctToDec(int val)
{
    int BASE = 1;
    int decimalNumber = 0;
    while (val > 0)
    {
        int last_digit = val % 10;
        val /= 10;
        decimalNumber += last_digit * BASE;
        BASE *= 8;
    }
    return decimalNumber;
}

void Melsec::CheckSum(uint8_t *result, uint8_t *data, int size)
{
    uint16_t sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum = (sum + data[i]);
    }
    String s = String(sum, HEX);
    s.toUpperCase();

    for (size_t i = 0; i < 2; i++)
    {
        if (s.length() > 2)
            result[i] = (uint8_t)(s[i + 1]);
        else
            result[i] = (uint8_t)(s[i]);
    }
}

String Melsec::SumCheck(String data)
{
    int sum = 0;
    for (int i = 0; i < data.length(); i++)
    {
        sum += (int8_t)data[i];
    }

    String res = String(sum, HEX);
    res.toUpperCase();
    res = res.substring(1);
    return res;
}

int16_t Melsec::StrToHex(String str)
{
    return (int)strtol(str.c_str(), 0, 16);
}

int8_t Melsec::StrToHex8(String str)
{
    return (int8_t)strtol(str.c_str(), 0, 8);
}
/*
Calculator Time Read Continute
*/
uint16_t Melsec::TimeReadContinous(float numOfReadPoint)
{
    float timeSendOneChar = 0.0;
    float intervalTime = 0.3;
    float maximumScan = 5.0;
    switch (_baudrate)
    {
    case 300:
        timeSendOneChar = 33.34f;
        break;

    case 600:
        timeSendOneChar = 16.67f;
        break;

    case 1200:
        timeSendOneChar = 8.34f;
        break;

    case 2400:
        timeSendOneChar = 4.17f;
        break;

    case 4800:
        timeSendOneChar = 2.08f;
        break;

    case 9600:
        timeSendOneChar = 1.04f;
        break;

    case 19200:
        timeSendOneChar = 0.52f;
        break;

    case 38400:
        timeSendOneChar = 0.26f;
        //timeSendOneChar = 1.04f;
        break;

    default:
        timeSendOneChar = 0.26f;
        break;
    }
     //return (uint16_t)((21+ 4 * numOfReadPoint) * timeSendOneChar + intervalTime + maximumScan);
    return (uint16_t)((21+ 4 * numOfReadPoint) * timeSendOneChar + intervalTime + maximumScan);
}
//uni16_t Melsec::
/*
Calculator Time Write Continute
*/
uint16_t Melsec::TimeWriteContinous(float numOfWritePoint)
{
    float timeSendOneChar = 0.0;
    float intervalTime = 0.3;
    float maximumScan = 5.0;
    //float maximumScan = 1.0;
    switch (_baudrate)
    {
    case 300:
        timeSendOneChar = 33.34f;
        break;

    case 600:
        timeSendOneChar = 16.67f;
        break;

    case 1200:
        timeSendOneChar = 8.34f;
        break;

    case 2400:
        timeSendOneChar = 4.17f;
        break;

    case 4800:
        timeSendOneChar = 2.08f;
        break;

    case 9600:
        timeSendOneChar = 1.04f;
        break;

    case 19200:
        timeSendOneChar = 0.52f;
        break;

    case 38400:
        timeSendOneChar = 0.26f;
        break;

    default:
        timeSendOneChar = 0.26f;
        break;
    }

    return (uint16_t)((20 + 4 * numOfWritePoint) * timeSendOneChar + intervalTime + maximumScan);
}

// Comment ReadWord Function
int16_t Melsec::ReadWord(uint16_t startAdd)
{
    int16_t result = 0;
    uint8_t byteBegin = 0x02;
    uint8_t byteEnd = 0x03;
    uint8_t byteComand[3] = {0x45, 0x30, 0x30};

    String str_startAdress = String((startAdd * 2 + 0x4000), 16);
    if (startAdd >= 8000)
    {
        str_startAdress = String(((startAdd - 8000) * 2 + 0x8000), 16);
    }
    uint8_t startAdress[str_startAdress.length()] = {};
    for (size_t i = 0; i < str_startAdress.length(); i++)
    {
        startAdress[i] = (int)str_startAdress[i];
    }

    String str_count = String(1 * 2, 16);
    uint8_t count[2] = {};
    count[0] = 0x30;
    count[1] = (uint8_t)str_count[0];

    uint8_t data[sizeof(byteComand) + sizeof(startAdress) + sizeof(count) + 1] = {};
    for (size_t i = 0; i < sizeof(byteComand); i++)
    {
        data[i] = byteComand[i];
    }
    for (size_t i = 0; i < sizeof(startAdress); i++)
    {
        data[i + sizeof(byteComand)] = startAdress[i];
    }
    for (size_t i = 0; i < sizeof(count); i++)
    {
        data[i + sizeof(byteComand) + sizeof(startAdress)] = count[i];
    }
    data[sizeof(data) - 1] = byteEnd;

    uint8_t crc[2] = {};
    CheckSum(crc, data, sizeof(data));

    uint8_t buff_send[sizeof(data) + 3];
    buff_send[0] = byteBegin;
    for (size_t i = 0; i < sizeof(buff_send); i++)
    {
        buff_send[i + 1] = data[i];
    }
    buff_send[sizeof(buff_send) - 2] = crc[0];
    buff_send[sizeof(buff_send) - 1] = crc[1];

    while (_serialPLC.available()) // Clear buffer Serial
    {
        _serialPLC.read();
    }
    _serialPLC.write(buff_send, sizeof(buff_send));

    //delay(TimeReadContinous(3.84));
    delay(TimeReadContinous(0.0384));
    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }
        strNum += (char)data[2];
        strNum += (char)data[3];
        strNum += (char)data[0];
        strNum += (char)data[1];

        result = StrToHex(strNum);
    }
    return result;
} 
/*

//Read Word
int16_t Melsec::ReadWord(uint16_t startAdd)
{
    int16_t result = 0;
    String sWriteData = "";
    String _command = "E00";
    String str_startAdress = String((startAdd * 2 + 0x4000), 16);
    if (startAdd >= 8000)
    {
        str_startAdress = String(((startAdd - 8000) * 2 + 0x8000), 16);
    }
    str_startAdress.toUpperCase();
    String strCount = "02";
    sWriteData = _command + str_startAdress + strCount + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_sent[sWriteData.length()] = {};
    for (size_t i = 0; i < sizeof(buff_sent); i++)
    {
        buff_sent[i] = (uint8_t)sWriteData[i];
    }
    _serialPLC.write(buff_sent, sizeof(buff_sent));
    //delay(TimeReadContinous(8000.0));
    //delay(TimeReadContinous(0.5));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};
     delay(TimeReadContinous(0.5));
    //while (_serialPLC.available())
    // {
    //    _serialPLC.readBytes(buff_rev, bytes);
    //    // _serialPLC.write(buff_rev, bytes);
    // }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }
        strNum += (char)data[2];
        strNum += (char)data[3];
        strNum += (char)data[0];
        strNum += (char)data[1];

        result = int16_t(StrToHex(strNum));
    }
    return result;
}
*/

//Read Memory

bool Melsec::ReadMemory(uint16_t startAdd)
{
    int startByte = startAdd / 8;
    int startBit = startAdd % 8;
    uint8_t arrBit[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    bool result = false;

    String sWriteData = "";
    String _command = "E00"; // 0: Read --- 1: Write
   // String _command = "E0"; // 0: Read --- 1: Write
    String _startAddress = String(startByte * 1 + 0x8800, HEX);
    if (startAdd >= 8000)
    {
        startByte = (startAdd - 8000) / 8;
        startBit = (startAdd - 8000) % 8;
        _startAddress = String(startByte * 1 + 0x8C00, HEX);
    }
    _startAddress.toUpperCase();
    String _count = "01";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_send[sWriteData.length()] = {};
    for (size_t i = 0; i < sWriteData.length(); i++)
    {
        buff_send[i] = (uint8_t)sWriteData[i];
    }

    _serialPLC.write(buff_send, sizeof(buff_send));

    delay(TimeReadContinous(0.5));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }

        strNum += (char)data[0];
        strNum += (char)data[1];

        result = (bool)(StrToHex(strNum) & arrBit[startBit]);
    }
    return result;
}

/*
Read Input
*/
bool Melsec::ReadInput(uint16_t startAdd)
{
    if ((startAdd % 10) > 7)
    {
        return false;
    }
    startAdd = OctToDec(startAdd);
    int startByte = startAdd / 8;
    int startBit = startAdd % 8;
    uint8_t arrBit[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    bool result = false;

    String sWriteData = "";
    String _command = "E00"; // 0: Read --- 1: Write
    String _startAddress = String(startByte * 1 + 0x8CA0, HEX);
    _startAddress.toUpperCase();
    String _count = "01";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_send[sWriteData.length()] = {};
    for (size_t i = 0; i < sWriteData.length(); i++)
    {
        buff_send[i] = (uint8_t)sWriteData[i];
    }

    while (_serialPLC.available())
    {
        _serialPLC.read();
    }

    _serialPLC.write(buff_send, sizeof(buff_send));
    delay(TimeReadContinous(8000.0));

    int bytes = _serialPLC.available();

    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }

        strNum += (char)data[0];
        strNum += (char)data[1];

        result = (bool)(StrToHex(strNum) & arrBit[startBit]);
    }
    return result;
}

/*
Read Output
*/
bool Melsec::ReadOutput(uint16_t startAdd)
{
    if ((startAdd % 10) > 7)
    {
        return false;
    }
    startAdd = OctToDec(startAdd);
    int startByte = startAdd / 8;
    int startBit = startAdd % 8;
    uint8_t arrBit[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    bool result = false;

    String sWriteData = "";
    String _command = "E00"; // 0: Read --- 1: Write
    String _startAddress = String(startByte * 1 + 0x8BC0, HEX);
    _startAddress.toUpperCase();
    String _count = "01";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_send[sWriteData.length()] = {};
    for (size_t i = 0; i < sWriteData.length(); i++)
    {
        buff_send[i] = (uint8_t)sWriteData[i];
    }

    _serialPLC.write(buff_send, sizeof(buff_send));

    delay(TimeReadContinous(0.5));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }

        strNum += (char)data[0];
        strNum += (char)data[1];

        result = (bool)(StrToHex(strNum) & arrBit[startBit]);
    }
    return result;
}

/*
Read State
*/
bool Melsec::ReadState(uint16_t startAdd)
{
    int startByte = startAdd / 8;
    int startBit = startAdd % 8;
    uint8_t arrBit[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    bool result = false;

    String sWriteData = "";
    String _command = "E00"; // 0: Read --- 1: Write
    String _startAddress = String(startByte * 1 + 0x8CE0, HEX);
    _startAddress.toUpperCase();
    String _count = "01";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_send[sWriteData.length()] = {};
    for (size_t i = 0; i < sWriteData.length(); i++)
    {
        buff_send[i] = (uint8_t)sWriteData[i];
    }

    _serialPLC.write(buff_send, sizeof(buff_send));

    delay(TimeReadContinous(0.5));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }

        strNum += (char)data[0];
        strNum += (char)data[1];

        result = (bool)(StrToHex(strNum) & arrBit[startBit]);
    }
    return result;
}

/*
Read Byte Input/Output/Memory/State
*/
uint8_t Melsec::ReadByte(uint16_t startAdd, uint8_t type)
{
    int startByte = startAdd;
    uint8_t result = 0;

    String sWriteData = "";
    String _command = "E00"; // 0: Read --- 1: Write
    String _startAddress = "";
    switch (type)
    {
    case Memory:
        _startAddress = String(startByte * 1 + 0x8800, HEX);
        if (startAdd >= 8000)
        {
            startByte = (startAdd - 8000) / 8;
            _startAddress = String(startByte * 1 + 0x8C00, HEX);
        }
        break;

    case Input:
        // startAdd = OctToDec(startAdd);
        _startAddress = String(startByte * 1 + 0x8CA0, HEX);
        break;

    case Output:
        // startAdd = OctToDec(startAdd);
        _startAddress = String(startByte * 1 + 0x8BC0, HEX);
        break;

    case State:
        _startAddress = String(startByte * 1 + 0x8CE0, HEX);
        break;

    default:
        return 0;
        break;
    }
    _startAddress.toUpperCase();

    String _count = "01";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_send[sWriteData.length()] = {};
    for (size_t i = 0; i < sWriteData.length(); i++)
    {
        buff_send[i] = (uint8_t)sWriteData[i];
    }

    _serialPLC.write(buff_send, sizeof(buff_send));

    delay(TimeReadContinous(0.5));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }

        strNum += (char)data[0];
        strNum += (char)data[1];

        result = (uint8_t)(StrToHex(strNum));
    }
    return result;
}

/*
Read DWord
*/
int32_t Melsec::ReadDWord(uint16_t startAdd)
{
    int32_t result = 0;
    String sWriteData = "";
    String _command = "E00";
    String str_startAdress = String((startAdd * 2 + 0x4000), 16);
    if (startAdd >= 8000)
    {
        str_startAdress = String(((startAdd - 8000) * 2 + 0x8000), 16);
    }
    str_startAdress.toUpperCase();
    String strCount = "04";
    sWriteData = _command + str_startAdress + strCount + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_sent[sWriteData.length()] = {};
    for (size_t i = 0; i < sizeof(buff_sent); i++)
    {
        buff_sent[i] = (uint8_t)sWriteData[i];
    }
    _serialPLC.write(buff_sent, sizeof(buff_sent));
    delay(TimeReadContinous(2.0));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNumLow = "";
        String strNumHigh = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }
        strNumHigh += (char)data[6];
        strNumHigh += (char)data[7];
        strNumHigh += (char)data[4];
        strNumHigh += (char)data[5];
        strNumLow += (char)data[2];
        strNumLow += (char)data[3];
        strNumLow += (char)data[0];
        strNumLow += (char)data[1];
        uint16_t numLow = StrToHex(strNumLow);
        uint16_t numHigh = StrToHex(strNumHigh);
        result = ((int32_t)numHigh) << 16 | numLow;
    }
    return result;
}

/*
Read Float
*/
float Melsec::ReadFloat(uint16_t startAdd)
{
    float result = 0;
    String sWriteData = "";
    String _command = "E00";
    String str_startAdress = String((startAdd * 2 + 0x4000), 16);
    if (startAdd >= 8000)
    {
        str_startAdress = String(((startAdd - 8000) * 2 + 0x8000), 16);
    }
    str_startAdress.toUpperCase();
    String strCount = "04";
    sWriteData = _command + str_startAdress + strCount + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    uint8_t buff_sent[sWriteData.length()] = {};
    for (size_t i = 0; i < sizeof(buff_sent); i++)
    {
        buff_sent[i] = (uint8_t)sWriteData[i];
    }
    _serialPLC.write(buff_sent, sizeof(buff_sent));
    delay(TimeReadContinous(2.0));

    int bytes = _serialPLC.available();
    byte buff_rev[bytes] = {0};

    while (_serialPLC.available())
    {
        _serialPLC.readBytes(buff_rev, bytes);
    }

    uint8_t crc_res[2] = {};
    uint8_t data_check_crc[sizeof(buff_rev) - 3] = {};

    for (size_t i = 0; i < sizeof(data_check_crc); i++)
    {
        data_check_crc[i] = buff_rev[i + 1];
    }

    CheckSum(crc_res, data_check_crc, sizeof(data_check_crc));

    if (buff_rev[sizeof(buff_rev) - 2] == crc_res[0] && buff_rev[sizeof(buff_rev) - 1] == crc_res[1])
    {
        uint8_t data[sizeof(buff_rev) - 4] = {};
        String strNum = "";
        for (size_t i = 0; i < sizeof(data); i++)
        {
            data[i] = buff_rev[i + 1];
        }
        strNum += (char)data[6];
        strNum += (char)data[7];
        strNum += (char)data[4];
        strNum += (char)data[5];
        strNum += (char)data[2];
        strNum += (char)data[3];
        strNum += (char)data[0];
        strNum += (char)data[1];

        dataF.i = strtoul(strNum.c_str(), NULL, 16);
        result = dataF.f;
    }

    return result;
}

/******************************************************************************************************/

/*
Write Output Bit
*/
void Melsec::WriteOutputBit(uint16_t startAdd, bool value)
{
    uint16_t startAddBase8 = OctToDec(startAdd);
    ///uint16_t startByte = (startAddBase8 / 173) + 0x5E;
    uint16_t startByte = (startAddBase8 / 173) + 0x5E;
    uint16_t bitAddress = startAddBase8 % 173;
    String strStartByte = String(startByte, HEX);
    strStartByte.toUpperCase();
    while (strStartByte.length() < 2)
    {
        strStartByte = "0" + strStartByte;
    }

    String strBitAddress = String(bitAddress, HEX);
    strBitAddress.toUpperCase();
    while (strBitAddress.length() < 2)
    {
        strBitAddress = "0" + strBitAddress;
    }
    String sWriteData = "";
    if (value)
    {
        sWriteData = "E7";
    }
    else
    {
        sWriteData = "E8";
    }
    sWriteData = sWriteData + strBitAddress + strStartByte + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);
    _serialPLC.print(sWriteData);
    // neu k dc thi tang thoi gian TimeWrite cho no nhanh len  nha pro
    delay(TimeWriteContinous(0.5));
    //delay(TimeWriteContinous(12.0));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}
/*
Write Memory Bit
*/
void Melsec::WriteMemoryBit(uint16_t startAdd, bool value)
{
    uint16_t startByte;
    uint16_t bitAddress;
    if (startAdd >= 8000)
    {
        startByte = ((startAdd - 8000) / 256) + 0x60;
        bitAddress = (startAdd - 8000) % 256;
    }
    else
    {
        startByte = (startAdd / 256) + 0x40;
        bitAddress = startAdd % 256;
    }

    String strStartByte = String(startByte, HEX);
    strStartByte.toUpperCase();
    while (strStartByte.length() < 2)
    {
        strStartByte = "0" + strStartByte;
    }

    String strBitAddress = String(bitAddress, HEX);
    strBitAddress.toUpperCase();
    while (strBitAddress.length() < 2)
    {
        strBitAddress = "0" + strBitAddress;
    }
    String sWriteData = "";
    if (value)
    {
        sWriteData = "E7";
    }
    else
    {
        sWriteData = "E8";
    }
    sWriteData = sWriteData + strBitAddress + strStartByte + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);
    _serialPLC.print(sWriteData);
    delay(TimeWriteContinous(0.5));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}

/*
Write State Bit
*/
void Melsec::WriteStateBit(uint16_t startAdd, bool value)
{
    uint16_t startByte = (startAdd / 256) + 0x67;
    uint16_t bitAddress = startAdd % 256;

    String strStartByte = String(startByte, HEX);
    strStartByte.toUpperCase();
    while (strStartByte.length() < 2)
    {
        strStartByte = "0" + strStartByte;
    }

    String strBitAddress = String(bitAddress, HEX);
    strBitAddress.toUpperCase();
    while (strBitAddress.length() < 2)
    {
        strBitAddress = "0" + strBitAddress;
    }
    String sWriteData = "";
    if (value)
    {
        sWriteData = "E7";
    }
    else
    {
        sWriteData = "E8";
    }
    sWriteData = sWriteData + strBitAddress + strStartByte + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);
    _serialPLC.print(sWriteData);
    delay(TimeWriteContinous(0.5));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}

/*
Write Bit
*/
void Melsec::WriteBit(uint8_t type, uint16_t startAdd, bool value)
{
    switch (type)
    {
    case Memory:
        WriteMemoryBit(startAdd, value);
        break;

    case Output:
        WriteOutputBit(startAdd, value);
        break;

    case State:
        WriteStateBit(startAdd, value);
        break;

    default:
        break;
    }
}

/*
Write Byte
*/
void Melsec::WriteByte(uint8_t type, uint16_t startAdd, uint8_t value)
{
    String sWriteData = "";
    String s = String(value, HEX);
    while (s.length() < 2)
    {
        s = "0" + s;
    }
    s.toUpperCase();
    sWriteData = s;
    String _command = "E10"; // 0: Read --- 1: Write

    String _startAddress = "";
    switch (type)
    {
    case Output:
        _startAddress = String(startAdd * 1 + 0x8BC0, HEX);
        break;

    case Memory:
        _startAddress = String(startAdd * 1 + 0x8800, HEX);
        if (startAdd >= 8000)
        {
            _startAddress = String((startAdd - 8000) * 1 + 0xBC00, HEX);
        }
        break;

    case State:
        _startAddress = String(startAdd * 1 + 0x8CE0, HEX);
        break;

    default:
        return;
        break;
    }

    _startAddress.toUpperCase();
    String _count = "01";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);

    _serialPLC.print(sWriteData);

    delay(TimeWriteContinous(0.5));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}

/*
Write Word
*/
void Melsec::WriteWord(uint16_t startAdd, int16_t value)
{
    String sWriteData = "";
    String s = String(value, HEX);
    while (s.length() < 4)
    {
        s = "0" + s;
    }
    sWriteData = s.substring(2) + s.substring(0, 2);
    sWriteData.toUpperCase();

    String command = "E10";
    String str_startAdress = String((startAdd * 2 + 0x4000), 16);
    if (startAdd >= 8000)
    {
        str_startAdress = String(((startAdd - 8000) * 2 + 0x8000), 16);
    }
    str_startAdress.toUpperCase();
    String strCount = "02";
    sWriteData = command + str_startAdress + strCount + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);
    _serialPLC.print(sWriteData);
    delay(TimeWriteContinous(1.0));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}

/*
Write DWord
*/
void Melsec::WriteDWord(uint16_t startAdd, int32_t value)
{
    String sWriteData = "";
    String s = String(value, HEX);
    while (s.length() < 8)
    {
        s = "0" + s;
    }
    sWriteData += s.substring(6) + s.substring(4, 6) + s.substring(2, 4) + s.substring(0, 2);
    sWriteData.toUpperCase();
    String _command = "E10"; // 0: Read --- 1: Write
    String _startAddress = String(startAdd * 2 + 0x4000, HEX);
    if (startAdd >= 8000)
    {
        _startAddress = String(startAdd * 2 + 0x8000, HEX);
    }
    _startAddress.toUpperCase();
    String _count = "04";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);
    _serialPLC.print(sWriteData);
    delay(TimeWriteContinous(2.0));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}


/*
Write Float
*/
void Melsec::WriteFloat(uint16_t startAdd, float value)
{
    String sWriteData = "";
    dataF.f = value;
    String s = String(dataF.i, HEX);
    while (s.length() < 8)
    {
        s = "0" + s;
    }
    sWriteData += s.substring(6) + s.substring(4, 6) + s.substring(2, 4) + s.substring(0, 2);
    sWriteData.toUpperCase();

    String _command = "E10"; // 0: Read --- 1: Write
    String _startAddress = String(startAdd * 2 + 0x4000, HEX);
    if (startAdd >= 8000)
    {
        _startAddress = String(startAdd * 2 + 0x8000, HEX);
    }
    _startAddress.toUpperCase();
    String _count = "04";
    sWriteData = _command + _startAddress + _count + sWriteData + (char)(3);
    sWriteData = (char)(2) + sWriteData + SumCheck(sWriteData);
    _serialPLC.print(sWriteData);
    delay(TimeWriteContinous(2.0));
    while (_serialPLC.available())
    {
        _serialPLC.read();
    }
}