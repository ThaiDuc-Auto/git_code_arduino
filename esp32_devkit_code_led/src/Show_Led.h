
//------------------------------------------------------ ATME VIET NAM ---------------------------------------------------
//-------------- https://www.atme.vn --------------- thu.vo.lhu@gmail.com ------------- 0983 383 283 ---------------------
//------------------------------- CHUONG TRINH HIEN THI LED MATRIX FULL COLOR P5 INDOOR YLR ------------------------------
/*
char* ki_tu[]={
               "À","Á","Ạ","Ả","Ã","Đ",         
               "Â","Ấ","Ầ","Ẫ","Ậ","Ẩ",
               "Ă","Ằ","Ắ","Ẵ","Ẳ","Ặ",
               "Ò","Ó","Ọ","Õ","Ỏ",
               "Ô","Ố","Ồ","Ộ","Ổ","Ỗ",
               "Ơ","Ớ","Ờ","Ợ","Ỡ","Ở",
               "È","É","Ẹ","Ẽ","Ẻ",
               "Ế","Ề","Ễ","Ê","Ệ","Ể",
               "Ị","Ì","Í","Ĩ","Ỉ",
               "Ú","Ù","Ũ","Ụ","Ủ",
               "Ư","Ứ","Ừ","Ữ","Ự","Ử",
               "Ý","Ỷ","Ỳ","Ỹ","Ỵ"
               "à","á","ạ","ả","ã","đ",         
               "â","ấ","ầ","ẫ","ậ","ẩ",
               "ă","ằ","ắ","ẵ","ả","ặ",
               "ò","ó","ọ","õ","ỏ",
               "ô","ố","ồ","ộ","ổ","ỗ",
               "ơ","ớ","ờ","ợ","ỡ","ở",
               "è","é","ẹ","ẽ","ẻ",
               "ế","ề","ễ","ê","ệ","ể",
               "ị","ì","í","ĩ","ỉ",
               "ú","ù","ũ","ụ","ủ",
               "ư","ứ","ừ","ữ","ự","ử",
               "ý","ỳ","ỷ","ỹ","ỵ"
              };
char* ma_ki_tu[]={
             "\xC0","\xC1","\xE4","\xBF","\xC3","\xD0", // "À","Á","Ạ","Ả","Ã","Đ",
             "\xC2","\xC6","\xC7","\xE0","\xE1","\xBE", //"Â","Ấ","Ầ","Ẫ","Ậ","Ẩ",
             "\xC4","\xE2","\xE3","\xE5","\xDB","\xDB", //"Ă","Ằ","Ắ","Ẵ","Ẳ","Ặ",
             "\xD2","\xD3","\xD5","\xD6","\xF0",        //"Ò","Ó","Ọ","Õ","Ỏ",
             "\xD4","\xF2","\xF3","\xF4","\xD1","\xDF", //"Ô","Ố","Ồ","Ộ","Ổ","Ỗ",
             "\xD7","\xD8","\xF6","\xF7","\xF8","\xDE", //"Ơ","Ớ","Ờ","Ợ","Ỡ","Ở",
             "\xC8","\xC9","\xEB","\xE7","\xED",        //"È","É","Ẹ","Ẽ","Ẻ",
             "\xCA","\xCB","\xEA","\xE8","\xE9","\xEE", //"Ế","Ề","Ễ","Ê","Ệ","Ể",
             "\xEF","\xCC","\xCD","\xCE","\xCF",        //"Ị","Ì","Í","Ĩ","Ỉ",
             "\xDA","\xD9","\xF9","\xFA","\xF1",        //"Ú","Ù","Ũ","Ụ","Ủ",
             "\xDC","\xFB","\xDB","\xFC","\xEC","\xBB",//"Ư","Ứ","Ừ","Ữ","Ự","Ử",// Ự Ỳ Ỷ Ỹ Ỵ "\xEC","\xFD","\xBA","\xFF","\xDD"
             "\xB9","\xBA","\xFD","\xFF","\xDD"         //"Ý","Ỷ","Ỳ","Ỹ","Ỵ"
            };
 */
 
