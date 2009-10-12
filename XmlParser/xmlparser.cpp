///////////////////////////////////////////////
//       XmlParser Library version 1.0       //
//       Copyleft 2009 WishmasterSoft        //
///////////////////////////////////////////////
#include "xmlparser.h"
XmlParser::XmlParser() {
  char nodata[] = "no data";
  xmlinfo.xmlversion = nodata;
  xmlinfo.encoding = nodata;
  xmlinfo.standalone = nodata;
  xmlfile = 0;
  data = 0;
  cdata = 0;
  errorcode = 0;
  errorsymbol = -1;
}
bool XmlParser::XmlOpen(char *filename) {
// Opening the file
  if (xmlfile != 0) {
    errorcode = 1;
    return false;
  }
  xmlfile=(FILE*)fopen(filename, "r");
  if (xmlfile == 0) {
    errorcode = 2;
    return false;
  }
  if (Load() == false) return false;  // Loading the file
  fclose(xmlfile);
  int wellformed, valid;
  // Check xml file
  if (Check(wellformed, valid) == false) return false;
  return true;
}
bool XmlParser::Load() {
  // get filesize
  fseek(xmlfile, 0, SEEK_END);
  filesize = ftell(xmlfile);
  rewind(xmlfile);
  word enc1, enc2;
  // Try to identify encoding
  fread((word*)enc1, 2, 1, xmlfile);
  fread((word*)enc2, 2, 1, xmlfile);
  if (enc1 == 0x0000 && enc2 == 0xfeff) xmlinfo.byteorderenc = 1;
  else if (enc1 == 0xfffe && enc2 == 0x0000) xmlinfo.byteorderenc = 2;
  else if (enc1 == 0x0000 && enc2 == 0xfffe) xmlinfo.byteorderenc = 3;
  else if (enc1 == 0xfeff && enc2 == 0x0000) xmlinfo.byteorderenc = 4;
  else if (enc1 == 0xfeff && enc2 != 0x0000) xmlinfo.byteorderenc = 5;
  else if (enc1 == 0xfffe && enc2 != 0x0000) xmlinfo.byteorderenc = 6;
  else if (enc1 == 0xefbb && hibyte(enc2) == 0xbf) xmlinfo.byteorderenc = 7;
  else if (enc1 == 0x0000 && enc2 == 0x003c) xmlinfo.byteorderenc = 8;
  else if (enc1 == 0x3c00 && enc2 == 0x0000) xmlinfo.byteorderenc = 9;
  else if (enc1 == 0x0000 && enc2 == 0x3c00) xmlinfo.byteorderenc = 10;
  else if (enc1 == 0x003c && enc2 == 0x0000) xmlinfo.byteorderenc = 11;
  else if (enc1 == 0x003c && enc2 == 0x003f) xmlinfo.byteorderenc = 12;
  else if (enc1 == 0x3c00 && enc2 == 0x3f00) xmlinfo.byteorderenc = 13;
  else if (enc1 == 0x3c3f && enc2 == 0x786d) xmlinfo.byteorderenc = 14;
  else if (enc1 == 0x4c6f && enc2 == 0xa794) xmlinfo.byteorderenc = 15;
  else xmlinfo.byteorderenc = 0;
  rewind(xmlfile);
  byte *bdata;
  word *wdata;
  dword* dwdata;
  if (xmlinfo.byteorderenc == 0 ||
      xmlinfo.byteorderenc == 7 ||
      xmlinfo.byteorderenc == 14 ||
      xmlinfo.byteorderenc == 15) {
  // 8-bit or 7-bit encoding or some error but try to read
    bdata = new byte[filesize];
    fread((byte*)bdata, filesize, 1, xmlfile);
  } else if (xmlinfo.byteorderenc == 5 ||
           xmlinfo.byteorderenc == 6 ||
           xmlinfo.byteorderenc == 12 ||
           xmlinfo.byteorderenc == 13) {  // 16-bit encoding
    wdata = new word[filesize/2];
    fread((word*)wdata, filesize/2, 1, xmlfile);
  } else if (xmlinfo.byteorderenc == 1 ||
           xmlinfo.byteorderenc == 2 ||
           xmlinfo.byteorderenc == 3 ||
           xmlinfo.byteorderenc == 4 ||
           xmlinfo.byteorderenc == 8 ||
           xmlinfo.byteorderenc == 9 ||
           xmlinfo.byteorderenc == 10 ||
           xmlinfo.byteorderenc == 11) {  // 32-bit encoding
    dwdata = new dword[filesize/4];
    fread((dword*)dwdata, filesize/4, 1, xmlfile);
  } else {  // unusual byteorderenc parameter
    errorcode = 4;
    return false;
  }
  return true;
}
bool XmlParser::Check(bool wellformed, bool valid) {
  wellformed = false;
  valid = false;
  int i = 0;
  // Main cycle
  return true;
}
