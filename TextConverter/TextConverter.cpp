#include "TextConverter.h"

TextConverter::TextConverter() {
  cConverted = 0;
  wConverted = 0;
  dwConverted = 0;
  errorcode = NoError;
}
TextConverter::~TextConverter() {
}
//TODO: Check what it really returns
char* TextConverter::Guess(dword dw1st4bytes) {
  const dword dwMaskSm = 0xffffff00;
  const dword dwMaskBig = 0xffff0000;
  dword dwtemp;
  dword dwtempbytes;
// try to ident encoding
  if (dw1st4bytes == bom[3])
    return (char*)putf32be;
  if (dw1st4bytes == bom[4])
    return (char*)putf32le;
  if (dw1st4bytes == bom[5] ||
      dw1st4bytes == bom[6] ||
      dw1st4bytes == bom[7] ||
      dw1st4bytes == bom[8])
    return (char*)putf7;
  if (dw1st4bytes == bom[10])
    return (char*)pebcdic;
  dwtemp = bom[12] & dwMaskSm;
  dwtempbytes = dw1st4bytes & dwMaskSm;
  if (dw1st4bytes == bom[12] || dwtempbytes == dwtemp)
    return (char*)pbocu1;
  if (dwtempbytes == bom[11])
    return (char*)pscsu;
  if (dwtempbytes == bom[9])
    return (char*)putf1;
  if (dwtempbytes == bom[0])
    return (char*)putf8;
  dwtempbytes = dw1st4bytes & dwMaskBig;
  if (dwtempbytes == bom[1])
    return (char*)putf16be;
  if (dwtempbytes == bom[2] && dwtempbytes != dw1st4bytes)
    return (char*)putf16le;
return 0;
}
bool TextConverter::Convert (byte* input, dword size_in, char* enc_in,
                             char* enc_out, byte* output, dword size_out,
                             byte type_out)
{
  BUFFER in, out;
// initialize input buffer
  in.size = size_in;
  in.data = input;
// Working with text...

// initialize output data from output buffer
  size_out = out.size;
  output = out.data;
  return true;
}
bool TextConverter::EtsiGsm0338 (BUFFER* in) {
// new buffer with size for utf-32 & 4 bytes for bom
  dword size = in->size*4+4;
  dword *buf = (dword*)malloc(in->size*4+4);
  for ( dword i = 0; i < in->size; i++ ) {
    switch (in->data[i]) {
      default:
        errorcode = InputWrongSymbol;
        return false;
        break;
    }
  }
// Saving the data
  dwData.size = size;
  dwData.data = (byte*)buf;
  return true;
}