// ham giai ma ascii
/*
int giai_ma(String m)
{
  int k;
  //if(m=='F')
  if(m=="f")
  {
    k=15;
  }else if(m=="e")//if(m=='E')
  {
    k=14;
  }else if(m=="d")//if(m=='D')
  {
    k=13;
  }else if(m=="c")//if(m=='C')
  {
    k=12;
  }else if(m=="b")//if(m=='B')
  {
    k=11;
  }else if(m=="a")//if(m=='A')
  {
    k=10;
  }else
  { 
    //k= m.toInt();
    k=m.toInt();
  }
  return k;
}
// tat ca cac ham va ki tu giai ma
char* adStrings[] = {
                     
                     "\x20","\x21","\x22","\x23","\x24","\x25","\x26","\x27","\x28","\x29","\x2A","\x2B","\x2C","\x2D","\x2E","\x2F",
                    "\x30","\x31","\x32","\x33","\x34","\x35","\x36","\x37","\x38","\x39","\x3A","\x3B","\x3C","\x3D","\x3E","\x3F",
                   "\x40","\x41","\x42","\x43","\x44","\x45","\x46","\x47","\x48","\x49","\x4A","\x4B","\x4C","\x4D","\x4E","\x4F",
                  "\x50","\x51","\x52","\x53","\x54","\x55","\x56","\x57","\x58","\x59","\x5A","\x5B","\x5C","\x5D","\x5E",
                 "\x61","\x62","\x63","\x64","\x65","\x66","\x67","\x68","\x69","\x6A","\x6B","\x6C","\x6D","\x6E","\x6F",
                "\x70","\x71","\x72","\x73","\x74","\x75","\x76","\x77","\x78","\x79","\x7A","\x7B","\x7C","\x7D","\x7E","\x7F"
                };
//lent_1=
char* MA_ASCII[] = {
                    
                    "20","21","22","23","24","25","26","27","28","29","2a","2b","2c","2d","2e","2f",
                    "30","31","32","33","34","35","36","37","38","39","3a","3b","3c","3d","3e","3f",
                    "40","41","42","43","44","45","46","47","48","49","4a","4b","4c","4d","4e","4f",
                    "50","51","52","53","54","55","56","57","58","59","5a","5b","5c","5d","5e",
                    "61","62","63","64","65","66","67","68","69","6a","6b","6c","6d","6e","6f",
                    "70","71","72","73","74","75","76","77","78","79","7a","7b","7c","7d","7e","7f",
                    }; /// BANG MA DEMO ASCII 28 NHA PRO

  // giai ma 2 byte     // co the bo sung 1 so ki tu in thuong vao cg ok la nha               
char* Ma_2bit[]={                                                   // BANG MA 2 BIT NHA
                  "\xC3\x80","\xC3\x81","\xC3\x82","\xC4\x82","\xC3\x83",                        // À Á Â Ă Ã 
                  "\xC4\x90","\xC3\x88","\xC3\x89","\xC3\x8A","\xC3\x8C","\xC3\x8D","\xC4\xAC",  // Đ È É Ê Ì Í Ĩ 
                  "\xC3\x92","\xC3\x93","\xC3\x95","\xC3\x94","\xC6\xA0","\xC3\x99","\xC3\x9A",  // Ò Ó Õ Ô Ơ Ù Ú                                                                             // Ò Ó Õ Ô Ơ Ù Ú
                  "\xC5\xA8","\xC6\xAF","\xC3\x9D",                                                //Ũ Ư Ý
                  "\xC3\xA0","\xC3\xA1","\xC3\xA2","\xC4\x83","\xC3\xA3",                        // à á â ă ã
                  "\xC4\x91","\xC3\xA8","\xC3\xA9","\xC3\xAA","\xC3\xAC","\xC3\xAD","\xC4\xA9",  //đ è é ê ì í ĩ
                  "\xC3\xB2","\xC3\xB3","\xC3\xB5","\xC3\xB4","\xC6\xA1","\xC3\xB9","\xC3\xBA",  //ò ó õ ô ơ ù ú
                  "\xC5\xA9","\xC6\xB0","\xC3\xBD"                                               //ũ ư ý
               };
char* MA_ASCII_2[]={"80","81","82","82","83",
                    "90","88","89","8a","8c","8d","ac",
                    "92","93","95","94","a0","99","9a",
                    "a8","af","9d",
                    "a0","a1","a2","83","a3",
                    "91","a8","a9","aa","ac","ad","a9",
                    "b2","b3","b5","b4","a1","b9","ba",
                    "a9","b0","bd"
                    };
char*MA_Phu_2[]={"c3","c3","c3","c4","c3",
                 "c4","c3","c3","c3","c3","c3","c4",
                 "c3","c3","c3","c3","c6","c3","c3",
                 "c5","c6","c3",
                 "c3","c3","c3","c4","c3",
                 "c4","c3","c3","c3","c3","c3","c4",
                 "c3","c3","c3","c3","c6","c3","c3",
                 "c5","c6","c3"
                 };
char* Ma_font_2byte[]={
                       "\xC0","\xC1","\xE1","\xC4","\xC3",                    // À Á Â Ă Ã 
                       "\xD0","\xC8","\xC9","\xE8","\xCC","\xCD","\xCE",      // Đ È É Ê Ì Í Ĩ
                       "\xD2","\xD3","\xD6","\xD4","\xD7","\xDA","\xD9",      // Ò Ó Õ Ô Ơ Ù Ú 
                       "\xF9","\xDC","\xB9",                                  // Ũ Ư Ý
                       "\x81","\x82","\x86","\x8C","\x89",                    // à á â ă ã
                       "\x92","\xA3","\xA4","\xA9","\xB0","\xAF","\xB1",      // đ è é ê ì í ĩ
                       "\x93","\x94","\x96","\x98","\x9E","\xBC","\xBB",      // ò ó õ ô ơ ù ú
                       "\x7F","\xB6","\xED"                                   // ũ ư ý
               };          

// giai ma so luong ki tu 3 byte

char* Ma_3bit[]={
                 "\xE1\xBA\xA2","\xE1\xBA\xA0","\xE1\xBA\xB0","\xE1\xBA\xAE","\xE1\xBA\xB2",   // Ả Ạ Ằ Ắ Ẳ
                 "\xE1\xBA\xB4","\xE1\xBA\xB6","\xE1\xBA\xA6","\xE1\xBA\xA4","\xE1\xBA\xA8",   // Ẵ Ặ Ầ Ấ Ẩ
                 "\xE1\xBA\xAA","\xE1\xBA\xAC","\xE1\xBA\xBA","\xE1\xBA\xBC","\xE1\xBA\xB8",   // Ẫ Ậ Ẻ Ẽ Ẹ
                 "\xE1\xBB\x80","\xE1\xBA\xBE","\xE1\xBB\x82","\xE1\xBB\x84","\xE1\xBB\x86",   // Ề Ế Ể Ễ Ệ
                 "\xE1\xBB\x88","\xE1\xBB\x8A","\xE1\xBB\x8E","\xE1\xBB\x8C","\xE1\xBB\x92",   // Ỉ Ị Ỏ Ọ Ồ
                 "\xE1\xBB\x90","\xE1\xBB\x94","\xE1\xBB\x96","\xE1\xBB\x98","\xE1\xBB\x9C",   // Ố Ổ Ỗ Ộ Ờ
                 "\xE1\xBB\x9A","\xE1\xBB\x9E","\xE1\xBB\xA0","\xE1\xBB\xA2","\xE1\xBB\xA6",   // Ớ Ở Ỡ Ợ Ủ
                 "\xE1\xBB\xA4","\xE1\xBB\xAA","\xE1\xBB\xA8","\xE1\xBB\xAC","\xE1\xBB\xAE",   // Ụ Ừ Ứ Ử Ữ
                 "\xE1\xBB\xB0","\xE1\xBB\xB2","\xE1\xBB\xB6","\xE1\xBB\xB8","\xE1\xBB\xB4",   // Ự Ỳ Ỷ Ỹ Ỵ
                
                 "\xE1\xBA\xA3","\xE1\xBA\xA1","\xE1\xBA\xB1","\xE1\xBA\xAF","\xE1\xBA\xB3",   // ả ạ ằ ắ ẳ 
                 "\xE1\xBA\xB5","\xE1\xBA\xB7","\xE1\xBA\xA7","\xE1\xBA\xA5","\xE1\xBA\xA9",   // ẵ ặ ầ ấ ẩ  
                 "\xE1\xBA\xAB","\xE1\xBA\xAD","\xE1\xBA\xBB","\xE1\xBA\xBD","\xE1\xBA\xB9",   // ẫ ậ ẻ ẽ ẹ abadbbbdb9
                 "\xE1\xBB\x81","\xE1\xBA\xBF","\xE1\xBB\x83","\xE1\xBB\x85","\xE1\xBB\x87",   // ề ế ể ễ ệ  81bf838587 
                 "\xE1\xBB\x89","\xE1\xBB\x8B","\xE1\xBB\x8F","\xE1\xBB\x8D","\xE1\xBB\x93",   // ỉ ị ỏ ọ ồ  898b8f8d93
                 "\xE1\xBB\x91","\xE1\xBB\x95","\xE1\xBB\x97","\xE1\xBB\x99","\xE1\xBB\x9D",   // ố ổ ỗ ộ ờ  919597999d
                 "\xE1\xBB\x9B","\xE1\xBB\x9F","\xE1\xBB\xA1","\xE1\xBB\xA3","\xE1\xBB\xA7",   // ớ ở ỡ ợ ủ  9b9fa1a3a7
                 "\xE1\xBB\xA5","\xE1\xBB\xAB","\xE1\xBB\xA9","\xE1\xBB\xAD","\xE1\xBB\xAF",   // ụ ừ ứ ử ữ  a5aba9adaf
                 "\xE1\xBB\xB1","\xE1\xBB\xB3","\xE1\xBB\xB7","\xE1\xBB\xB9","\xE1\xBB\xB5"    // ự ỳ ỷ ỹ ỵ  b1b3b7b9b5             
                };
char* Ma_font_3byte[]={
                       "\xBF","\xE4","\xE2","\xE3","\xDB",  // Ả Ạ Ằ Ắ Ẳ
                       "\xE5","\xDB","\xC7","\xC6","\xBE",  // Ẵ Ặ Ầ Ấ Ẩ
                       "\xE0","\xE1","\xED","\xE7","\xEB",  // Ẫ Ậ Ẻ Ẽ Ẹ
                       "\xCB","\xCA","\xEE","\xEA","\xE9",  // Ề Ế Ể Ễ Ệ
                       "\xCF","\xEF","\xF0","\xD5","\xF3",  // Ỉ Ị Ỏ Ọ Ồ
                       "\xF2","\xD1","\xDF","\xF4","\xF6",  // Ố Ổ Ỗ Ộ Ờ
                       "\xD8","\xDE","\xF8","\xF7","\xF1",  // Ớ Ở Ỡ Ợ Ủ
                       "\xFA","\xDB","\xFB","\xBB","\xFC",  // Ụ Ừ Ứ Ử Ữ
                       "\xEC","\xFD","\xBA","\xFE","\xDD",  // Ự Ỳ Ỷ Ỹ Ỵ
                       
                       "\x84","\x83","\x8D","\x8E","\x91", // ả ạ ằ ắ ẳ
                       "\x8F","\x90","\x88","\x87","\x8B", // ẵ ặ ầ ấ ẩ  
                       "\x89","\x8A","\xA7","\xA6","\xA5", // ẫ ậ ẻ ẽ ẹ
                       "\xAA","\xAE","\xAD","\xAB","\xAC", // ề ế ể ễ ệ
                       "\xB3","\xB2","\x97","\x95","\x9A", // ỉ ị ỏ ọ ồ
                       "\x99","\x9C","\x9D","\x9B","\xA0", // ố ổ ỗ ộ ờ
                       "\x9F","\xA8","\xA2","\xA1","\xDF", // ớ ở ỡ ợ ủ
                       "\x80","\xCF","\xB4","\xB8","\xB5", // ụ ừ ứ ử ữ
                       "\xB7","\xEE","\x60","\x5F","\x1F"  // ự ỳ ỷ ỹ ỵ 
                      };
 // MA PHU DE KIEM TRA               
char*MA_Phu_3[]={
                  "ba","ba","ba","ba","ba",
                  "ba","ba","ba","ba","ba",
                  "ba","ba","ba","ba","ba",
                  "bb","ba","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  //"bb","ba"
                  "ba","ba","ba","ba","ba",
                  "ba","ba","ba","ba","ba",
                  "ba","ba","ba","ba","ba",
                  "bb","ba","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb",
                  "bb","bb","bb","bb","bb"
                  };
// BANG MA O KI TU CUOI CUNG LUN NHA
char* MA_ASCII_3[]={
                     "a2","a0","b0","aE","b2",
                     "b4","b6","a6","a4","a8",
                     "bb","ac","ba","bc","b8",
                     "80","be","82","84","86",
                     "88","8a","8e","8c","92",
                     "90","94","96","98","9c",
                     "9a","9e","a0","a2","a6",
                     "a4","aa","a8","ac","ae",
                     "b0","b2","b6","b8","b4",
                     //"ab","bf"
                     "a3","a1","b1","af","b3",
                     "b5","b7","a7","a5","a9",
                     "ab","ad","bb","bd","b9",
                     "81","bf","83","85","87",
                     "89","8b","8f","8d","93",
                     "91","95","97","99","9d",
                     "9b","9f","a1","a3","a7",
                     "a5","ab","a9","ad","af",
                     "b1","b3","b7","b9","b5"
                     };

// code giai ma hex
void configLedmatrix(void){
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setPanelBrightness(192);   // Do dai cua tam hien thi
  matrix.clear();                   // Xoa man hinh
  timer_update_display = millis();  // khoi tao thoi gian update man hinh
  timer_update_value = millis();    //khoi tao thoi gian update ket qua modbus
}

char*Array_tmk_1[]={"\x30\x30\x30\x30","\x30\x30\x30","\x30\x30","\x30",""}; // do dai lent la 4 nha pro
char*Array_tmk_2[]={"    ","   ","  "," ",""};
char*Array_tmk_3[]={"w","ww","www","wwww","wwwww"};
int ht_tmk_a(int s)
{
  int val_kq;
  if(s/10<1)
    {
      val_kq=0;
    }else if(s/100<1)
    {
      val_kq=1;
    }
    else if(s/1000<1)
    {
      val_kq=2;
    }else if(s/10000<1)
    {
      val_kq=3;
    }
    else
    {
      val_kq=4;
    }
    return val_kq;
}
*/
// chi claer so thoi nha
void clear_so(int c1,int c2)
{
  for(int c3=c2-8;c3<=c2;c3++)
  {
    for(int c4=c1;c4<=c1+6;c4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(c4,c3,0);
    }
  }
}
// code giai ma hex
void configLedmatrix(void){
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setPanelBrightness(1000000);   // Do dai cua tam hien thi
  matrix.clear();                   // Xoa man hinh
  timer_update_display = millis();  // khoi tao thoi gian update man hinh
  timer_update_value = millis();    //khoi tao thoi gian update ket qua modbus
}
// chi claer so thoi nha
void clear_vitri(int d1,int d2,int set)
{
  for(int d3=d2-29;d3<=d2;d3++)
  {
    for(int d4=d1;d4<=d1+(15*set);d4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(d4,d3,0);
    }
  }
}
void clear_vitri1(int d1,int d2,int set)
{
  for(int d3=d2-9;d3<=d2;d3++)
  {
    for(int d4=d1;d4<=d1+(6*set);d4++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(d4,d3,0);
    }
  }
}

