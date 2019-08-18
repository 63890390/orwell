#!/usr/bin/env python3
#Converts things from here: https://github.com/yuan631111976/qtavplayer/blob/b4394d620076cedb05fdc006daee2918baeb73d9/AVOutput.cpp
import re
#TODO: add AV_PIX_FMT_YUV420P,{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},{1,1},0,0,0,false to formats.cp
def constructorWith14Elements(elements):
    struct = '''    pixelFormats[{0}] = PixelFormat {{
        //Fraction yuvSizes[3];
        {{{1},{2},{3}}},
        //Fraction yuvWidths[3];
        {{{4},{5},{6}}},
        //Fraction yuvHeights[3];
        {{{7},{8},{9}}},
        //GLint yuvInternalFormat[3];
        {{{10},{10},{10}}},
        //GLenum yuvGlFormat[3];
        {{{11},{11},{11}}},
        //int textureFormat
        {12},
        //bool isPlanar
        {13},
        //GLenum dataType
        GL_UNSIGNED_BYTE
    }};'''.format(*elements)
    return struct

def constructorWith15Elements(elements):
    struct = '''    pixelFormats[{0}] = PixelFormat {{
        //Fraction yuvSizes[3];
        {{{1},{2},{3}}},
        //Fraction yuvWidths[3];
        {{{4},{5},{6}}},
        //Fraction yuvHeights[3];
        {{{7},{8},{9}}},
        //GLint yuvInternalFormat[3];
        {{{10},{10},{10}}},
        //GLenum yuvGlFormat[3];
        {{{11},{11},{11}}},
        //int textureFormat
        {12},
        //bool isPlanar
        {13},
        //GLenum dataType
        {14}
    }};'''.format(*elements)
    return struct

def constructorWith18Elements(elements):
    struct = '''    pixelFormats[{0}] = PixelFormat {{
        //Fraction yuvSizes[3];
        {{{1},{2},{3}}},
        //Fraction yuvWidths[3];
        {{{4},{5},{6}}},
        //Fraction yuvHeights[3];
        {{{7},{8},{9}}},
        //GLint yuvInternalFormat[3];
        {{{10},{12},{14}}},
        //GLenum yuvGlFormat[3];
        {{{11},{13},{15}}},
        //int textureFormat
        {16},
        //bool isPlanar
        {17},
        //GLenum dataType
        GL_UNSIGNED_BYTE
    }};'''.format(*elements)
    return struct

pixelFormats = open('../PixelFormats.cpp', 'w')
pixelFormats.write('#include "PixelFormats.h"\n\n')
pixelFormats.write('//Generated by converter.py\n\n')

pixelFormats.write('StaticPixelFormats PixelFormats::staticPixelFormats;\n\n')
pixelFormats.write('Fraction zero  = {0,1};\n\
Fraction one   = {1,1};\n\
Fraction two   = {1,2};\n\
Fraction three = {1,3};\n\
Fraction four  = {1,4};\n\n')
pixelFormats.write('StaticPixelFormats::StaticPixelFormats() {\n\n')
with open('formats.cpp', 'r') as file:
    data = file.read()
data = data.splitlines()
data = [x for x in data if x!='']
data = [x for x in data if not '//' in x]
data = list(map(lambda x: x.replace(';', ''), data))
data = list(map(lambda x: x.replace('GL_LUMINANCE16', 'GL_R16'), data)) #GL_LUMINANCE is not supported on CORE profile
data = list(map(lambda x: x.replace('GL_LUMINANCE_ALPHA', 'GL_RG'), data)) #GL_LUMINANCE is not supported on CORE profile
data = list(map(lambda x: x.replace('GL_LUMINANCE', 'GL_RED'), data)) #GL_LUMINANCE is not supported on CORE profile
data = list(map(lambda x: x.replace(' ', ''), data))

for d in data:
    pixel_format = re.search('params\[(.+)\]', d).group(1)
    render_params = re.search('RenderParams\((.+)\)', d).group(1)
    l = render_params.split(',')
    s = ''
    if len(l)==14:
        s = constructorWith14Elements(l)
    elif len(l)==15:
        s = constructorWith15Elements(l)
    elif len(l)==18:
        s = constructorWith18Elements(l)
    else:
        print("DIFFERENT LENGTH! " + str(len(l)) + " for " + pixel_format)
    pixelFormats.write(s + '\n')
pixelFormats.write('}')

print('Written data to file ../pixelFormats.cpp')