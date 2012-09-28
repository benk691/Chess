#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general


class CodeObject(xml.dom.Node):
    CODE_LINE = sum( [ ord(symb) for symb in "CODE_LINE" ] )
    CODE_CONTENT = sum( [ ord(symb) for symb in "CODE_CONTENT" ] )
    
    def __init__(self, code_type, line_numb_tag_name = general.__LINE_NUMB_TAG_NAME__, content_tag_name = general.__CONTENT_TAG_NAME__):
        self.line_numb_tag_name = line_numb_tag_name
        self.content_tag_name = content_tag_name
        self.code_obj_str = ""
        self.code_type = code_type
        self.line_map = dict()
        self.content = None
        self.xmlCodeNode = None
    
    
    def CodeInfoGenerator(self):
        if self.code_type == self.CODE_LINE:
            yield self.line_numb_tag_name
        
        elif self.code_type == self.CODE_CONTENT:
            yield self.content_tag_name


code_obj = CodeObject( CodeObject.CODE_LINE )

print "dir( xml.dom.Node ) = ", dir( xml.dom.Node )
print "\ndir( code_obj ) = ", dir( code_obj )
print "\ndir( code_obj.line_map ) = ", dir( code_obj.line_map )

print "\nhasattr( code_obj.line_map, \"__iter__\" ) = ", hasattr( code_obj.line_map, "__iter__" )

code_obj.line_map = []

print "\nhasattr( code_obj.line_map, \"__iter__\" ) = ", hasattr( code_obj.line_map, "__iter__" )
