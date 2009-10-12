#ifndef _TEXTCONVERTER_H_
#define _TEXTCONVERTER_H_

#include <string.h>
#include <malloc.h>

typedef unsigned char byte;       // 1 byte
typedef unsigned short int word;  // 2 bytes
typedef unsigned int dword;       // 4 bytes
typedef unsigned long int qword;  // 8 bytes

inline byte lowbyte (word a) { return (byte)a; }
inline byte hibyte (word a) { return (byte)((a >> 8) & 0xFF); }
inline word loword (dword a) { return (word)a; }
inline word hiword (dword a) { return (word)(((a) >> 16) & 0xFFFF); }

// encodings
// 1 byte
const char putf1[] = "UTF-1\0"; // really 1 byte ???
const char putf7[] = "UTF-7\0";
const char putf8[] = "UTF-8\0"; // variable size. FUCK!!!
const char pebcdic[] = "UTF-EBCDIC\0";
const char pscsu[] = "SCSU\0";
const char pbocu1[] = "BOCU-1\0";
// ETSI GSM 0.3.38
const char petsi[] = "ETSI\0"; // 7-bit
const char pgsm[] = "GSM\0";
const char pgsm0338[] = "GSM0338\0";
// 2 bytes
const char putf16be[] = "UTF-16 BE\0"; // variable size. FUCK!!!
const char pucs2be[] = "UCS-2 BE\0"; // variable size. FUCK!!!
const char putf16le[] = "UTF-16 LE\0"; // variable size. FUCK!!!
const char pucs2le[] = "UCS-2 LE\0"; // variable size. FUCK!!!
// 4 bytes
const char putf32be[] = "UTF-32 BE\0";
const char pucs4be[] = "UCS-4 BE\0";
const char putf32le[] = "UTF-32 LE\0";
const char pucs4le[] = "UCS-4 LE\0";

// Maybe like universal encoding will use UTF32 Big Endian.
// But it's fucking big!!!
// But universal...

const dword bom[] = { 0xefbbbf00,   // utf-8     0
                      0xfeff0000,   // utf-16 be 1
                      0xfffe0000,   // utf-16 le 2
                      0x0000feff,   // utf-32 be 3
                      0xfffe0000,   // utf-32 le 4
                      0x2b2f7638,   // utf-7     5
                      0x2b2f7639,   // utf-7     6
                      0x2b2f762b,   // utf-7     7
                      0x2b2f762f,   // utf-7     8
                      0xf7644c00,   // utf-1     9
                      0xdd736673,   // ebcdic   10
                      0x0efeff00,   // scsu     11
                      0xfbee28ff }; // bocu1    12
struct BUFFER {
  dword size;
  byte *data;
};
class TextConverter {
 public:
  TextConverter();
  ~TextConverter();
// variables
  byte  *cConverted;
  word  *wConverted;
  dword *dwConverted;
// function for text converting
// input - text to convert
// size in - size of input buffer in bytes
// enc_in - input text encode
// enc_out - output text encode
// output - converted text with type marked in type_out
// size_out - size of converted buffer
// type_out - marks type of output buffer:
//            1 - if byte
//            2 - if word
//            4 - if dword
//            other - if error
// return value: 1 if success or 0 if error
  bool Convert (byte* input, dword size_in, char* enc_in,
                char* enc_out, byte* output, dword size_out,
                byte type_out);
// function for avtomated reading of encoding.
// works with very small variety of encodings.
// dw1st4bytes - first 4 bytes of input text
// return text encoding or 0 if encoding could not be identificated
  char* Guess (dword dw1st4bytes);
  int GetLastError () { return errorcode; }
 private:
// Error codes
typedef enum TextConverterErrorCodes {
// there is no error
  NoError,
// error input data, wrong symbol
  InputWrongSymbol
};
// variables
  BUFFER dwData;
  int errorcode;
// functions
// ETSI GSM 0.3.38
  bool EtsiGsm0338 (BUFFER *in);
  BUFFER* EtsiGsm0338 ();
};
#endif
