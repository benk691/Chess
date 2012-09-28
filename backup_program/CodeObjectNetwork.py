#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general
import CodeObject, Comment


class CodeObjectNetwork(object):
    def __init__(self, xmlDoc, filename, line_numb_encoding = general.__LINE_NUMB_ENCODING__, content_encoding = general.__CONTENT_ENCODING__, line_numb_tag_name = general.__LINE_NUMB_TAG_NAME__, content_tag_name = general.__CONTENT_TAG_NAME__):
        self.line_numb_encoding = line_numb_encoding
        self.content_encoding = content_encoding
        self.line_numb_tag_name = line_numb_tag_name
        self.content_tag_name = content_tag_name
        self.xmlDoc = xmlDoc
        self.filename = filename
        
        self._initEncodingMap()
    
    
    def _initEncodingMap(self):
        self.encoding_map = dict()
        
        self.encoding_map[ self.line_numb_encoding ] = self.xmlDoc.createElement(self.line_numb_tag_name)
        self.encoding_map[ self.content_encoding ] = self.xmlDoc.createElement(self.content_tag_name)



