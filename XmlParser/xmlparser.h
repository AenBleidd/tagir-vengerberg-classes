///////////////////////////////////////////////
//       XmlParser Library version 1.0       //
//       Copyleft 2009 WishmasterSoft        //
///////////////////////////////////////////////
#ifndef _xmlparser_h_
#define _xmlparser_h_
#include <stdio.h>
// Class For parsing xml files
/* Error codes
0 - there is no errors (false alarm)
1 - some file is opened. please close it before opening or use class copy
2 - error while trying to open file
3 - symbol outside brackets < />
4 - some error in encoding. There is no such value!
5 - there isno data in buffers. Maybe file was empty.
*/
typedef unsigned char byte;       // 1 byte
typedef unsigned short int word;  // 2 bytes
typedef unsigned int dword;       // 4 bytes
typedef unsigned long int qword;  // 8 bytes

// now unused
inline byte lowbyte (word a) { return (byte)a; }
inline byte hibyte (word a) { return (byte)((a >> 8) & 0xFF); }
// now unused
inline word loword (dword a) { return (word)a; }
// now unused
inline word hiword (dword a) { return (word)(((a) >> 16) & 0xFFFF); }

struct XMLTREE;
struct XMLPARAM;
struct XMLINFO {
  char *xmlversion;  // Version of the xml file syntax
  char *encoding;  // Language encoding;
  byte byteorderenc;  // information about encoding and byte order
  /* Encoding info
    0 - Some error or there is no xml header
    ------Byte Order Mark Exists------
     1 - UCS-4 big-endian machine (1234 order)
     2 - UCS-4 little-endian machine (4321 order)
     3 - UCS-4 big-endian machine unusual octet order (2143)
     4 - UCS-4 little-endian machine unusual octet order (3412)
     5 - UTF-16 big-endian
     6 - UTF-16 little-endian
     7 - UTF-8
    ------Byte Order Mark Doesn't Exist------
     8 - maybe UCS-4 big-endian machine (1234 order)
     9 - maybe UCS-4 little-endian machine (4321 order)
    10 - maybe UCS-4 big-endian machine unusual octet order (2143)
    11 - maybe UCS-4 little-endian machine unusual octet order (3412)
    12 - maybe UTF-16 big-endian or big-endian ISO-10646-UCS-2
         BUT big-endian
    13 - maybe UTF-16 little-endian or little-endian ISO-10646-UCS-2
         BUT little-endian
    14 - maybe UTF-8, ISO 646, ASCII, ISO 8859, Shift-JIS, EUC
         or some other 7-bit, 8-bit or mixed-width encoding
    15 - EBCDIC
  */
  char *standalone;  // Standalone Document Declaration
};
struct XMLTREE {
  XMLTREE *parent;
  char *branch;
  char *value;
  XMLPARAM *param;
  XMLTREE *child;
};
struct XMLPARAM {
  XMLTREE *parent;
  XMLPARAM *previous;
  char *param;
  char *value;
  XMLPARAM *next;
};
class XmlParser {
 public:
  XmlParser();
  ~XmlParser();
  // Open xml file
  bool XmlOpen(char *filename);
  // Write data to xml file
  bool Write();
  // Close xml file
  void Close();
  // return last error; returns 0 if there is no errors
  int GetLastXmlError() { return errorcode; }
  // return line with error
  int GetLastXmlErrorLine();
  // return the version of the xml file syntax
  char* GetXmlVersion() { return xmlinfo.xmlversion; }
  // return the type of language encoding
  char* GetXmlLangEncoding() { return xmlinfo.encoding; }
  // return the attribute 'Standalone Document Declaration'
  char* IsStandalone() { return xmlinfo.standalone; }
 private:
  XMLINFO xmlinfo;  // Information about opened xml file
  FILE *xmlfile;  // descriptor of the open xml file
  dword *data;  // storage of raw xml data
  dword *cdata;  // storage of CDATA
  int errorcode;  // error code
  int errorsymbol;  // position of symbol that causes error. for debugging
  int filesize;  // size of the file in bytes

  // Check xml file
  // output parameters shows if the xml document valid and\or well-formed
  bool Check(bool wellformed, bool valid);
  bool Load();  // Load xml file
  void Raw2Tree();  // Convert raw xml data to tree view for using
  void Tree2Raw();  // Convert tree view to raw xml data for writing to xml file
};
#endif
