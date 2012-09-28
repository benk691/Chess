#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general
import CodeObject


class Comment(CodeObject.CodeObject):
    def __init__(self, code_type, comment_id, sl_id = general.__SL_COMMENT_ID__, ml_id = general.__ML_COMMENT_ID__):
        super(Comment, self).__init__(code_type)
        self.sl_id = sl_id
        self.ml_id = ml_id
        self.comment_id = comment_id
        self.delimit = lambda txt: "\"%s\"" % str(txt)
    
    
    def addTxt(self, line_numb, txt):
        data = self.delimit(txt)
        self.line_map[ line_numb ] = self.xmlDoc.createTextNode( data )
        
        if self.content == None:
            self.content = [ data ]
        
        else:
            self.content.append( data )
    
    
    def updateAttrMap(self):
        self.attr_map = dict()
        
        self.attr_map[ "type" ] = self.comment_id