void vien_ngang(int y6)
{
  for(int n6=y6;n6<y6+1;n6++)
  {
    for(int c6=0;c6<64;c6++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(c6,n6,LED_WHITE_LOW);
    }
  }
}
void vien_doc(int x7)
{

  for(int n7=0;n7<=32;n7++)
  {
    for(int c7=x7;c7<x7+1;c7++)             ///xiu co the sua cho nay nha
    {
      matrix.drawPixel(c7,n7,LED_WHITE_LOW);
    }
  }
}

// function LED html 
/* Style */
String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:12px auto;font-size:18px}"
"input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
"#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
"form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn{background:#3498db;color:#fff;cursor:pointer}</style>";

/* Login page */
String loginIndex = 
"<form name=loginForm>"
"<h1>TMK ESP32 LED Matrix</h1>"
"<input name=userid placeholder='User ID'> "
"<input name=pwd placeholder=Password type=Password> "
"<input type=submit onclick=check(this.form) class=btn value=Login></form>"
"<script>"
"function check(form) {"
"if(form.userid.value=='duc' && form.pwd.value=='tmducam18')"
"{window.open('/serverIndex')}"
"else"
"{alert('Error Password or Username')}"
"}"
"</script>" + style;

 
/* Server Index Page */
String serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<h1>TMK ESP32 LED Matrix</h1>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Choose file...</label>"
"<input type='submit' class=btn value='Update'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>" + style;
