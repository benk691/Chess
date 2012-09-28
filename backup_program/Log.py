#!/usr/bin/env /tps/bin/python

import sys, os, re, copy, inspect, subprocess, xml, xml.dom, xml.dom.minidom
import general


class Log(object):
    def __init__(self, version = 0, comment = general.__COMMENT_ID__, include = general.__INCLUDE_ID__, cpp = general.__CPP_ID__, debug = general.__DEBUG_ID__, function = general.__FUNCTION_ID__, struct = general.__STRUCT_ID__, cclass = general.__CLASS_ID__, variable = general.__VARIABLE_ID__, string = general.__STRING_ID__, nl_id = general.__NL_ID__, amp_id = general.__AMP_ID__, lt_id = general.__LT_ID__, gt_id = general.__GT_ID__, dbl_quote_id = general.__DBL_QUOTE_ID__, uni_quote_id = general.__UNI_QUOTE_ID__, src_dir_name = general.__SRC_DIR_NAME__):
        self.log_str = ""
        self.comment_id = comment
        self.include_id = include
        self.cpp_id = cpp
        self.debug_id = debug
        self.function_id = function
        self.struct_id = struct
        self.class_id = cclass
        self.variable_id = variable
        self.string_id = string
        self.nl_id = nl_id
        self.amp_id = amp_id
        self.lt_id = lt_id
        self.gt_id = gt_id
        self.dbl_quote_id = dbl_quote_id
        self.uni_quote_id = uni_quote_id
        self.src_dir_name = src_dir_name
        
        self.extractKeyList = [ self.comment_id, self.string_id, self.macro_id, self.include_id, self.debug_id, self.function_id, self.struct_id, self.class_id, self.variable_id  ]
        
        self.version = version
        self.file_map = dict()
        
        self._InitContainedInMap()
        self._InitContainerMap()
        self._InitMatchMap()
        self._InitExtractMap()
        self._InitXml()
        self._establishVersion()
        self._logCode()
    
    
    def _logCode(self):
        for item in os.walk(self.src_dir_name):
            for file_name in item[ 2 ]:
                pos = file_name.rfind('.')
                ext = ""
                
                if pos >= 0 and pos < len(file_name):
                    ext = file_name[ pos :  ]
                
                if file_name[ 0 ] != '.' and (ext == ".cc" or ext == ".h"):
                    self._logFile(file_name)
    
    
    def _logFile(self, file_name):
        self.file_map[ file_name ] = self.rootDom.createElement("file")
        
        self.file_map[ file_name ].setAttributeNode(self.rootDom.createAttribute("name"))
        self.file_map[ file_name ].setAttribute("name", file_name)
        
        self._processCodeByLine(file_name)
        
        self.root.appendChild(self.file_map[ file_name ])
    
    
    def _processCodeByLine(self, file_name):
        byLineNode = self.rootDom.createElement("byLine")
        
        path = self.src_dir_name + "/" + file_name
        
        src_file = open(path, "r")
        
        line_numb = 1
        in_comment = False
        in_cpp_def = False
        
        for line in src_file:
            content = copy.deepcopy( line )
            content = self.match_map[ self.nl_id ].sub("", content)
            
            codeNode = self._createCodeNode(content, line_numb)
            
            codeNode, content, in_comment = self._extractCode(codeNode, content, in_comment)
            
            byLineNode.appendChild(codeNode)
            
            line_numb += 1
        
        src_file.close()
        
        self.file_map[ file_name ].appendChild(byLineNode)
    
    
    def _extractCode(self, codeNode, content, in_comment):
        for key in self.extractKeyList:
            codeNode, content, in_comment = self.extract_map[ key ]( codeNode, content, in_comment )
        
        return codeNode, content, in_comment
    
    
    def _extractComment(self, codeNode, content, in_comment):
        delimit = lambda a: "\"%s\"" % (a)
        
        sl_delim = "//"
        start_ml_delim = "/*"
        end_ml_delim = "*/"
        
        commentNode = None
        
        if in_comment:
            commentNode = self.rootDom.createElement("comment")
            
            pos = content.find(end_ml_delim)
            
            if pos >= 0 and pos < len(content):
                comment = content[  : pos ]
                
                commentNode.appendChild( self.rootDom.createTextNode( delimit( comment ) ) )
                
                content = content[ (pos + len(end_ml_delim)) :  ]
                
                in_comment = False
            
            else:
                commentNode.appendChild( self.rootDom.createTextNode( delimit( content ) ) )
        
        if not in_comment:
            sl_pos = content.find(sl_delim)
            
            if sl_pos >= 0 and sl_pos < len(content):
                if commentNode == None:
                    commentNode = self.rootDom.createElement("comment")
                
                comment = content[ (sl_pos + len(sl_delim)) :  ]
                
                commentNode.appendChild( self.rootDom.createTextNode( delimit( comment ) ) )
                
                content = content[  : sl_pos ]
            
            start_pos = content.find(start_ml_delim)
            end_pos = content.find(end_ml_delim)
            
            while start_pos >= 0 and start_pos < len(content):
                if commentNode == None:
                    commentNode = self.rootDom.createElement("comment")
                
                if end_pos >= 0 and end_pos < len(content):
                    comment = content[ (start_pos + len(start_ml_delim)) : end_pos ]
                    
                    commentNode.appendChild( self.rootDom.createTextNode( delimit( comment ) ) )
                    
                    content = content[  : start_pos ] + content[ (end_pos + len(end_ml_delim)) :  ]
                    
                    start_pos = content.find(start_ml_delim)
                    end_pos = content.find(end_ml_delim)
                
                else:
                    comment = content[ (start_pos + len(start_ml_delim)) :  ]
                    
                    commentNode.appendChild( self.rootDom.createTextNode( delimit( comment ) ) )
                    
                    content = content[  : start_pos ]
                    
                    in_comment = True
                    
                    break
        
        if commentNode != None:
            codeNode.appendChild(commentNode)
        
        return codeNode, content, in_comment
    
    
    def _extractInclude(self, codeNode, content, in_comment):
        if not in_comment:
            pos = content.find("#include")
            
            includeNode = None
            
            if pos >= 0 and pos < len(content):
                includeNode = self.rootDom.createElement("include")
                includeNode.setAttributeNode(self.rootDom.createAttribute("loc"))
                
                angle_start_pos = content.find("<")
                angle_end_pos = content.find(">")
                quote_start_pos = content.find("\"")
                quote_end_pos = quote_start_pos + content[ (quote_start_pos + 1) :  ].find("\"") + 1
                
                if angle_start_pos >= 0 and angle_start_pos < len(content) and angle_end_pos >= 0 and angle_end_pos < len(content):
                    loc = content[ (angle_start_pos + 1) : angle_end_pos ]
                    
                    includeNode.setAttribute("loc", loc)
                    
                    content = content[ (angle_end_pos + 1) :  ]
                
                elif quote_start_pos >= 0 and quote_start_pos < len(content) and quote_end_pos >= 0 and quote_end_pos < len(content):
                    loc = content[ (quote_start_pos + 1) : quote_end_pos ]
                    
                    includeNode.setAttribute("loc", loc)
                    
                    content = content[ (quote_end_pos + 1) :  ]
            
            if includeNode != None:
                codeNode.appendChild(includeNode)
        
        return codeNode, content, in_comment
    
    
    def _extractMacro(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _extractDebug(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _extractFunction(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _extractStruct(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _extractClass(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _extractVariable(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _extractString(self, codeNode, content, in_comment):
        return codeNode, content, in_comment
    
    
    def _createCodeNode(self, line, line_numb):
        codeNode = self.rootDom.createElement("code")
        
        codeNode.setAttributeNode(self.rootDom.createAttribute("lineNumb"))
        codeNode.setAttribute("lineNumb", str(line_numb))
        
        return codeNode
    
    
    def _establishVersion(self):
        self.versionNode = self.rootDom.createElement("chess")
        
        self.versionNode.setAttributeNode(self.rootDom.createAttribute("version"))
        self.versionNode.setAttribute("version", str(self.version))
        
        self.root.appendChild(self.versionNode)
    
    
    def _ResetContainedInMap(self):
        self.contained_in_map[ self.comment_id ] = False
        self.contained_in_map[ self.string_id ] = False
        self.contained_in_map[ self.cpp_id ] = False
        self.contained_in_map[ self.class_id ] = False
        self.contained_in_map[ self.struct_id ] = False
        self.contained_in_map[ self.function_id ] = False
        self.contained_in_map[ self.variable_id ] = False
    
    
    def _ResetContainerMap(self):
        self.container_map[ self.comment_id ] = None
        self.container_map[ self.string_id ] = None
        self.container_map[ self.cpp_id ] = None
        self.container_map[ self.class_id ] = None
        self.container_map[ self.struct_id ] = None
        self.container_map[ self.function_id ] = None
        self.container_map[ self.variable_id ] = None
    
    
    def _InitXml(self):
        self.dom = xml.dom.getDOMImplementation()
        self.rootDom = self.dom.createDocument(None, "log", None)
        self.root = self.rootDom.documentElement
    
    
    def _InitContainedInMap(self):
        self.contained_in_map = dict()
        
        self.contained_in_map[ self.comment_id ] = False
        self.contained_in_map[ self.string_id ] = False
        self.contained_in_map[ self.cpp_id ] = False
        self.contained_in_map[ self.class_id ] = False
        self.contained_in_map[ self.struct_id ] = False
        self.contained_in_map[ self.function_id ] = False
        self.contained_in_map[ self.variable_id ] = False
    
    
    def _InitContainerMap(self):
        self.container_map = dict()
        
        self.container_map[ self.comment_id ] = None
        self.container_map[ self.string_id ] = None
        self.container_map[ self.cpp_id ] = None
        self.container_map[ self.class_id ] = None
        self.container_map[ self.struct_id ] = None
        self.container_map[ self.function_id ] = None
        self.container_map[ self.variable_id ] = None
    
    
    def _InitMatchMap(self):
        self.match_map = dict()
        
        self.match_map[ self.nl_id ] = re.compile(r"\n+")
        self.match_map[ self.amp_id ] = re.compile(r"&amp;")
        self.match_map[ self.lt_id ] = re.compile(r"&lt;")
        self.match_map[ self.gt_id ] = re.compile(r"&gt;")
        self.match_map[ self.dbl_quote_id ] = re.compile(r"&quot;")
        self.match_map[ self.uni_quote_id ] = re.compile(r"&apos;")
    
    
    def _InitExtractMap(self):
        self.extract_map = dict()
        
        self.extract_map[ self.comment_id ] = self._extractComment
        self.extract_map[ self.include_id ] = self._extractInclude
        self.extract_map[ self.macro_id ] = self._extractMacro
        self.extract_map[ self.debug_id ] = self._extractDebug
        self.extract_map[ self.function_id ] = self._extractFunction
        self.extract_map[ self.struct_id ] = self._extractStruct
        self.extract_map[ self.class_id ] = self._extractClass
        self.extract_map[ self.variable_id ] = self._extractVariable
        self.extract_map[ self.string_id ] = self._extractString
    
    
    def _FormString(self):
        self.log_str = self.rootDom.toprettyxml()
        
        self.log_str = self.match_map[ self.amp_id ].sub("&", self.log_str)
        self.log_str = self.match_map[ self.lt_id ].sub("<", self.log_str)
        self.log_str = self.match_map[ self.gt_id ].sub(">", self.log_str)
        self.log_str = self.match_map[ self.dbl_quote_id ].sub("\"", self.log_str)
        self.log_str = self.match_map[ self.uni_quote_id ].sub("\'", self.log_str)
    
    
    def __repr__(self):
        return self.rootDom.toprettyxml()
    
    
    def __str__(self):
        return self.rootDom.toprettyxml()



"""
class Changelog(object):
    def __init__(self, version = 0, added = __ADDED__, mod = __MOD__, deleted = __DELETED__):
        self.added = added
        self.mod = mod
        self.deleted = deleted
        self.ns_list = [ self.added, self.mod, self.deleted ]
        self.old_version = version - 1
        self.current_version = version
        
        self._InitXml()
    
    
    def _InitXml(self):
        self.dom = xml.dom.getDOMImplementation()
        self.rootDom = dom.createDocument(None, "changelog", None)
        
        self._createRootNS()
    
    
    def _createRootNS(self):
        for ns in ns_list:
            name = "xmlns:%s" % ns
            
            self.rootDom.documentElement.setAttributeNode(self.rootDom.createAttribute(name))
            self.rootDom.documentElement.setAttribute(name, ns)
"""



