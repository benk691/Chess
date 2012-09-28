#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general

############################################################
# TODO: 
#       - Make code more general by incorporating plugins
############################################################


class CodeObject(object):
    def __init__(self, code_type, code_tag_name = general.__CODE_TAG_NAME__, end_index = general.__END_INDEX__):
        self.code_obj_str = ""
        self.code_type = code_type
        self.hash_value = sum( [ ord(symb) for symb in str(self.code_type) ] )
        self.code_tag_name = code_tag_name
        self.tag_name = ""
        self.end_index = end_index
        self.attr_map = dict()
        self.xmlCodeNode = None
    
    
    def codeInfoGenerator(self):
        if self.code_type == self.CODE_LINE and len(self.line_map) == 1:
            yield self.line_numb_tag_name, self.attr_map
            
            try:
                item = self.line_map.items()[ 0 ]
                
                self.attr_map[ self.line_numb_tag_name ] = str(item[ 0 ])
                
                yield self.code_tag_name, self.attr_map
                
                item[ 1 ].updateAttrMap()
                
                yield item[ 1 ].code_tag_name, item[ 1 ].attr_map
            
            except:
                pass
        
        elif self.code_type == self.CODE_CONTENT:
            yield self.content_tag_name, self.attr_map
    
    
    def updateAttrMap(self):
        pass
    
    
    def _FormString(self):
        if self.xmlCodeNode != None:
            self.code_obj_str = self.xmlCodeNode.toprettyxml()
        
        else:
            self.code_obj_str = str(self.xmlCodeNode)
    
    
    def __repr__(self):
        self._FormString()
        
        return self.code_obj_str
    
    
    def __str__(self):
        self._FormString()
        
        return self.code_obj_str



